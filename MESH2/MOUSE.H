//--------------------------------------------------------------------------
//  Mouse.h
//     Declaraciones de funciones y varibles globales para usar el rat¢n
//
//                                                Juan V. Guerrero   1998
//--------------------------------------------------------------------------
#ifndef _MOUSE_H
#define _MOUSE_H

extern int IsMousePresent();
extern void ShowMouse();
extern void HideMouse();
extern void GetMouseStatus(int *x, int *y, int *button);
extern void UpdateCursor();
extern int getmousebutton();

#endif
