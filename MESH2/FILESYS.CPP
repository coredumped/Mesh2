#include<dir.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include"c:\progra~1\borlandc\cpps\juan\jvgtools.h"

static char fbuffer[1024];
char *jvg_fbuscar(char *fn);

Boolean jvg_fexist(char *fn){
 FILE *e;
 if((e = fopen(fn, "rb")) == NULL) return Falso;
 fclose(e);
 return Verdadero;
}

FILE *jvg_fopen(char *fn, char *type){
 FILE *f;
 if(strchr(type, 'r') == NULL){
  f = fopen(fn, type);
  sprintf(fbuffer,"Ha sucedido un error al intentar\n\rabrir el archivo: %s\n\ren modo de escritura.\n\r¨Desea continuar?\n\r", fn);
  if(f == NULL){
   if(jvg_message("Archivo", fbuffer) == Falso) exit(1);
  }
  return f;
 }
 f = fopen(fn, type);
 if(f == NULL){
  sprintf(fbuffer, " El archivo: %s\n\r no fue encontrado.¨Desea\n\r buscar uno equivalente\n\r en la unidad actual?\n\r", fn);
  if(jvg_message("Archivo", fbuffer) == Falso) exit(1);
  strcpy(fn, jvg_fbuscar(fn));
  f = fopen(fn, type);
 }
 return f;
}

char *jvg_fbuscar(char *fn){
 int i;
 Boolean ok;
 char fname[MAXFILE];
 char fext[MAXEXT];
 char fdir[MAXDIR];
 char fdrive[MAXDRIVE];
 char fpath[13];
 struct ffblk fblk;
 fnsplit(fn, fdrive, fdir, fname, fext);
 sprintf(fpath, "%s.*", fname);
 i = findfirst(fpath, &fblk, 0);
 if(i == 0){
  sprintf(fbuffer, "Se ha encontrado el archivo\n\r%s\n\r¨Desea utilizarlo?\n\r", fblk.ff_name);
  ok = jvg_message("B£squeda", fbuffer);
  if(ok == Verdadero) return fblk.ff_name;
  else{
   do{
    i = findnext(&fblk);
    sprintf(fbuffer, "Se ha encontrado el archivo\n\r%s\n\r¨Desea utilizarlo?\n\r", fblk.ff_name);
    ok = jvg_message("B£squeda", fbuffer);
    if(ok == Verdadero) return fblk.ff_name;
   }while(!i);
  }
 }
 errormsg("Error Fatal!", "Es imposible leer un\n\rarchivo inexistente\n\rpor consiguiente\n\rse finalizar  este\n\rprograma!!!");
 exit(1);
 return NULL;
}

int jvg_fscanf(FILE *fp, char *fmt, ...){
 int cnt;
 va_list  argptr;
 if(feof(fp)){
  if(!jvg_message("Lectura", "Se ha excedido el fin\n\rde archivo al leer un\n\run archivo abierto\n\r¨Desea continuar?\n\r")){
   exit(1);
  }
 }
 va_start(argptr, fmt);
 cnt = vfscanf(fp, fmt, argptr);
 va_end(argptr);
 return(cnt);
}

size_t jvg_fread(void *ptr, size_t size, size_t n, FILE *f){
 if(feof(f)){
  if(!jvg_message("Lectura", "Se ha excedido el fin\n\rde archivo al leer un\n\run archivo abierto\n\r¨Desea continuar?\n\r")){
   exit(1);
  }
 }
 return fread(ptr, size, n, f);
}

char *jvg_fgets(char *s, int n, FILE *f){
 if(feof(f)){
  if(!jvg_message("Lectura", "Se ha excedido el fin\n\rde archivo al leer un\n\run archivo abierto\n\r¨Desea continuar?\n\r")){
   exit(1);
  }
 }
 return fgets(s, n, f);
}

void copyfile(char *dest, char *sorc){
 FILE *dst, *src;
 char b;
 src = jvg_fopen(sorc, "rb");
 dst = jvg_fopen(dest, "wb");
 do{
  jvg_fread((void*)&b, 1, 1, src);
  if(!feof(src)) fwrite((void*)&b, 1, 1, dst);
 }while(!feof(src));
 fclose(src);
 fclose(dst);
}
