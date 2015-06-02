//------------------------------------------------
//  Programa visualizador de imagenes en formato
//  Targa
//                        Juan V. Guerrero  1998
//------------------------------------------------
//#include"c:\x-vr1~1.1\include\xvrdefs.h"
#include<stdlib.h>
#include<dos.h>
#include<stdio.h>
#include<conio.h>
enum Bool {False = 0, True = 1};
typedef unsigned char uchar;
typedef unsigned int  uint;
typedef unsigned long ulong;

#define XVRMK_FP(s,o)  ( (void far *)( ((ulong)(s) << 16) + (ulong)(o) ))
#define useSVGA 0


uint CurBank;
uint BytesPerLine;
uchar BytesPerPixel;
const ulong VideoAdress = 0xA0000L;
uchar *VideoMem;
void (*SetBank)(uint);
void putpixel(int x, int y, uchar c, Bool usefast = False);
uint hic;
int redbase, bluebase, greenbase;

void TridentNewBank(uint bnk){
 asm{
  mov al, 0x06
  mov dx, 0x03CE
  out dx, al
  mov dx, 0x03CF
  in ax,  dx
  or ax,  4
  shl ax, 8
  or ax,  6
  mov dx, 0x03CE
  out dx, ax
  mov dx, 0x03C4
  mov al, 0x0B
  out dx, al
  mov dx, 0x03C5
  in ax,  dx
  mov ax, [bnk]
  xor ax, 0x0002
  shl ax, 0x0008
  or ax,  0x000E
  mov dx, 0x03C4
  out dx, ax
 }
}

void initgraph(){
 if(useSVGA){
  asm{
   mov ax, 0x005d
   int 0x10
  }
  CurBank = 255;
//  SetBank = trdnt_newbank;
  BytesPerLine = 640;
  BytesPerPixel = 1;
  //The following code maps physical adress to the pointer
  //known as VideoMem
  uint s = (uint)(VideoAdress >> 4);  //this part obtains segment
  uint o = (uint)(VideoAdress & 0xF); //and this one the offset
  VideoMem = (uchar*)XVRMK_FP(s, o);
  return;
 }
 asm{
  mov ax, 0x0013
  int 0x10
 }
}

void closegraph(){
 asm{
  mov ax, 0x0003
  int 0x10
 }
}

void slowputpixel(int x, int y, unsigned char c){
 asm{
  mov ah, 0x0C
  mov bh, 0x00
  mov al, [c]
  mov cx, [x]
  mov dx, [y]
  int 0x10
 }
}

void fastputpixel(int x, int y, uchar c){
 uchar *memPtr;
 uint bank;
 ulong adress;
 adress = ((ulong)BytesPerLine) * y + x;
 bank = (uint)(adress >> 16);
 if(bank != CurBank){
  CurBank = bank;
  SetBank(bank);
 }
 memPtr = (uchar*)XVRMK_FP(0xA000, adress & 0xFFFFL);
 *memPtr = c;
}

void putpixel(int x, int y, uchar c, Bool usefast){
 if(x > 639) return;
 if(y > 479) return;
 if(x < 0) return;
 if(y < 0) return;
 if(c == 0) return;
 if(usefast){
  fastputpixel(x, y, c);
  return;
 }
 slowputpixel(x, y, c);
}

void setpalette(unsigned int c, char r, char g, char b){
 if(redbase < -63) redbase = -63;
 if(greenbase < -63) greenbase = -63;
 if(bluebase < -63) bluebase = -63;
 if(redbase > 63) redbase = 63;
 if(greenbase > 63) greenbase = 63;
 if(bluebase > 63) bluebase = 63;
 r += redbase;
 g += greenbase;
 b += bluebase;
 if(r < 0) r = 0;
 if(g < 0) g = 0;
 if(b < 0) b = 0;
 if(r > 63) r = 63;
 if(g > 63) g = 63;
 if(b > 63) b = 63;
 outport(0x3c8, c);
 outportb(0x3c9, r);
 outportb(0x3c9, g);
 outportb(0x3c9, b);
}

unsigned char TGAHdrData[4096];

typedef struct{
 short    NumOfBytInId;
 short    ColorMapType;
 short    ImageTypeCode;
 unsigned ColorMapOrigin;
 unsigned ColorMapLength;
 short    ColorMapEntrySize;
 unsigned XStart;
 unsigned YStart;
 unsigned Width;
 unsigned Height;
 short    PixelSize;
 short    ImageDescriptor;
 unsigned PaletteStart;
 unsigned DataStart;
}TGAHeader;

void DisplayTGAInfo(TGAHeader th, Bool disp = False);
void DisplayTGAInfo(TGAHeader th, Bool disp){
 if(disp){
  printf("\nNumOfBytInId: %u\n", th.NumOfBytInId);
  printf("ColorMapType: %u\n", th.ColorMapType);
  printf("ImageTypeCode: %u\n", th.ImageTypeCode);
  printf("ColorMapOrigin: %u\n", th.ColorMapOrigin);
  printf("ColorMapLength: %u\n", th.ColorMapLength);
  printf("ColorMapEntrySize: %u\n", th.ColorMapEntrySize);
  printf("XStart: %u\n", th.XStart);
  printf("YStart: %u\n", th.YStart);
  printf("Width: %u\n", th.Width);
  printf("Height: %u\n", th.Height);
  printf("PixelSize: %u\n", th.PixelSize);
  printf("ImageDescriptor: %u\n", th.ImageDescriptor);
  printf("PaletteStart: %u\n", th.PaletteStart);
  printf("DataStart: %u\n", th.DataStart);
 }
}

void GetTGAHeader(char *fname, TGAHeader *th){
 FILE *image;
 image = fopen(fname, "rb");
 fread(TGAHdrData, 786, 1, image);
 fclose(image);
 th->NumOfBytInId      = TGAHdrData[0];
 th->ColorMapType      = TGAHdrData[1];
 th->ImageTypeCode     = TGAHdrData[2];
 th->ColorMapOrigin    = TGAHdrData[3] + 256 * TGAHdrData[4];
 th->ColorMapLength    = TGAHdrData[5] + 256 * TGAHdrData[6];
 th->ColorMapEntrySize = TGAHdrData[7];
 th->XStart            = TGAHdrData[8] + 256 * TGAHdrData[9];
 th->YStart            = TGAHdrData[10] + 256 * TGAHdrData[11];
 th->Width             = TGAHdrData[12] + 256 * TGAHdrData[13];
 th->Height            = TGAHdrData[14] + 256 * TGAHdrData[15];
 th->PixelSize         = TGAHdrData[16];
 th->ImageDescriptor   = TGAHdrData[17];
 th->PaletteStart      = 18 + th->NumOfBytInId;
 th->DataStart         = 18 + th->NumOfBytInId + 3 * th->ColorMapLength;
}

void SetTGAPalette(TGAHeader th){
 int c;
 int i;
 unsigned char r, g, b;
 for(c = 1; c < 256; c++){
  i = c * 3;
  r = (TGAHdrData[th.PaletteStart + 2 + i]) >> 2;
  g = (TGAHdrData[th.PaletteStart + 1 + i]) >> 2;
  b = (TGAHdrData[th.PaletteStart + 0 + i]) >> 2;
  setpalette(c, r, g, b);
 }
}

void SaveMSH(char *fname, TGAHeader th){
 unsigned w, h;
 unsigned char r, g, b;
 register int i;
 register int c;
 void *pic;
 FILE *f;
 pic = XVRMK_FP(0xA000, 0x0);
 f = fopen(fname, "wb");
 w = th.Width;
 h = th.Height;
 fwrite(&w, sizeof(unsigned), 1, f);
 fwrite(&h, sizeof(unsigned), 1, f);
 for(c = 1; c < 256; c++){
  i = c * 3;
  r = (TGAHdrData[th.PaletteStart + 2 + i]) >> 2;
  g = (TGAHdrData[th.PaletteStart + 1 + i]) >> 2;
  b = (TGAHdrData[th.PaletteStart + 0 + i]) >> 2;
  if(r > 63) r = 63;
  if(g > 63) g = 63;
  if(b > 63) b = 63;
  if(r < 0) r = 0;
  if(g < 0) g = 0;
  if(b < 0) b = 0;
  fwrite(&r, 1, 1, f);
  fwrite(&g, 1, 1, f);
  fwrite(&b, 1, 1, f);
 }
 fwrite(pic, 1, 64000U, f);
 fclose(f);
}


void DisplayRLE_TGA(char *fname, TGAHeader th, int x, int y){
 int rad, kol, dir, i;
 char pakethdr;
 short int pakettyp;
 short int hdrnumber;
 short int rlecolor;
 FILE *image;
 image = fopen(fname, "rb");
 fseek(image, th.DataStart, SEEK_SET);
 if((th.ImageDescriptor&32)==32){
  rad = y;
  dir = 1;
 }
 else{
  rad = y + th.Height;
  dir =- 1;
 }
 kol = 0;
 while (!feof(image)){
  fread(&pakethdr, 1, 1, image);
  pakettyp = pakethdr & 128;
  hdrnumber = pakethdr & 127;
  if(pakettyp == 0){
   fread((void*)TGAHdrData, hdrnumber+1, 1, image);
   for(i = 0; i < hdrnumber + 1; i++){
    putpixel(x + kol, rad, TGAHdrData[i]);
    kol++;
    if((kol % th.Width == 0) && (kol != 0)){
     rad = rad + dir;
     kol = 0;
    }
   }
  }
  else{
   fread((void*)(&rlecolor), 1, 1, image);
   for(i = 0; i < hdrnumber + 1; i++){
    putpixel(x + kol, rad, rlecolor);
    kol++;
    if((kol % th.Width==0) && (kol!=0)) {
     rad = rad + dir;
     kol = 0;
    }
   }
  }
 }
 fclose(image);
}

void DisplayUncompTGA(char *fname, TGAHeader th, int x, int y){
 int i, j, rad;
 char *ImageData;
 FILE *image;
 ImageData = new char[th.Width];
 image = fopen(fname, "rb");
 fseek(image, th.DataStart, SEEK_SET);
 if((th.ImageDescriptor & 32) == 32){
  rad = y;
  for(i = y; i < (y + th.Height - 4); i++){
   fread((void*)ImageData, th.Width, 1, image);
   for(j = 0; j < th.Width; j++) putpixel(x + j, i, ImageData[j]);
  }
 }
 else{
  rad = y + th.Height - 4;
  for(i = rad; i > (rad - th.Height); i--){
   fread((void*)ImageData, th.Width, 1, image);
   for(j = 0; j < th.Width; j++) putpixel(x + j, i - 1, ImageData[j]);
  }
 }
 fclose(image);
 delete ImageData;
}

void fade(char *fname){
 int c;
 TGAHeader th;
 for(c = 0; c < 64; c++){
  redbase = c;
  bluebase = c;
  greenbase = c;
  GetTGAHeader(fname, &th);
  setpalette(0, c, c, c);
  SetTGAPalette(th);
  delay(10);
 }
 delay(25);
}

TGAHeader DisplayTGA(char *fname, char *mshfname){
 TGAHeader th;
 int k;
 GetTGAHeader(fname, &th);
 switch(th.ImageTypeCode){
  case 1:
   initgraph();
   SetTGAPalette(th);
   DisplayUncompTGA(fname, th, 0, 0);
   SaveMSH(mshfname, th);
   do{
    k = getch();
    if(k == '+'){
     redbase++;
     greenbase++;
     bluebase++;
    }
    if(k == '-'){
     redbase--;
     greenbase--;
     bluebase--;
    }
    if(k == 'r') redbase--;
    if(k == 'R') redbase++;
    if(k == 'g') greenbase--;
    if(k == 'G') greenbase++;
    if(k == 'b') bluebase--;
    if(k == 'B') bluebase++;
    if(k == 13){
     redbase = 0;
     bluebase = 0;
     greenbase = 0;
    }
    GetTGAHeader(fname, &th);
    SetTGAPalette(th);
   }while(k != 27);
   fade(fname);
   closegraph();
   break;
  case 9:
   initgraph();
   SetTGAPalette(th);
   DisplayRLE_TGA(fname, th, 0, 0);
   SaveMSH(mshfname, th);
   do{
    k = getch();
    if(k == '+'){
     redbase++;
     greenbase++;
     bluebase++;
    }
    if(k == '-'){
     redbase--;
     greenbase--;
     bluebase--;
    }
    if(k == 'r') redbase--;
    if(k == 'R') redbase++;
    if(k == 'g') greenbase--;
    if(k == 'G') greenbase++;
    if(k == 'b') bluebase--;
    if(k == 'B') bluebase++;
    if(k == 13){
     redbase = 0;
     bluebase = 0;
     greenbase = 0;
    }
    GetTGAHeader(fname, &th);
    SetTGAPalette(th);
   }while(k != 27);
   fade(fname);
   closegraph();
   break;
  default:
   printf("\nEl formato de esta imagen Targa no es\n");
   printf("compatible.\nTipo de imagen %u\n", th.ImageTypeCode);
   getch();
 }
 return th;
}

void main(int argc, char *argv[]){
 hic = 0;
 char fname[80];
 char mshfname[80];
 int tmp;
 TGAHeader info;
 if(argc < 3){
  printf("Archivo TGA: ");
  scanf("%s", &fname);
  printf("\n");
  printf("Convertir a MSH, entre el nombre del archivo: ");
  scanf("%s", &mshfname);
  printf("\n");
 }
 else{
  sprintf(fname, "%s", argv[1]);
  sprintf(mshfname, "%s", argv[2]);
 }
 FILE *test;
 redbase = 0;
 bluebase = 0;
 greenbase = 0;
 if(argc == 4){
  tmp = atoi(argv[3]);
  redbase = tmp;
  greenbase = tmp;
  bluebase = tmp;
 }
 test = fopen(fname, "rb");
 if(test == NULL){
  printf("\nArchivo no existe!!!\n");
  return;
 }
 fclose(test);
 info = DisplayTGA(fname, mshfname);
 textcolor(15);
 clrscr();
 DisplayTGAInfo(info);
}
