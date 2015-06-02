//--------------------------------------------------------------------------
// SuperVGA.h
//
//     Cabecera que contiene los prototipos de las funciones que han
//  de utilizar los modos de video Super VGA compatibles con VESA
// ver 1.0
//                                                         Juan V. Guerrero
//                                                              1998
//--------------------------------------------------------------------------

typedef struct{
 char signature[4];
 unsigned char version_me;
 unsigned char version_ma;
 void far *oem;
 char caps[4];
 void far *modelist;
 char res[238];
}SVGAInfo;

typedef struct{
 unsigned atributos;
 unsigned char WinAAttr;
 unsigned char WinBAttr;
 unsigned granularidad;
 unsigned WinSize;
 unsigned WinAseg;
 unsigned WinBseg;
 void far *func;
 unsigned bperscanline;
 unsigned width;
 unsigned height;
 unsigned char charheight;
 unsigned char charwidth;
 unsigned char memplanes;
 unsigned char bitsperpixel;
 unsigned char banks;
 unsigned char memmodel;
 unsigned char banksize;
}VESAModeInfo;

extern int SVGAgetmaxy();
extern int SVGAgetmaxx();
extern void SVGAputpixel(int x, int y, unsigned char color);
extern int SetSVGAMode(unsigned mode);
extern int GetVESAModeInfo(VESAModeInfo *info, unsigned mode);
extern int GetSVGAInfo(SVGAInfo *info);
