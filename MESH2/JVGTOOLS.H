/*++<TITLE>++*/
//JVG's Tools for C 1.0
/*++<INTRO>

     Archivo de cabecera que contiene las declaraciones de funciones y
defines necesarios para trabajar con con las herramientas de extensi¢n
de C.

++*/
#include<stdio.h>
#ifndef JVGTOOLS_H
#define JVGTOOLS_H
#define MARCO_DOBLE    1
#define MARCO_SENCILLO 0
#define SC_IZQ     0x4B00
#define SC_DER     0x4D00
#define SC_ARRIBA  0x4800
#define SC_ABAJO   0x5000
#define SC_ESC     0x011B
#define SC_ENTER   0x1C0D
#define SC_F1      0x3B00
#define SC_F2      0x3C00
#define SC_F3      0x3D00
#define SC_F4      0x3E00
#define SC_F5      0x3F00
#define SC_F6      0x4000
#define SC_F7      0x4100
#define SC_F8      0x4200
#define SC_F9      0x4300
#define SC_F10     0x4400
#define SC_F11     0x8500
#define SC_F12     0x8600
#define SC_PGUP    0x4900
#define SC_PGDN    0x5100
#define SC_INS     0x5200
#define SC_DEL     0x5300
#define SC_INICIO  0x4700
#define SC_FIN     0x4F00
#define SC_TAB     0x0F00

enum Boolean {Verdadero = 1, Falso = 0, True = 1, False = 0};

extern void ajustarcolores(int fondo, int primerplano, int seleccionado, int seltexto);
extern void ajustarmarco(int m);
extern void m_borde(int b);
extern void m_fondo(int f);
extern void marco(int x1, int y1, int x2, int y2);
extern void marcar_texto(char *txt, int largo);
extern void desmarcar_texto(char *txt, int largo);
extern void printchars(char c, int n);
extern void lineah(int x1, int x2);
extern int menu_horz(int fila, char *ops[], int n);
extern int menu_vert(int x, int y, char *ops[], int n);
extern void guardar_estado();
void iniciar_herram();
void errormsg(char *title, char *msg);
Boolean jvg_message(char *title, char *msg);
Boolean jvg_fexist(char *fn);
FILE *jvg_fopen(char *fn, char *type);
char *jvg_fbuscar(char *fn);
int jvg_fscanf(FILE *fp, char *fmt, ...);
int jvg_scanf(char *title, char *prompt, char *fmt, ...);
char *jvg_fgets(char *s, int n, FILE *f);
#endif

