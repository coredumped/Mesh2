//--------------------------------------------------------------------------
//  Mouse.cpp
//
//     Este m¢dulo contiene las funciones necesarias para tener acceso
//   al uso del rat¢n utilizando rutinas escritas en assembler.
//
//                                                  Juan V. Guerrero   1998
//--------------------------------------------------------------------------
#include<alloc.h>
#include<graphics.h>
#include<stdlib.h>
#include"mesh.h"
#include"mouse.h"

int IsMousePresent(){
 int isAlive;
 asm{
  mov ax, 0x0000
  int 0x33
  mov [isAlive], ax
 }
 return isAlive;
}

void ShowMouse(){
 asm{
  mov ax, 0x0001
  int 0x33
 }
}

void HideMouse(){
 asm{
  mov ax, 0x0002
  int 0x33
 }
}

void GetMouseStatus(int *x, int *y, int *button){
 int mx, my, mb;
 asm{
  mov ax, 0x0003
  int 0x33
  mov [mb], bx;
  mov [mx], cx;
  mov [my], dx;
 }
 *button = mb;
 *x = mx;
 *y = my;
}

void DrawCursor(int x, int y){
 static poly[8];
 setcolor(2);
 setfillstyle(SOLID_FILL, 2);
 poly[0] = x;
 poly[1] = y;
 poly[2] = x + 10;
 poly[3] = y + 5;
 poly[4] = x + 6;
 poly[5] = y + 6;
 poly[6] = x + 5;
 poly[7] = y + 10;
 fillpoly(4, poly);
}

void UpdateCursor(){
 int x, y, temp;
 GetMouseStatus(&x, &y, &temp);
 DrawCursor(x, y);
}

int getmousebutton(){
 int x, y, b;
 GetMouseStatus(&x, &y, &b);
 return b;
}