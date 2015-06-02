#include<bios.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<stdarg.h>
#include"c:\progra~1\borlandc\cpps\juan\jvgtools.h"
extern restaurar_colores();
extern char JVGmarcf;	    //Especifica el color de fondo de los marcos
extern char JVGmarcb;      //Identifica el color del borde de los marcos
extern char JVGpplano;     //Identifica el color de primer plano
extern char JVGmarco;
extern void guardar_ventana();
extern void restaurar_ventana();
extern void JVGalarma();
extern char JVGbuffer[];
extern void playspksnd(char *fname);
extern int  calculate_xpos(char *ops[], int i);
extern JVGtecla();
extern void msg_snd();
extern void error_snd();

Boolean aceptar_cancelar(){
 int  i = 0, lasti = 0, key, fila = wherey(), x = wherex();
 char *buttons[] = {" Aceptar ", " Cancelar "};
 gotoxy(x + 1, fila);
 cputs(" Aceptar  Cancelar ");
 gotoxy(x + calculate_xpos(buttons, i), fila);
 marcar_texto(buttons[i], strlen(buttons[i]));
 msg_snd();
 do{
  key = bioskey(0);
  if((key & SC_IZQ) == SC_IZQ){
   i--;
   if((i>=0)&&(i<=1))JVGtecla();
  }
  if((key & SC_DER) == SC_DER){
   i++;
   if((i>=0)&&(i<=1))JVGtecla();
  }
  if(i >= 2)  i = 1;
  if(i < 0) i = 0;
  gotoxy(x + calculate_xpos(buttons, lasti), fila);
  desmarcar_texto(buttons[lasti], strlen(buttons[lasti]));
  gotoxy(x + calculate_xpos(buttons, i), fila);
  marcar_texto(buttons[i], strlen(buttons[i]));
  lasti = i;
 }while(((key & SC_ENTER)!= SC_ENTER) && ((key & SC_ABAJO) != SC_ABAJO));
 gotoxy(x + calculate_xpos(buttons, i), fila);
 desmarcar_texto(buttons[i], strlen(buttons[i]));
 _setcursortype(_NORMALCURSOR);
 if(i == 0) return Verdadero;
 return Falso;
}


Boolean jvg_message(char *title, char *msg){
 int x, y, h = 5, w, i, len, m, bb, bf;
 Boolean ret = False;
 w = 20 + strlen(title);
 len = 5;
 for(i = 0; i < strlen(msg); i++){
  if((msg[i] == '\n')&&(msg[i+1] == '\r')){
   h++;
   len = 0;
   i++;
  }
  if(len > w) w = len;
  len++;
 }
 x = (80 - w) / 2;
 y = (50 - h) / 2;
 guardar_estado();
 guardar_ventana();
 bf = JVGmarcf;
 bb = JVGmarcb;
 m = JVGmarco;
 m_borde(14);
 m_fondo(1);
 ajustarmarco(MARCO_DOBLE);
 gettext(x, y, x + w - 1, y + h - 1, JVGbuffer);
 marco(x, y, x + w - 1,y + h - 1);
 _setcursortype(_NOCURSOR);
 gotoxy(x + 1, y);
 cputs("(ž)");
 cputs(title);
 window(x + 2, y + 1, x + w, y + h - 2);
 cputs("\n\r");
 cputs(msg);
 restaurar_ventana();
 gotoxy(x + w/2 - 10, y + h - 2);
 m_borde(bb);
 m_fondo(bf);
 ajustarmarco(m);
 ret = aceptar_cancelar();
 _setcursortype(_NORMALCURSOR);
 restaurar_colores();
 puttext(x, y, x + w - 1, y + h - 1, JVGbuffer);
 return ret;
}

void errormsg(char *title, char *msg){
 int h = 3, w, i, len, bb, bf, m, x, y;
 w = 6 + strlen(title);
 len = 3;
 for(i = 0; i < strlen(msg); i++){
  if((msg[i] == '\n')&&(msg[i+1] == '\r')){
   h++;
   len = 0;
   i++;
  }
  if(len > w) w = len;
  len++;
 }
 x = (80 - w) / 2;
 y = (50 - h) / 2;
 guardar_estado();
 guardar_ventana();
 bf = JVGmarcf;
 bb = JVGmarcb;
 m = JVGmarco;
 m_borde(15);
 m_fondo(4);
 ajustarmarco(MARCO_DOBLE);
 gettext(x, y, x + w - 1, y + h - 1, JVGbuffer);
 marco(x, y, x + w - 1,y + h - 1);
 _setcursortype(_NOCURSOR);
 m_borde(bb);
 m_fondo(bf);
 gotoxy(x + 1, y);
 cputs("(ž)");
 cputs(title);
 window(x + 1, y + 1, x + w, y + h);
 textcolor(15);
 textbackground(4);
 cputs(msg);
 error_snd();
 getch();
 _setcursortype(_NORMALCURSOR);
 restaurar_ventana();
 restaurar_colores();
 puttext(x, y, x + w - 1, y + h - 1, JVGbuffer);
 ajustarmarco(m);
}


int jvg_scanf(char *title, char *prompt, char *fmt, ...){
 int cnt;
 int x, y, h = 8, w, i, len, m, bb, bf;
 va_list  argptr;
 w = 20 + strlen(title);
 len = 5;
 for(i = 0; i < strlen(prompt); i++){
  if((prompt[i] == '\n')&&(prompt[i+1] == '\r')){
   h++;
   len = 0;
   i++;
  }
  if(len > w) w = len;
  len++;
 }
 x = (80 - w) / 2;
 y = (50 - h) / 2;
 guardar_estado();
 guardar_ventana();
 bf = JVGmarcf;
 bb = JVGmarcb;
 m = JVGmarco;
 m_borde(14);
 m_fondo(1);
 ajustarmarco(MARCO_DOBLE);
 gettext(x, y, x + w - 1, y + h - 1, JVGbuffer);
 marco(x, y, x + w - 1,y + h - 1);
 gotoxy(x + 1, y);
 cputs("(ž)");
 cputs(title);
 window(x + 2, y + 1, x + w, y + h - 2);
 cputs(prompt);
 ajustarmarco(m);
 restaurar_ventana();
 marco(x + 1, y + h - 4, x + w - 2, y + h - 2);
 gotoxy(x + 2, y + h - 3);
 va_start(argptr, fmt);
 cnt = vscanf(fmt, argptr);
 va_end(argptr);
 fflush(stdin);
 m_borde(bb);
 m_fondo(bf);
 restaurar_colores();
 puttext(x, y, x + w - 1, y + h - 1, JVGbuffer);
 return cnt;
}

Boolean jvg_xmessage(char *title, char *msg, char *fmt, ...){
 int x, y, h = 5, w, i, len, m, bb, bf;
 va_list  argptr;
 Boolean ret = False;
 w = 20 + strlen(title);
 len = 5;
 for(i = 0; i < strlen(msg); i++){
  if((msg[i] == '\n')&&(msg[i+1] == '\r')){
   h++;
   len = 0;
   i++;
  }
  if(len > w) w = len;
  len++;
 }
 x = (80 - w) / 2;
 y = (50 - h) / 2;
 guardar_estado();
 guardar_ventana();
 bf = JVGmarcf;
 bb = JVGmarcb;
 m = JVGmarco;
 m_borde(14);
 m_fondo(1);
 ajustarmarco(MARCO_DOBLE);
 gettext(x, y, x + w - 1, y + h - 1, JVGbuffer);
 marco(x, y, x + w - 1,y + h - 1);
 _setcursortype(_NOCURSOR);
 gotoxy(x + 1, y);
 cputs("(ž)");
 cputs(title);
 window(x + 2, y + 1, x + w, y + h - 2);
 cputs("\n\r");
 cputs(msg);
 va_start(argptr, msg);
 vprintf(fmt, argptr);
 va_end(argptr);
 restaurar_ventana();
 gotoxy(x + w/2 - 10, y + h - 2);
 m_borde(bb);
 m_fondo(bf);
 ajustarmarco(m);
 ret = aceptar_cancelar();
 _setcursortype(_NORMALCURSOR);
 restaurar_colores();
 puttext(x, y, x + w - 1, y + h - 1, JVGbuffer);
 return ret;
}
