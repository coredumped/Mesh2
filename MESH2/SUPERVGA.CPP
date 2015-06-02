//--------------------------------------------------------------------------
// VESA.cpp
//
//    Programa que verifica la disponibilidad de una tarjeta VESA
//
//                                                      Juan V. Guerrero
//--------------------------------------------------------------------------
#include<dos.h>
#include"supervga.h"

unsigned VESA_CurBank;

VESAModeInfo _SVGAModeInfo;


int GetVESAModeInfo(VESAModeInfo *info, unsigned mode){
 REGS regs;
 REGS outregs;
 SREGS sregs;
 regs.x.ax = 0x4F01;
 regs.x.cx = mode;
 regs.x.di = FP_OFF(info);
 sregs.es = FP_SEG(info);
 int86x(0x10, &regs, &outregs, &sregs);
 return (outregs.h.ah == 0)?1:0;
}

int GetSVGAInfo(SVGAInfo *info){
 REGS regs, outregs;
 SREGS sregs;
 regs.x.ax = 0x4F00;
 sregs.es = FP_SEG(&info);
 regs.x.di = FP_OFF(&info);
 int86x(0x10, &regs, &outregs, &sregs);
 return (outregs.h.ah == 0)?1:0;
}

int SetSVGAMode(unsigned mode){
 unsigned char status;
 if(!GetVESAModeInfo(&_SVGAModeInfo, mode)) return 0;
 asm{
  mov ax, 0x4F02
  mov bx, [mode]
  int 0x10
  mov [status], ah
 }
 return (status == 0)?1:0;
}

unsigned GetSVGAMode(){
 unsigned char status;
 unsigned mode;
 asm{
  mov ax, 0x4F03
  int 0x10
  mov [status], ah
  mov [mode], bx
 }
 if(status != 0) return 0;
 return mode;
}

void SetBank(unsigned bank){
 asm{
  mov ax, 0x4F05
  xor bh, bh
  mov dx, [bank]
  xor bl, bl
  int 0x10
 }
}

void SVGAputpixel(int x, int y, unsigned char color){
 unsigned char *VidMem;
 unsigned long adress;
 unsigned bank;
 if(x < 0) return;
 if(x >= _SVGAModeInfo.width) return;
 if(y < 0) return;
 if(y >= _SVGAModeInfo.height) return;
 adress = (unsigned long)(x + y * (unsigned long)_SVGAModeInfo.bperscanline);
 bank = (unsigned)(adress >> 16);
 if(bank != VESA_CurBank){
  VESA_CurBank = bank;
  SetBank(bank);
 }
 VidMem = (unsigned char*)MK_FP(0xA000, adress & 0xFFFFL);
 *VidMem = color;
}

int SVGAgetmaxx(){
 return _SVGAModeInfo.width;
}

int SVGAgetmaxy(){
 return _SVGAModeInfo.height;
}