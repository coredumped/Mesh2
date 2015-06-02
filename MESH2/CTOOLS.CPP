/*++<TITULO>++*/
//JVG's Tools for C 1.0
/*++<INTRO>

     Codigo fuente escrito en C que adiciona funciones para utilizar menus
  desplegables y menus horizontales.

++*/

#include<bios.h>
#include<conio.h>
#include<string.h>
#include"c:\progra~1\borlandc\cpps\juan\jvgtools.h"

//  Ú Â ¿        É Ë »     þ ° ± ² Û Ü ß
//Ä³ ÃÅ´       Íº ÌÎ¹       © ¸ ñ ^ ½ ô
//  À Á Ù        È Ê ¼     « ¬ ó ž ® ¯ õ

/*++<VARIABLES GLOBALES{>++*/
char JVGfondo;      //Identifica el color de fondo
char JVGpplano;     //Identifica el color de primer plano
char JVGselbar;     //Identifica el color de la barra de selecci¢n
char JVGseltxt;     //Identifica el color del texto seleccionado
char JVGmarco;      //Identifica si el marco es doble o sencillo
char fondoact;      //Guarda el color del fondo seleccionado por
		    //textbackground
char pplanoact;     //Guarda el color del primer plano seleccionado por
		    //textcolor
char JVGmarcf;	    //Especifica el color de fondo de los marcos
char JVGmarcb;      //Identifica el color del borde de los marcos
extern int JVGlastvmnui;
struct text_info tinf;
/*++<}VARIABLES GLOBALES>++*/

/*++<FUNCION{>++*/
//----------------------------------------------------------------------------
//<DECLARACION{>
// void printchars(char c, int n);
//<}DECLARACION>
//<DESCRIPCION{>
//   Esta funci¢n muestra una cantidad n de caracteres previamente dados por
// el programador.
//   Para esta operaci¢n rellenamos imprimimos multiples veces el caracter
// ha mostrar, haciendo uso de la funci¢n putch.
//<}DESCRIPCION>
//<ARGUMENTOS{>
// <char c>: especifica que letras se imprimiran
//
// <int n>:  especifica cuantas veces se repetir  la letra
//<}ARGUMENTOS>
//----------------------------------------------------------------------------
void printchars(char c, int n){
 int i;
 for(i = 0; i < n; i++) putch(c);
}
/*++<}FUNCION>++*/

/*++<FUNCION{>++*/
//----------------------------------------------------------------------------
//<DECLARACION{>
// void lineah(int x1, int x2);
//<}DECLARACION>
//<DESCRIPCION{>
//   La funci¢n lineah dibuja una l¡nea horizontal en la columna x1 y fila
// actual, la linea puede ser sencilla o doble, esto se especifica al
// seleccionar si se utiliza o no un marco doble.
//   Para llevar a cabo esta tarea la funci¢n hace uso de la rutina
// printchars.
//<}DESCRIPCION>
//<ARGUMENTOS{>
// <int x1>:  coordenada x inicial para dibujar la linea
// <int x2>:  coordenada x final para dibujar la linea
//<}ARGUMENTOS>
//----------------------------------------------------------------------------
void lineah(int x1, int x2){
 gotoxy(x1, wherey());
 if(!JVGmarco) printchars('Ä', x2 - x1 + 1);
 else printchars('Í', x2 - x1 + 1);
}
/*++<}FUNCION>++*/

void ajustarmarco(int m){
 JVGmarco = m;
}

void guardar_estado(){
 gettextinfo(&tinf);
 fondoact = tinf.attribute >> 4;
 pplanoact = (fondoact << 4)^ tinf.attribute;
}

void guardar_ventana(){
 gettextinfo(&tinf);
}

void restaurar_ventana(){
 window(tinf.winleft, tinf.wintop, tinf.winright, tinf.winbottom);
 gotoxy(tinf.curx, tinf.cury);
}

void restaurar_colores(){
 textcolor(pplanoact);
 textbackground(fondoact);
}

void marco(int x1, int y1, int x2, int y2){
 int y;
 if(x1 > x2){
  y = x1;
  x1 = x2;
  x2 = y;
 }
 if(y1 > y2){
  y = y1;
  y1 = y2;
  y2 = y;
 }
 gotoxy(x1, y1);
 textcolor(JVGmarcb);
 textbackground(JVGmarcf);
 if(!JVGmarco) cprintf("Ú");
 else cprintf("É");
 lineah(x1 + 1, x2 - 1);
 if(!JVGmarco) cprintf("¿\n\r");
 else cprintf("»\n\r");
 for(y = y1 + 1; y < y2; y++){
  gotoxy(x1, y);
  if(!JVGmarco) cprintf("³");
  else cprintf("º");
  printchars(32, x2 - x1 - 1);
  if(!JVGmarco) cprintf("³");
  else cprintf("º");
 }
 gotoxy(x1, y2);
 if(!JVGmarco) cprintf("À");
 else cprintf("È");
 lineah(x1 + 1, x2 - 1);
 if(!JVGmarco) cprintf("Ù\n\r");
 else cprintf("¼\n\r");
}

void ajustarcolores(int fondo, int primerplano, int seleccionado, int seltexto){
 JVGfondo = fondo;
 JVGpplano = primerplano;
 JVGselbar = seleccionado;
 JVGseltxt = seltexto;
}

void marcar_texto(char *txt, int largo){
 int x;
 x = wherex();
 textcolor(JVGseltxt);
 textbackground(JVGselbar);
 printchars(32, largo);
 gotoxy(x, wherey());
 cprintf("%s", txt);
}

void desmarcar_texto(char *txt, int largo){
 int x;
 x = wherex();
 textcolor(JVGpplano);
 textbackground(JVGmarcf);
 printchars(32, largo);
 gotoxy(x, wherey());
 cprintf("%s", txt);
}

void iniciar_herram(){
 textmode(C4350);
 guardar_estado();
 ajustarcolores(1, 15, 14, 0);
 m_borde(15);
 m_fondo(1);
 JVGlastvmnui = 0;
}

void m_borde(int b){
 JVGmarcb = b;
}

void m_fondo(int f){
 JVGmarcf = f;
}

