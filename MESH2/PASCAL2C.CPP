#include<conio.h>
#include<string.h>
#include"c:\progra~1\borlandc\cpps\juan\jvgtools.h"
int Reportar(char *fmt, ...);
void copyfile(char *dest, char *sorc);
Boolean jvg_xmessage(char *title, char *msg, char *fmt, ...);

static char pasbuffer[256];

//Busca un caracter y retorna su posicion en la cadena
int findchr(char chr, char *str){
 int len, i, found = -1;
 len = strlen(str);
 for(i = 0; i < len; i++){
  if(str[i] == chr){
   found = i;
   break;
  }
 }
 return found;
}

//Busca un caracter y retorna su posicion en la cadena
int findchrfrom(int start, char chr, char *str){
 int len, i, pos = -1;
 len = strlen(str);
 for(i = start; i < len; i++){
  if(str[i] == chr){
   pos = i;
   break;
  }
 }
 return pos;
}


//Reemplaza el £ltimo caracter de una cadena
void replastchr(char *str, char c){
 int len;
 len = strlen(str);
 str[len - 2] = c;
}

//Busca srch en str y retorna su posicion en la cadena
int findstr(char *srch, char *str){
 Boolean found;
 int len1, len2, i, j, cnt;
 if(strstr(str, srch) == NULL) return -1;
 len1 = strlen(str);
 len2 = strlen(srch);
 for(i = 0; i < len1; i++){
  found = False;
  j = 0;
  cnt = 0;
  while((j < len2) && !found){
   if(str[i + j] == srch[j]) cnt++;
   if(cnt == len2) found = Verdadero;
   j++;
  }
  if(found) break;
 }
 return i;
}


void copystring(char *str1, int pos1, char *str2, int pos2){
 int i, len;
 len = strlen(str2) - pos2;
 for(i = 0; i < len; i++) str1[i + pos1] = str2[i + pos2];
}


void fillwith(int start, char *str, char c){
 int i, len;
 len = strlen(str);
 if(start > len) return;
 for(i = start; i < len; i++){
  str[i] = c;
 }
}

//reemplaza rep2 en rep1, que est  localizado en string
int replacestr(char *string, char *rep1, char *rep2){
 int pos1, len1, len2, lenstr;
 char temp[256];
 char *str = NULL;
 str = string;
 pos1 = findstr(rep1, string);
 if(pos1 == -1) return Falso;
 strcpy(temp, string);
 len1 = strlen(rep1);
 len2 = strlen(rep2);
 lenstr = strlen(string);
 strcpy(temp, string);
 if(lenstr != len1){
  copystring(str, pos1, rep2, 0);
  copystring(str, pos1 + len2, temp, pos1 + len1);
  lenstr = lenstr - len1 + len2;
  fillwith(lenstr, str, '\0');
 }
 else{
  strcpy(str, rep2);
 }
 return Verdadero;
}

void replace_begin_end(FILE *pasfile, FILE *cfile){
 do{
  strset(pasbuffer, '\0');
  jvg_fgets(pasbuffer, 256, pasfile);
  replacestr(pasbuffer, "END.\n", "}\n");
  replacestr(pasbuffer, "END;\n", "}\n");
  replacestr(pasbuffer, "END", "}");
  replacestr(pasbuffer, "BEGIN", "{");
  replacestr(pasbuffer, "end.\n", "}\n");
  replacestr(pasbuffer, "end;\n", "}\n");
  replacestr(pasbuffer, "end", "}");
  replacestr(pasbuffer, "begin", "{");
  fprintf(cfile, "%s", pasbuffer);
 }while(!feof(pasfile));
}

void format_coments(FILE *pasfile, FILE *cfile){
 do{
  strset(pasbuffer, '\0');
  jvg_fgets(pasbuffer, 256, pasfile);
  replacestr(pasbuffer, "{", "/*");
  replacestr(pasbuffer, "}", "*/");
  fprintf(cfile, "%s", pasbuffer);
 }while(!feof(pasfile));
}

void kill_spc(char *str){
 int i, len, n, j = 0;
 char unspc[32];
 for(i = 0; i < len; i++){
  if(str[i] != 32){
   unspc[j] = str[i];
   j++;
  }
 }
 strcpy(str, unspc);
}

void format_asm_keyword(FILE *pasfile, FILE *cfile){
 do{
  strset(pasbuffer, '\0');
  jvg_fgets(pasbuffer, 256, pasfile);
  replacestr(pasbuffer, "asm\n", "asm{\n");
  replacestr(pasbuffer, "ASM\n", "asm{\n");
  replacestr(pasbuffer, "Asm\n", "asm{\n");
  fprintf(cfile, "%s", pasbuffer);
 }while(!feof(pasfile));
}

void format_hex(char *buf){
 char phex[4];
 char chex[4];
 for(int i = 0; i < 16; i++){
  sprintf(phex, "$%X", i);
  sprintf(chex, "0x%X", i);
  replacestr(buf, phex, chex);
  sprintf(phex, "$%x", i);
  sprintf(chex, "0x%X", i);
  replacestr(buf, phex, chex);
 }
}

void format_program_directive(FILE *pasfile, FILE *cfile){
 do{
  int pos;
  char quote[] = {34,0};                //"
  char squote[] = {39,0};               //'
  strset(pasbuffer, '\0');
  jvg_fgets(pasbuffer, 256, pasfile);
  if((pos = findstr("program ", pasbuffer)) == 0) replacestr(pasbuffer, "program", "//");
  else
  if((pos = findstr("Program ", pasbuffer)) == 0) replacestr(pasbuffer, "program", "//");
  else
  if((pos = findstr("PROGRAM ", pasbuffer)) == 0) replacestr(pasbuffer, "program", "//");
  if(pos != -1) replacestr(pasbuffer, ";\n", "\n");

  if((pos = findstr("if ", pasbuffer)) == 0) replacestr(pasbuffer, "if ", "if(");
  else
   if((pos = findstr("If ", pasbuffer)) == 0) replacestr(pasbuffer, "if ", "if(");
   else
    if((pos = findstr("IF ", pasbuffer)) == 0) replacestr(pasbuffer, "if ", "if(");
  if(pos != -1) replacestr(pasbuffer, "=", "==");

  if((findstr("uses ", pasbuffer) == 0) ||
     (findstr("Uses ", pasbuffer) == 0) ||
     (findstr("USES ", pasbuffer) == 0)){
   fprintf(cfile, "//Recuerde declarar sus inclusiones\n");
   replacestr(pasbuffer, "uses", "//uses");
   replacestr(pasbuffer, "Uses", "//uses");
   replacestr(pasbuffer, "USES", "//uses");
  }
  replacestr(pasbuffer, ":=", "=");
  replacestr(pasbuffer, "div", "/");

  while(replacestr(pasbuffer, "'", "xx$$xx"));
  while(replacestr(pasbuffer, quote, squote));
  while(replacestr(pasbuffer, "xx$$xx", quote));
  format_hex(pasbuffer);

  fprintf(cfile, "%s", pasbuffer);
 }while(!feof(pasfile));
}

void trans_types(char *instr, char *outstr){
 if(stricmp(instr, "integer")  == 0){
  strcpy(outstr, "int ");
  return;
 }
 if(stricmp(instr, "real")     == 0){
  strcpy(outstr, "double ");
  return;
 }
 if(stricmp(instr, "byte")     == 0){
  strcpy(outstr, "unsigned char ");
  return;
 }
 if(stricmp(instr, "word")     == 0){
  strcpy(outstr, "unsigned int ");
  return;
 }
 if(stricmp(instr, "shortint") == 0){
  strcpy(outstr, "short int ");
  return;
 }
 if(stricmp(instr, "longint")  == 0){
  strcpy(outstr, "long int ");
  return;
 }
 if(stricmp(instr, "boolean")  == 0){
  strcpy(outstr, "int ");
  return;
 }
 if(stricmp(instr, "single")   == 0){
  strcpy(outstr, "float ");
  return;
 }
 if(stricmp(instr, "double")   == 0){
  strcpy(outstr, "double ");
  return;
 }
 if(stricmp(instr, "extended") == 0){
  strcpy(outstr, "long double ");
  return;
 }
 if(stricmp(instr, "comp")     == 0){
  strcpy(outstr, "long int ");
  return;
 }
 if(jvg_xmessage("Traductor:", "El siguiente tipo no existe, desea\n\rutilizar uno nuevo?\n\r\n\r", " %s\n\r", instr)){
  jvg_scanf("Traductor:", "Escriba el nombre de el\n\rnuevo tipo a usar\n\r", "%s", &outstr);
 }
 else{
  strcpy(outstr, instr);
 }
 strcat(outstr, " ");
}

void format_procs(FILE *pasfile, FILE *cfile){
 int paren1, paren2;  //paren1 y paren2 correponden a los parentesis '(' y ')' respectivamente
 int p2;              //corresponde a la posicion del signo de :
 int coma;            //corresponde a la posicion de la ,
 int pcoma;           //corresponde a la posicion del ;
 int itmp;
 int i;
 char tmptype[20];    //Almacena el nombre de un tipo temporalmente
 char tmpvar[64];     //En pascal los nombres de las variables pueden tener hasta 64 caracteres
 char declbuffer[256];
 Boolean finish = Falso;
 do{
  strset(pasbuffer, '\0');
  jvg_fgets(pasbuffer, 256, pasfile);
  if(strstr(pasbuffer, "procedure") || strstr(pasbuffer, "PROCEDURE")){
   putch(219);
   Reportar(" formateando: %s", pasbuffer);
   replacestr(pasbuffer, "procedure ", "void ");
   replacestr(pasbuffer, "PROCEDURE ", "void ");
   replastchr(pasbuffer, '{');
   if(!strchr(pasbuffer, '(')) replacestr(pasbuffer, "{", "(void)");
   else{
    replastchr(pasbuffer, '\0');
    strcpy(declbuffer, pasbuffer);
    paren1 = findchr('(', pasbuffer);
    paren2 = findchr(')', pasbuffer);
    p2 = findchr(':', pasbuffer);
    coma = findchr(',', pasbuffer);
    pcoma = findchr(';', pasbuffer);
    i = paren1 + 1;
    fillwith(paren1 + 1, declbuffer, '\0');
    do{
     Reportar("  formateando los parametros...\n");
     if(pcoma == -1){
      Reportar("   Traduciendo tipos de variables\n");
      strset(tmptype, '\0');
      copystring(tmptype, 0, pasbuffer, p2);
      fillwith(findchr(')', tmptype), tmptype, '\0');
      replacestr(tmptype, ":", " ");
      while(replacestr(tmptype, " ", ""));
      trans_types(tmptype, tmptype);
      coma = findchr(',', pasbuffer);
      //At this point we retrieve the variable names
      Reportar("   buscando los nombres de las variables\n");
      do{
       strset(tmpvar, '\0');
       copystring(tmpvar, 0, pasbuffer, i);
       itmp = findchr(',', tmpvar);
       if(itmp == -1){                     //Si no hay coma hacer
	itmp = findchr(':', tmpvar);
	fillwith(itmp, tmpvar, '\0');
	while(replacestr(tmpvar, " ", ""));
	strcat(declbuffer, tmptype);
	strcat(declbuffer, tmpvar);
	finish = Verdadero;
       }
       else{                               //Si hay coma hacer
	fillwith(itmp, tmpvar, '\0');
	while(replacestr(tmpvar, " ", ""));
	strcat(declbuffer, tmptype);
	strcat(declbuffer, tmpvar);
	strcat(declbuffer, ", ");
       }
       Reportar("    encontr¢: %s\n", tmpvar);
       i = coma + 1;
       coma = findchrfrom(coma + 1, ',', pasbuffer);
       if(coma != -1) i = coma + 1;
      }while(!finish);
      strcat(declbuffer, ")\n");
      strcpy(pasbuffer, declbuffer);
     }
     p2 = findchrfrom(p2 + 1, ':', pasbuffer);
    }while((p2 != -1) && (pcoma != - 1));
    while(replacestr(pasbuffer, ";", ","));
   }
   Reportar(" resultado: %s", pasbuffer);
  }
  fprintf(cfile, "%s", pasbuffer);
 }while(!feof(pasfile));
}

long countlines(char *srcprg){
 FILE *prg;
 long n = 0;
 prg = jvg_fopen(srcprg, "rt");
 do{
  jvg_fgets(pasbuffer, 256, prg);
  n++;
 }while(!feof(prg));
 fclose(prg);
 strset(pasbuffer, '\0');
 return n;
}

void pascal2c(){
 char temp[32];
 FILE *cfile, *pfile;
 long lines;
 jvg_scanf("Traductor", "Nombre del archivo en Pascal que va a traducirse a C:", "%s", &temp);
 lines = countlines(temp);
 pfile = jvg_fopen(temp, "rt");
 jvg_scanf("Traductor", "Nombre del archivo en C en que se va escribir:", "%s", &temp);
 marco(6, 24, 74, 26);
 gotoxy(7, 25);

 //Formatear las lineas de comentario en Pascal a C
 cfile = jvg_fopen(temp, "wt");
 format_coments(pfile, cfile);
 fclose(cfile);
 fclose(pfile);
 copyfile("pascal2c.tmp", temp);
 putch(219);
 //Reemplazar begin y end por { }
 cfile = jvg_fopen(temp, "wt");
 pfile = jvg_fopen("pascal2c.tmp", "rt");
 replace_begin_end(pfile, cfile);
 fclose(cfile);
 fclose(pfile);
 copyfile("pascal2c.tmp", temp);
 putch(219);
 //Formateando bloques asm
 Reportar("Formateando bloques asm...");
 cfile = jvg_fopen(temp, "wt");
 pfile = jvg_fopen("pascal2c.tmp", "rt");
 format_asm_keyword(pfile, cfile);
 fclose(cfile);
 fclose(pfile);
 copyfile("pascal2c.tmp", temp);
 Reportar("Formateo de bloques asm completado\n\n");
 putch(219);
 //Formateando la directiva program
 Reportar("Formateando la directiva program...");
 cfile = jvg_fopen(temp, "wt");
 pfile = jvg_fopen("pascal2c.tmp", "rt");
 format_program_directive(pfile, cfile);
 fclose(cfile);
 fclose(pfile);
 copyfile("pascal2c.tmp", temp);
 Reportar("Formateo de la directiva program concluido\n\n");
 putch(219);

 //Reemplazar procedure por void
 Reportar("Formateando procedimientos...\n");
 cfile = jvg_fopen(temp, "wt");
 pfile = jvg_fopen("pascal2c.tmp", "rt");
 format_procs(pfile, cfile);
 fclose(cfile);
 fclose(pfile);
 copyfile("pascal2c.tmp", temp);
 Reportar("Formato de procedimientos completado\n\n");
}