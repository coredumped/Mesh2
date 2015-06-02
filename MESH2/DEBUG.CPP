#include<stdio.h>
#include<stdarg.h>

int Reportar(char *fmt, ...){
 int cnt;
 FILE *fp;
 fp = fopen("debug.log", "at");
 va_list  argptr;
 va_start(argptr, fmt);
 cnt = vfprintf(fp, fmt, argptr);
 va_end(argptr);
 fclose(fp);
 return(cnt);
}
