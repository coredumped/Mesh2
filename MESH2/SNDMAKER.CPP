#include<dos.h>
#include<conio.h>
#include<bios.h>
#include<stdio.h>
#include"jvgtools.h"

#define SC_PLUS  0x4E2B
#define SC_MINUS 0x4A2D
#define MAX_FREQ 3000

void play(unsigned f[], unsigned t[], int n, int reps);
void graphsound(unsigned f[], int n);
void savesound(unsigned f[], unsigned t[], int n);
void loadsound(unsigned f[], unsigned t[], int n);
void spectral(int l);

void main(){
 int i;
 int key = 0, flag = 0;
 int sel = 0;
 int reps = 1;
 unsigned freq[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0,
		    0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0};
 unsigned t[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0,
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0};
 textmode(C4350);
 clrscr();
 graphsound(freq, 32);
 gotoxy(1, sel + 18);
 putch(26);
 _setcursortype(_NOCURSOR);
 gotoxy(50, 4);
 cprintf("Frecuencia:  %5u Hz", freq[sel]);
 gotoxy(50, 5);
 cprintf("Tiempo:      %03.3f secs", (float)t[sel] / 1000);
 gotoxy(50, 6);
 cprintf("Repeticiones: %3d ", reps);
 int lastsel = 0;
 gotoxy(2,2);
 cputs("F1         Reset\n\r");
 cputs(" F2         Guardar\n\r");
 cputs(" F3         Cargar\n\r ");
 putch(24);
 putch(25);
 cputs("         Seleccionar\n\r ");
 putch(27);
 putch(26);
 cputs("         Disminuir/Incrementar frecuencia\n\r");
 cputs(" -+         Disminuir/Incrementar tiempo\n\r");
 cputs(" ENTER      Ejecutar sonido\n\r");
 cputs(" Fin/Inicio Disminuir/Incrementar tiempo total\n\r");
 cputs(" F9/F10     Disminuir/Incrementar frecuencia en todos\n\r");
 cputs(" ESPACIO    Ejecutar seleccionado\n\r");
 cputs(" F4         Editar frecuencia\n\r");
 cputs(" F5         Editar tiempo\n\r");
 cputs(" F6         Invertir frecuencia\n\r");
 cputs(" RePag      Incrementa las repeticiones\n\r");
 cputs(" AvPag      Disminuye las repeticiones\n\r");
 cputs(" ESC        Salir");
 do{
  key = 0;
  key = bioskey(0);
  if(key == SC_ARRIBA) sel--;
  if(key == SC_ABAJO) sel++;
  if(key == SC_DER){
   freq[sel]+=4;
   gotoxy(2, sel + 18);
   spectral((int)((float)freq[sel] * 78 / MAX_FREQ));
  }
  if(key == SC_IZQ){
   freq[sel]-=4;
   gotoxy(2, sel + 18);
   spectral((int)((float)freq[sel] * 78 / MAX_FREQ));
  }
  if(sel > 31) sel = 0;
  if(sel < 0) sel = 31;
  if(freq[sel] < 0) freq[sel] = 0;
  if(freq[sel] > MAX_FREQ) freq[sel] = MAX_FREQ;
  gotoxy(1, lastsel + 18);
  putch(32);
  gotoxy(1, sel + 18);
  putch(26);
  if(key == SC_MINUS) t[sel]--;
  if(key == SC_PLUS) t[sel]++;
  if(key == SC_ENTER) play(freq, t, 32, reps);
  if(key == 0x011B) flag = 1;
  if(key == 0x5100) reps--;
  if(key == 0x4900) reps++;
  if(key == 0x3C00) savesound(freq, t, 32);
  if(key == 0x3D00){
   loadsound(freq, t, 32);
   graphsound(freq, 32);
  }
  if(key == 0x3920){
   sound(freq[sel]);
   delay(t[sel]);
   nosound();
  }
  if(key == 0x3B00){
   for(i = 0; i < 32; i++){
    freq[i] = 0;
    t[i] = 0;
   }
   graphsound(freq,32);
  }
  if(key == 0x3E00){
   gotoxy(1,1);
   printf("Frecuencia: ");
   _setcursortype(_NORMALCURSOR);
   scanf("%d", &freq[sel]);
   _setcursortype(_NOCURSOR);
   fflush(stdin);
   gotoxy(1,1);
   printchars(32, 79);
   graphsound(freq, 32);
  }
  if(key == 0x3F00){
   gotoxy(1,1);
   printf("Tiempo (milisegundos): ");
   _setcursortype(_NORMALCURSOR);
   scanf("%d", &t[sel]);
    _setcursortype(_NOCURSOR);
   fflush(stdin);
   gotoxy(1,1);
   printchars(32, 79);
  }
  if(key == 0x4000){
   freq[sel] = MAX_FREQ - freq[sel];
   gotoxy(2, sel + 18);
   spectral((int)((float)freq[sel] * 78 / MAX_FREQ));
  }
  if(key == 0x4700){
   for(i = 0; i < 32; i++){
    if(freq[i] != 0) t[i]++;
   }
  }
  if(key == 0x4F00){
   for(i = 0; i < 32; i++){
    if((freq[i] != 0) && (t[i] != 0)) t[i]--;
   }
  }
  if(key == 0x4300){
   for(i = 0; i < 32; i++){
    if(freq[i] != 0) freq[i]-=4;
    if(kbhit())getch();
   }
   graphsound(freq, 32);
  }
  if(key == 0x4400){
   for(i = 0; i < 32; i++){
    freq[i]+=4;
    if(freq[i] > MAX_FREQ) freq[i] = MAX_FREQ;
    if(kbhit())getch();
   }
   graphsound(freq, 32);
  }
  if(t[sel] > 5000) t[sel] = 5000;
  gotoxy(1, lastsel + 18);
  putch(32);
  gotoxy(1, sel + 18);
  putch(26);
  gotoxy(50, 4);
  cprintf("Frecuencia:  %5u Hz", freq[sel]);
  gotoxy(50, 5);
  cprintf("Tiempo:      %03.3f secs", (float)t[sel] / 1000);
  gotoxy(50, 6);
  cprintf("Repeticiones: %3d ", reps);
  lastsel = sel;
 }while(flag == 0);
 _setcursortype(_NORMALCURSOR);
 clrscr();
}

void play(unsigned f[], unsigned t[], int n, int reps){
 int i, j, last = 0;
 for(i = 0; i < reps; i++){
  for(j = 0; j < n; j++){
   if((t[j] >0)){
    gotoxy(1, last + 18);
    putch(' ');
    gotoxy(1, j + 18);
    putch(26);
    last = j;
    if(f[j] > 0) sound(f[j]);
    delay(t[j]);
   }
   if(kbhit())getch();
  }
  nosound();
 }
 gotoxy(1, last + 18);
 putch(' ');
}

void columna(int x, int y, int l){
 int i;
 gotoxy(x, y - l);
 for(i = 0; i < l; i++) putch('þ');
}

void printchars(char c, int l){
 for(int i = 0; i < l; i++) putch(c);
}

void spectral(int l){
 if(l <= 0) return;
 printchars(32, 78);
 gotoxy(2, wherey());
 textcolor(1);
 for(int i = 0; i < l; i++){
  if(i > 8) textcolor(9);
  if(i > 16) textcolor(LIGHTCYAN);
  if(i > 24) textcolor(CYAN);
  if(i > 32) textcolor(GREEN);
  if(i > 40) textcolor(LIGHTGREEN);
  if(i > 48) textcolor(YELLOW);
  if(i > 56) textcolor(LIGHTRED);
  if(i > 64) textcolor(RED);
  putch(254);
 }
 textcolor(7);
}

void graphsound(unsigned f[], int n){
 int i, y;
 float tmp;
 window(1,18,80,50);
 clrscr();
 window(1,1,80,50);
 for(i = 0; i < n; i++){
  tmp = (float)f[i] * 78 / MAX_FREQ;
  y = (int)tmp;
  gotoxy(2, i + 18);
  spectral(y+1);
 }
}

void savesound(unsigned f[], unsigned t[], int n){
 int i;
 char filename[80];
 FILE *snd;
 gotoxy(1,1);
 cprintf("Archivo: ");
 _setcursortype(_NORMALCURSOR);
 gets(filename);
 _setcursortype(_NOCURSOR);
 snd = fopen(filename, "wt");
 for(i = 0; i < n; i++) fprintf(snd, "%u %u\n", f[i], t[i]);
 fclose(snd);
 gotoxy(1,1);
 printchars(' ', 79);
}

void loadsound(unsigned f[], unsigned t[], int n){
 int i;
 char filename[80];
 FILE *snd;
 gotoxy(1,1);
 cprintf("Archivo: ");
 _setcursortype(_NORMALCURSOR);
 gets(filename);
 _setcursortype(_NOCURSOR);
 snd = fopen(filename, "rt");
 if(snd == NULL){
  textcolor(4 + BLINK);
  gotoxy(1,1);
  cprintf("Archivo no existe!!");
  delay(100);
  textcolor(7);
  printchars(' ', 79);
  return;
 }
 for(i = 0; i < n; i++) fscanf(snd, "%u %u\n", &f[i], &t[i]);
 fclose(snd);
 gotoxy(1,1);
 printchars(' ', 79);
}