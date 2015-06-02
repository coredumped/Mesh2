#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"c:\progra~1\borlandc\cpps\juan\jvgtools.h"

void playspksnd(char *fname);
void spktoc(char *sndfile);
void pascal2c();

char *archmnu[] = {
 "Cargar", "Cerrar", "@", "Imprimir", "Copiar a...",
 "Generar Setup", "@", "Salir"
};

char *mainops[] = {
 " Archivo ", " Editar ", " Traducir ", " Compilar ", " Utilidades ",
 " Proyecto "
};

char *transmnu[] = {
 "C->Pascal", "Pascal->C",  "Basic->C", "@", "C->C++", "C++->Pascal",
  "Pascal->C++", "@", "Generar HTML"
};

char *compmnu[] = {
 "Small    ", "Compact  ", "Medium   ", "Large    ", "@", "Hacer EXE",
 "Ejecutar"
};

char *editmnu[] = {
 "Borland C++ 2.0", "Edit.com", "@", "Otro..."
};

char *prjmnu[] = {
 "Nuevo...", "Abrir", "Guardar", "Cerrar", "@", "Crear Libreria"
};

char *utilmnu[] = {
 "Generar sonido", "Cargar sonido", "Ejecutar sonido", "Generar codigo de sonido", "@", "Generar setup"
};

char *msg = "El menu seleccionado\n\rno ha sido definido\n\rhasta el momento";
char *msg2 = "El elemento seleccionado\n\rno hace ninguna funcion";

void titulo(){
 gotoxy(1,1);
 textcolor(15);
 textbackground(1);
 printchars('Í', 80);
 gotoxy(2,1);
 cputs("(ž)[þ] Mini compilador ");
}

void main(){
 Boolean stop = False, btmp;
 char sndfile[32] = "????????.spk";
 clrscr();
 textcolor(0);
 iniciar_herram();
 ajustarcolores(3, 0, 0, 14);
 m_borde(0);
 m_fondo(3);
 gotoxy(1,1);
 textcolor(15);
 textbackground(1);
 printchars('Í', 80);
 gotoxy(2,1);
 cputs("(ž)[þ] Mini compilador ");
 do{
  switch(menu_horz(2, mainops, 6)){
   case 0:
    if(menu_vert(1, 3, archmnu, 8) == 7){
     if(jvg_message("Salir", "Est  seguro que desea salir?\n\r")) stop = True;
    }
    else errormsg("Error", msg2);
    break;
   case 1:
    if(menu_vert(10, 3, editmnu, 4) == -1) errormsg("Error", msg2);
    break;
   case 2:
    switch(menu_vert(18, 3, transmnu, 9)){
     case 1:
      pascal2c();
      break;
     default:
      errormsg("Error", msg2);
    }
    break;
   case 3:
    if(menu_vert(28, 3, compmnu, 7) != -1) errormsg("Error", msg2);
    break;
   case 4:
    switch(menu_vert(38, 3, utilmnu, 6)){
     case 0:
      if(system(".\\sonidos\\sndmaker") < 0){
       errormsg("Error", "No hay memoria suficiente\n\rpara ejecutar sndmaker o\n\rno se encotr¢ el ejecuta-\n\rble correspondiente.");
      }
      titulo();
      break;
     case 1:
      do{
       jvg_scanf("Archivo", "Nombre del archivo a cargar:", "%s", &sndfile);
       btmp = jvg_fexist(sndfile);
       if(btmp == Falso){
	strcpy(sndfile, jvg_fbuscar(sndfile));
	btmp = Verdadero;
       }
      }while(btmp == Falso);
      break;
     case 2:
      playspksnd(sndfile);
      break;
     case 3:
      spktoc(sndfile);
      break;
     default:
      errormsg("Error", msg2);
    }
    break;
   case 5:
    if(menu_vert(48, 3, prjmnu, 6) != -1) errormsg("Error", msg2);
    break;
   default:
    errormsg("Error", msg);
  };
 }while(!stop);
 if(kbhit())getch();
 gotoxy(1, 49);
}


void spktoc(char *sndfile){
 unsigned f, t;
 char temp[32];
 FILE *s, *c;
 s = jvg_fopen(sndfile, "rt");
 jvg_scanf("Sonido:", "Archivo de C en que incluir  el c¢digo:", "%s", &temp);
 c = jvg_fopen(temp, "at");
 jvg_scanf("Sonido:", "Nombre de la funci¢n que ejecutar  el sonido:", "%s", &temp);
 fprintf(c, "\n//Generado a partir de: %s\n", sndfile);
 fprintf(c, "void %s()\n{\n", temp);
 do{
  fscanf(s, "%u %u", &f, &t);
  if(f != 0) fprintf(c, " sound(%u);\n", f);
  if(t != 0) fprintf(c, " delay(%u);\n", t);
 }while(!feof(s));
 fprintf(c, " nosound();\n");
 fprintf(c, "}\n");
 fclose(s);
 fclose(c);
}