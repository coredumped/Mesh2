//---------------------------------------------------------------------------
//  GUI.cpp
//
//  ver 1.0
//     M¢dulo encargado de la interfaz gr fica de usuario
//                                                       Juan V. Guerrero
//                                                                 1998
//---------------------------------------------------------------------------
#include<bios.h>
#include<stdio.h>
#include<graphics.h>
#include<string.h>
#include<conio.h>
#include<string.h>
#include "scancode.h"
#include "mesh.h"
#include "mouse.h"
#include "gui.h"

void DrawPanel(int l, int t, int r, int b, int tipo){
 int shadow = 8, light = 15;
 if(tipo == HUNDIDO){
  shadow = 15;
  light = 8;
 }
 setcolor(light);
 line(r, t, l, t);
 line(l, t, l, b);
 setcolor(shadow);
 line(l, b, r, b);
 line(r, b, r, t);
}

void DrawWindow(int x, int y, int r, int b, char *title){
 DrawPanel(x, y, r, b, ELEVADO);
 setfillstyle(SOLID_FILL, 1);
 bar(x + 5, y + 2, r - 3, y + 2 + textheight(title));
 setcolor(15);
 outtextxy(x + 2, y + 2, title);
}

void DrawMeshWindow(){
 setfillstyle(SOLID_FILL, 7);
 bar(0, 0, 639, 349);
 setfillstyle(SOLID_FILL, EGA_BLACK);
 bar(3, 13, 483, 263);
 DrawPanel(0, 0, 639, 349, ELEVADO);
 setfillstyle(SOLID_FILL, 7);
 bar(1, 1, 638, 10);
 setfillstyle(SOLID_FILL, 1);
 bar(4, 1, 635, 10);
 setcolor(15);
 outtextxy(8, 2, "Mesh II");
 line(638, 11, 1, 11);
 line(1, 11, 1, 348);
 setcolor(8);
 line(1, 348, 638, 348);
 line(638, 348, 638, 11);
 DrawPanel(483, 13, 637, 347, HUNDIDO);
 DrawPanel(3, 263, 482, 347, ELEVADO);
}

void CreateButton(int x, int y, Button *btn, char *caption){
 btn->x = x;
 btn->y = y;
 strcpy(btn->caption, caption);
 btn->r = textwidth(caption) + 10 + x;
 btn->b = textheight(caption) + 6 + y;
 btn->status = ELEVADO;
}

void DrawButton(Button btn){
 DrawPanel(btn.x, btn.y, btn.r, btn.b, btn.status);
 setcolor(EGA_BLACK);
 outtextxy(btn.x + 5, btn.y + 3, btn.caption);
}

int CheckIfPressed(Button *btn){
 int x, y, b;
 GetMouseStatus(&x, &y, &b);
 if(b == 1){
  if(((x >= btn->x) && (x <= btn->r)) && ((y >= btn->y) && (y <= btn->b)))
   btn->status = HUNDIDO;
  else
   btn->status = ELEVADO;
 }
 else
  btn->status = ELEVADO;
 return btn->status;
}

void Message(char *title, char *msg){
 int x, r, w, ok = 1;
 Button btn;
 w = textwidth(msg) + 18;
 x = 320 - w / 2;
 r = x + w - 1;
 CreateButton(320 - (textwidth("Aceptar") >> 1) - 5, 195, &btn, "Aceptar");
 do{
  setfillstyle(SOLID_FILL, 7);
  bar(x, 160, r, 215);
  DrawWindow(x, 160, r, 215, title);
  setcolor(EGA_BLACK);
  outtextxy(x + 9, 176, msg);
  CheckIfPressed(&btn);
  DrawButton(btn);
  UpdateCursor();
  if(btn.status == HUNDIDO){
   DrawButton(btn);
   UpdateCursor();
  }
  flippage();
  while(btn.status == HUNDIDO){
   CheckIfPressed(&btn);
   ok = 0;
  }
 }while(ok);
}

void CreateTab(int x, int y, Button *btn, char *caption){
 btn->x = x;
 btn->y = y;
 strcpy(btn->caption, caption);
 settextstyle(DEFAULT_FONT, VERT_DIR, 1);
 btn->r =  textheight(caption) + 10 + x;
 btn->b =  textwidth(caption) + 10 + y;
 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
 btn->status = ELEVADO;
}

void DrawTab(Button btn){
 DrawPanel(btn.x, btn.y, btn.r, btn.b, ELEVADO);
 setcolor(7);
 line(btn.x, btn.y, btn.x, btn.b);
 settextstyle(DEFAULT_FONT, VERT_DIR, 1);
 setcolor(EGA_BLACK);
 outtextxy(btn.x + 13, btn.y + 5, btn.caption);
 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
}

int MeshFxyPanel(int active){
 Button Fxy[MAXFXY];
 int i, y;
 char text[12];
 if(!active) return -1;
 y = 30;
 setfillstyle(SOLID_FILL, 7);
 bar(499, y - 1, 600, y + MAXFXY * 15);
 DrawPanel(499, y - 1, 600, y + MAXFXY * 15, HUNDIDO);
 for(i = 0; i < MAXFXY; i++){
  sprintf(text, "Funci¢n #%2d", i + 1);
  CreateButton(500, y, &Fxy[i], text);
  y += 15;
  DrawButton(Fxy[i]);
 }
 for(i = 0; i < MAXFXY; i++){
  CheckIfPressed(&Fxy[i]);
  if(Fxy[i].status == HUNDIDO){
   DrawButton(Fxy[i]);
   UpdateCursor();
   return i;
  }
 }
 return -1;
}

int MeshTabPanel(Button Tab){
 CheckIfPressed(&Tab);
 if(Tab.status == HUNDIDO) return 1;
 return 0;
}

void DrawCommandPanel(int x, int y, int r, int b, Button Tab, int isactive){
 DrawPanel(x, y, r, b, ELEVADO);
 DrawTab(Tab);
 if(isactive){
  setcolor(8);
  line(r, Tab.y, r, y);
  line(r, Tab.b, r, b);
 }
}

int MeshOptionPanel(int active){
 Button command[13];
 register int i;
 CreateButton(495, 30,  &command[0],  "Eje: X+");
 CreateButton(495, 45,  &command[1],  "Eje: X-");
 CreateButton(495, 60,  &command[2],  "Eje: Y+");
 CreateButton(495, 75,  &command[3],  "Eje: Y-");
 CreateButton(495, 90,  &command[4],  "Eje: Z+");
 CreateButton(495, 105, &command[5],  "Eje: Z-");
 CreateButton(495, 120, &command[12], "Detener");
 CreateButton(495, 160, &command[6],  "Eje: X+");
 CreateButton(495, 175, &command[7],  "Eje: X-");
 CreateButton(495, 190, &command[8],  "Eje: Y+");
 CreateButton(495, 205, &command[9],  "Eje: Y-");
 CreateButton(495, 220, &command[10], "Eje: Z+");
 CreateButton(495, 235, &command[11], "Eje: Z-");
 if(!active) return -1;
 setfillstyle(SOLID_FILL, 7);
 bar(499, 31, 600, 236);
 setcolor(0);
 outtextxy(493, 19, "Rotaci¢n");
 outtextxy(493, 145, "Traslaci¢n");
 DrawPanel(494, 29, 562, 135, HUNDIDO);
 DrawPanel(494, 159, 562, 250, HUNDIDO);
 for(i = 0; i < 13; i++)
  DrawButton(command[i]);
 for(i = 0; i < 13; i++){
  CheckIfPressed(&command[i]);
  if(command[i].status == HUNDIDO){
   DrawButton(command[i]);
   UpdateCursor();
   return i;
  }
 }
 return -1;
}


void FixStr(char *str){
 int len;
 len = strlen(str);
 str[len - 1] = '\0';
}


void MeshHelp(){
 int flag = 1, y, key;
 static char hlpline[80];
 char *errmsg = "ERROR - MeshII.Hlp no existe";
 FILE *f;
 Button salir;
 CreateButton(4, 14, &salir, "Salir");
 setactivepage(0);
 setvisualpage(0);
 setfillstyle(SOLID_FILL, 7);
 bar(0, 0, 639, 349);
 DrawWindow(0, 0, 639, 349, " MeshII - Ayuda");
 setfillstyle(SOLID_FILL, 15);
 bar(3, 30, 636, 346);
 DrawPanel(3, 30, 636, 346, HUNDIDO);
 DrawButton(salir);
 f = fopen("MeshII.hlp", "rt");
 if(f != NULL){
  y = 34;
  while(fgets(hlpline, 90, f)){
   FixStr(hlpline);
   outtextxy(9, y, hlpline);
   y += textheight(hlpline);
  }
  fclose(f);
 }
 else{
  settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
  outtextxy(320 - textwidth(errmsg)/2, 175 - textheight(errmsg) / 2, errmsg);
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
 }
 ShowMouse();
 do{
  CheckIfPressed(&salir);
  if(salir.status == HUNDIDO){
   HideMouse();
   DrawButton(salir);
   ShowMouse();
   while(CheckIfPressed(&salir));
   flag = 0;
  }
  if(bioskey(1)) key = bioskey(0);
  if(key == SC_ESC) flag = 0;
 }while(flag);
 HideMouse();
 flippage();
}