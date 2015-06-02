#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include"c:\progra~1\borlandc\cpps\juan\jvgtools.h"

void JVGsound(unsigned freq, unsigned milis)
{
 if(milis == 0) return;
 if(freq == 0){
  delay(milis);
  return;
 }
 sound(freq);
 delay(milis);
 nosound();
}

void JVGtecla(){
 JVGsound(1340, 22);
 JVGsound(2000, 44);
 JVGsound(1340,48);
}

void JVGmenu(){
 JVGsound(340, 16);
 JVGsound(1000, 24);
 JVGsound(320,20);
}

void playspksnd(char *fname){
 unsigned freq, t;
 FILE *file;
 file = jvg_fopen(fname, "rt");
 do{
  jvg_fscanf(file, "%u %u", &freq, &t);
  sound(freq);
  delay(t);
 }while(!feof(file));
 nosound();
 fclose(file);
}

void msg_snd(){
 sound(900);
 delay(20);
 delay(20);
 sound(1800);
 delay(25);
 delay(20);
 sound(2800);
 delay(35);
 nosound();
}

void error_snd(){
 sound(177);
 delay(37);
 delay(20);
 sound(274);
 delay(16);
 delay(20);
 sound(428);
 delay(37);
 sound(84);
 delay(8);
 nosound();
}
