#include<bios.h>
#include<conio.h>
#include<string.h>
#include"c:\progra~1\borlandc\cpps\juan\jvgtools.h"

extern char JVGfondo;      //Identifica el color de fondo
extern char JVGpplano;     //Identifica el color de primer plano
extern char JVGselbar;     //Identifica el color de la barra de selecci¢n
extern char JVGseltxt;     //Identifica el color del texto seleccionado
extern char JVGmarco;      //Identifica si el marco es doble o sencillo
extern restaurar_colores();
extern void guardar_estado();
extern JVGtecla();
extern JVGmenu();
int JVGlastvmnui;

char JVGbuffer[1024];

int menu_vert(int x, int y, char *ops[], int n){
 Boolean flag = Falso;
 int i = 0, lasti = 0, key, max, tmp;
 max = strlen(ops[0]);
 for(i = 0; i < n; i++){
  tmp = strlen(ops[i]);
  if(tmp > max) max = tmp;
 }
 guardar_estado();
 _setcursortype(_NOCURSOR);
 JVGmenu();
 gettext(x, y, x + max + 1, y + n + 1, JVGbuffer);
 marco(x, y, x + max + 1, y + n + 1);
 textcolor(JVGpplano);
 textbackground(JVGfondo);
 for(i = 0; i < n; i++){
  gotoxy(x + 1, y + 1 + i);
  if(strcmp(ops[i], "@") != 0) cputs(ops[i]);
  else{
   gotoxy(x, wherey());
   if(!JVGmarco) putch('Ã');
   else putch('Ì');
   lineah(x + 1, x + max);
   if(!JVGmarco) putch('´');
   else putch('¹');
  }
 }
 i = 0;
 gotoxy(x + 1, y + 1 + i);
 marcar_texto(ops[i], max);
 do{
  key = bioskey(0);
  if((key & SC_ARRIBA) == SC_ARRIBA){
   i--;
   JVGtecla();
  }
  if((key & SC_ABAJO) == SC_ABAJO){
   i++;
   JVGtecla();
  }
  if(i >= n) i = 0;
  if(i < 0) i = n - 1;
  tmp = strcmp(ops[i], "@");
  if(tmp == 0){
   if((key & SC_ARRIBA) == SC_ARRIBA) i--;
   if((key & SC_ABAJO) == SC_ABAJO) i++;
  }
  gotoxy(x + 1, y + 1 + lasti);
  desmarcar_texto(ops[lasti], max);
  gotoxy(x + 1, y + 1 + i);
  marcar_texto(ops[i], max);
  lasti = i;
  if(((key & SC_ESC)== SC_ESC) || ((key & SC_IZQ)== SC_IZQ) ||
			    ((key & SC_DER)== SC_DER)) flag = Verdadero;
 }while(((key & SC_ENTER) != SC_ENTER) && (flag == Falso));
 puttext(x, y, x + max + 1, y + n + 1, JVGbuffer);
 _setcursortype(_NORMALCURSOR);
 restaurar_colores();
 if(!flag) return i;
 return -1;
}

int calculate_xpos(char *ops[], int i){
 int x, j;
 x = 0;
 for(j = 0; j < i; j++) x+=strlen(ops[j]);
 return x + 1;
}


int menu_horz(int fila, char *ops[], int n){
 int i, max = 0, key, lasti = 0;
 guardar_estado();
 textcolor(JVGpplano);
 textbackground(JVGfondo);
 _setcursortype(_NOCURSOR);
 gotoxy(1, fila);
 printchars(32, 80);
 gotoxy(1, fila);
 for(i = 0; i < n; i++){
  max = max + strlen(ops[i]);
  if(max <= 80) cputs(ops[i]);
  else{
   n = i - 1;
   break;
  }
 }
 if(JVGlastvmnui >= n) JVGlastvmnui = 0;
 i = JVGlastvmnui;
 lasti = JVGlastvmnui;
 gotoxy(calculate_xpos(ops, i), fila);
 marcar_texto(ops[i], strlen(ops[i]));
 do{
  key = bioskey(0);
  if((key & SC_IZQ) == SC_IZQ){
   i--;
   JVGtecla();
  }
  if((key & SC_DER) == SC_DER){
   i++;
   JVGtecla();
  }
  if(i >= n)  i = 0;
  if(i < 0) i = n - 1;
  gotoxy(calculate_xpos(ops, lasti), fila);
  desmarcar_texto(ops[lasti], strlen(ops[lasti]));
  gotoxy(calculate_xpos(ops, i), fila);
  marcar_texto(ops[i], strlen(ops[i]));
  lasti = i;
 }while(((key & SC_ENTER)!= SC_ENTER) && ((key & SC_ABAJO) != SC_ABAJO));
 gotoxy(calculate_xpos(ops, i), fila);
 desmarcar_texto(ops[i], strlen(ops[i]));
 _setcursortype(_NORMALCURSOR);
 restaurar_colores();
 JVGlastvmnui = i;
 return i;
}
