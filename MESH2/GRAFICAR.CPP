//------------------------------------------------------------------------
//  3-D Engine
//
//     Motor para graficos 3-D
//  ver 1.0                                       Juan V. Guerrero   1998
//------------------------------------------------------------------------
#include<dos.h>
#include<mem.h>
#include<stdio.h>

void ajustarpaleta(unsigned int c, char r, char g, char b){
 asm{
  mov ax, [c]
  mov dx, 0x03c8
  out dx, al
  mov al, [r]
  mov dx, 0x03c9
  out dx, al
  mov al, [g]
  mov dx, 0x03c9
  out dx, al
  mov al, [b]
  mov dx, 0x03c9
  out dx, al
 }
}

void iniciarModo13(){
 asm mov ax, 0x0013
 asm int 0x10
}

void modoTexto(){
 asm mov ax, 0x0003
 asm int 0x10
}

int cargarMSH(char *fname){
 void *pic = MK_FP(0xA000, 0x0);
 unsigned w, h;
 register int c;
 unsigned char r, g, b;
 FILE *f;
 f = fopen(fname, "rb");
 memset(pic, '\0', 64000);
 if(f == NULL) return 0;
 fread(&w, sizeof(unsigned), 1, f);
 fread(&h, sizeof(unsigned), 1, f);
 for(c = 1; c < 256; c++){
  fread(&r, 1, 1, f);
  fread(&g, 1, 1, f);
  fread(&b, 1, 1, f);
  ajustarpaleta(c, r, g, b);
 }
 fread(pic, 1, 64000, f);
 fclose(f);
 return 1;
}

float xxxtemp, lastxxxtemp, lastx;
Point2d c3dto2d(Point3d p, float horihi, float wide, float divi){
 Point2d punto;
 if(x == 0){
  punto.x = p.y;
  punto.y = p.z;
  return punto;
 }
 if(x == lastx){
  xxxtemp = lastxxxtemp;
 }
 else{
  if(x > 0) xxxtemp = xxIrel[(int)(x * 2)];
  else{
   xxxtemp = 1 - pow(divi, p.x);
  }
 }
 punto.x = p.y + xxxtemp * (wide - p.y);
 punto.y = p.z + xxxtemp * (horihi - p.z);
 lastx = p.x;
 lastxxxtemp = xxxtemp;
 return(punto);
}

Point3d rotate(Point3d o, Point3d *p, float theta, float alpha){
 float xt, yt, zt, ct, st;
 xt = *p.x;
 yt = *p.y;
 zt = *p.z;
 ct = cos(theta);
 st = sin(theta);
 *p.x = xt * ct + yt * st + o.x;
 *p.y = yt * ct + xt * st + o.y;
 *p.z = zt * cos(alpha) + sqrt(xt * xt + yt * yt) * sin(alpha) + o.z;
 return *p;
}

