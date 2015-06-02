//----------------------------------------------------------------------------------------
//
//    Mesh.cpp
//
//      A program that animates 3-D ecuations
//
//    first compiled:  04-06-1997
//
//  													  written by:  Juan V. Guerrero
//----------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <graphics.h>
#include <dos.h>
#include <string.h>

float xxIrel[8000];    //Array que contiene los niveles de profundidad
float seno[362];       //Array que contiene los valores de seno
float coseno[362];     //Array que contiene los valores de coseno
float tangente[362];   //Array que contiene los valores de tangente
int PolygonMode = 1;   //Variable que contiene el estado de los poligonos
							  //     Si es 1 los poligonos se rellenan de color
							  //     en caso contrario son transparentes


//Esta funcion espera a que el CRT termine de dibujar la pantalla
void wtVerticalRetrace(void){
 asm     mov     dx,0x3DA
WaitVerticalRetrace1:
 asm     in      al,dx
 asm     test    al,8
 asm     jne     WaitVerticalRetrace1
WaitVerticalRetrace2:
 asm     in      al,dx
 asm     test    al,8
 asm     je      WaitVerticalRetrace2
}


//Estructura que crea un punto bidimensional dado por sus coordenadas x,y
typedef struct{
	double x;
	double y;
} Point2d;


//Estructura que crea un punto bidimensional dado por sus coordenadas x,y,z
typedef struct{
	double x;
	double y;
	double z;
} Point3d;

double deepness3d;       //variable que contiene la profundidad maxima de la pantalla
int scrmaxx, scrmaxy;    //scrmaxx es el ancho de la pantalla
								 //scrmaxy es el alto de la pantalla


//Esta funcion calcula el divisor adecuado dada la altura del horizonte (horihi)
//y la profundidad de pantalla
double divix(double horihi, double prof){
 double xdivi;
 horihi = fabs(horihi);
 if(horihi <= 0) horihi = horihi + 0.00001;
 xdivi = exp((log(horihi)) / prof);
 return(1 / xdivi);
}


//Devuelve el valor del seno para el angulo sexagesimal x
double Sin(int x){
 int ang;
 ang = x * 180 / M_PI;
 if(ang > 360) ang = ang - 360;
 if(ang < 0) ang = ang + 360;
 if(ang == 0) return 0;
 return seno[ang];
}


//Devuelve el valor del coseno para el angulo sexagesimal x
double Cos(int x){
 int ang;
 ang = x * 180 / M_PI;
 if(ang > 360) ang = ang - 360;
 if(ang < 0) ang = ang + 360;
 if(ang == 0) return 1;
 return coseno[ang];
}


//Devuelve el valor de la tangente para el angulo sexagesimal x
double Tan(double x){
 int ang;
 ang = x * 180 / M_PI;
 if(ang < 0) return tan(x);
 if(ang > 360) tan(x);
 return tangente[ang];
}


//Muestra el mensaje de despedida del programa y la informacion sobre como conseguir
//el codigo fuente
void displaymessage(){
 printf("Este es un programa de freeware si deseas obtener el c¢digo fuente\n");
 printf("llama al 253-1052 y pregunta por Juan o deja un mensaje.\n");
 printf("Este programa fue hecho utilizando Borland C++ 4.0 y utiliza BGI\n");
 printf("El problema del parpadeo de la imagen fue solucionado gracias a la funci¢n\n");
 printf("wtVerticalRetrace que espera que el monitor termine de dibujar en la pantalla\n\n");
 printf("El autor cursa el primer a¤o de inform tica en la Universidad Nacional de Panam \n");
 printf("\nLa £nica condici¢n para poseer este software es que sea distribuido a otras\n");
 printf("personas en forma gratuita, es decir piratealo libremente.\n");
 printf("NOTA: Este programa aun requiere optimizaci¢n\n");
 textcolor(7 + BLINK);
 cprintf("Costo del c¢digo fuente: ");
 textcolor(10 + BLINK);
 cprintf("B/5.00");
}


//Inicia el modo grafico y precalcula los valores de profundidad y tablas trigonometricas
//para angulos sexagesimales
void init3dgraph(void){
 int errorcode;
 int gdriver;
 int gmode;
  gdriver = DETECT;
  //Inicia modo grafico asumiendo que egavga.bgi esta en c:\bc4\bin, si falla
  //luego lo busca en c:\borlandc\bin, si aun falla, entonces lo busca en la
  //unidad y ruta actual, si vuelve a fallar entonces despliega un mensaje de
  //error
  initgraph(&gdriver, &gmode, "c:\\progra~1\\borlandc\\bgi");
redo_from_start:
  errorcode = graphresult();
  if (errorcode != grOk){
	initgraph(&gdriver, &gmode, "c:\\progra~1\\borlandc\\bgi");
	errorcode = graphresult();
	if(errorcode == grOk) goto redo_from_start;
	else{
	 initgraph(&gdriver, &gmode, "");
	 errorcode = graphresult();
	 if(errorcode == grOk) goto redo_from_start;
	}
	printf("%s\n", grapherrormsg(errorcode));
	printf("Programa finalizado!!!");
	exit(1);
  }
  settextstyle(SMALL_FONT, HORIZ_DIR, 0);
  setusercharsize(2, 2, 2, 2);
  deepness3d = 3500;
#define XVANISH getmaxy()/2
#define YVANISH getmaxx()*0.25
#define DIVI divix(YVANISH, deepness3d)
//restablece modo de texto;
  restorecrtmode();
  _setcursortype(_NOCURSOR);
  gotoxy(1,1);
  printf("Ajustando tabla trigonometrica...\n");
  gotoxy(1,21);
  printf("Este es un programa de freeware si deseas obtener el c¢digo fuente");
  gotoxy(1, 22);
  printf("llama al 253-1052 y pregunta por Juan o deja un mensaje.");
  gotoxy(1, 23);
  printf("Este programa fue hecho utilizando Borland C++ 4.0 y utiliza BGI");
  gotoxy(1, 24);
  cprintf("NOTA: Este programa aun requiere optimizaci¢n");
  gotoxy(1, 25);
  cprintf("El autor cursa el primer a¤o de inform tica en la Universidad Nacional de Panam \n");
  int angle;
  double ang;
  //Carga la tabla trigonometrica a sus respectivos arrays
  for(angle = 0; angle <=360; angle++){
	ang = angle * M_PI / 180;
	seno[angle] = sin(ang);
	coseno[angle] = cos(ang);
	tangente[angle] = tan(ang);
	gotoxy(1, 2);
	printf("Angulo: %01.4f rads  ", ang);
	gotoxy(1, 3);
	printf("Seno:     %01.4f   ", seno[angle]);
	gotoxy(1, 4);
	printf("Coseno:   %01.4f   ", coseno[angle]);
	gotoxy(1, 5);
	printf("Tangente: %01.4f                                ", tangente[angle]);
  }
  gotoxy(1, 6);
  printf("Calculando dimensiones...\n");
  //Precalcula los valores de profundidad para x
  for(int xx = 0; xx < 8000; xx++){
	xxIrel[xx] = 1 - pow(DIVI, xx * 0.5);
	gotoxy(1, 7);
	printf("X=%04.1f  Deep=%01.4f ", xx * 0.5, xxIrel[xx]);
  }
  //restablece modo grafico a VGA 640x350 con 16 colores y 2 paginas de video
  setgraphmode(VGAMED);
  cleardevice();
}


double xxxtemp, lastxxxtemp, lastx;
//Convierte una coordenada tridimensional x,y,z a una coordenada bidimensional x,y de
//acuerdo a los parametros de altura del horizonte (horihi), ancho de vision (wide) y
//divisor adecuado (divi)
Point2d c3dto2d(double x, double y, double z, double horihi, double wide, double divi){
 Point2d punto;
 if(x == 0){
  punto.x = y;
  punto.y = z;
  return punto;
 }
 if(x == lastx){
  xxxtemp = lastxxxtemp;
 }
 else{
  if(x > 0) xxxtemp = xxIrel[(int)(x * 2)];
  else{
	xxxtemp = 1 - pow(divi, x);
  }
 }
 punto.x = y + xxxtemp * (wide - y);
 punto.y = z + xxxtemp * (horihi - z);
 lastx = x;
 lastxxxtemp = xxxtemp;
 return(punto);
}


//Dibuja un poligono dados sus vertices (*xpoints), la cantidad de vertices (numpoints),
//los parametros del espacio 3-D (horihi, wide, divi), el color de rellenado (fill)
//y el color de borde del poligono (colo)
void Polygon3d(Point3d *xpoints, int numpoints, double horihi, double wide, double divi, int colo, int fill){
 int poly[500];
 int xpoly, apoly = 0;
 Point2d point;
 setcolor(colo);
 //Primero transforma las coordenadas de 2-D a 3-D
 //y luego crea el areglo de puntos para la funcion drawpoly o fillpoly
 for(xpoly = 0; xpoly < numpoints; xpoly++){
  point = c3dto2d(xpoints[xpoly].x, xpoints[xpoly].y, xpoints[xpoly].z, horihi, wide, divi);
  poly[apoly] = point.x;
  apoly++;
  poly[apoly] = point.y;
  apoly++;
 }
 poly[apoly] = poly[0];
 apoly++;
 poly[apoly] = poly[1];
 apoly++;
 //Dibuja el poligono de acuerdo al modo de rellenado (PolygonMode)
 if(PolygonMode == 0){
  setcolor(10);
  drawpoly(apoly / 2, poly);
 }
 else{
  setfillstyle(SOLID_FILL, fill);
  fillpoly(apoly / 2, poly);
 }
}

//La funcion rotate rota un punto p alrededor de un punto c dado un angulo a sobre
//el plano x-y
//NOTA: esta funcion no funciona bien y debe ser corregida
Point3d Rotate(Point3d p, Point3d c, double da){
 Point3d r;
 r.x = c.x + p.x * Cos(da);
 r.y = c.y + p.y * Sin(da);
 r.z = p.z;
 return r;
}

//Escala un punto p dada la magnificacion y el centro del espacio
Point3d Scale(Point3d p, double magnification, Point3d center)	{
 Point3d punto;
 punto.x = -p.x * magnification + center.x;
 punto.y = p.y * magnification + center.y;
 punto.z = -p.z * magnification + center.z;
 return(punto);
}


//Dibuja una linea dados sus extremos 3-D, los parametros del espacio y el color
void line3d(double x1, double y1, double z1, double x2, double y2, double z2, double h, double w, double d, int color){
 setcolor(color);
 Point2d p1, p2;
 p1 = c3dto2d(x1, y1, z1, h, w, d);
 p2 = c3dto2d(x2, y2, z2, h, w, d);
 line(p1.x, p1.y, p2.x, p2.y);
 moveto(p2.x, p2.y);
}


//Dibuja una linea desde el punto actual hasta el punto especificado, los parametros
//del espacio y el color
void lineto3d(double x, double y, double z, double h, double w, double d, int color){
 setcolor(color);
 Point2d p;
 p = c3dto2d(x, y, z, h, w, d);
 lineto(p.x, p.y);
}


//Calcula el color de un poligono en funcion de una de sus coordenadas z
int GetColor(double z){
 int r = abs(z * 15/1.25 + 1);
 if(r == 0) r = 1;
 return(r);
}


//Retorna el valor de la coordenada z en funcion x, y, rl tiempo (t), la frecuencia
//en x (xf), la frecuencia en y (yf) y la funcion especificada
double f(double x, double y, double t, double xf, double yf, int fun){
 float xx, yy;
 switch(fun){
  case 0:
	return (sin(xf * x + yf * y - t));
  case 1:
	return (2 * sin(xf * t) * exp(-(x * x + y * y)));
  case 2:
	return (sin(xf * x * y + t));
  case 3:
	xx = x * x;
	yy = y * y;
	return cos(xx + yy + t) / (xx + yy + 1);
 }
 return (sin(xf * x + yf * y - t));
}


//Despliega el menu de ayuda
void displayhelp(){
 int left = 13;
 gotoxy(left, 2);
 printf("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ<Menu de ayuda>ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿");
 gotoxy(left, 3);
 printf("³H: disminuye el horizonte                            ³");
 gotoxy(left, 4);
 printf("³h: eleva el horizonte                                ³");
 gotoxy(left, 5);
 printf("³S: aumenta el ladeo                                  ³");
 gotoxy(left, 6);
 printf("³s: disminuye el ladeo                                ³");
 gotoxy(left, 7);
 printf("³+: aumenta la cantidad de pol¡gonos                  ³");
 gotoxy(left, 8);
 printf("³-: disminuye la cantidad de pol¡gonos                ³");
 gotoxy(left, 9);
 printf("³x: aumenta la frecuencia de X                        ³");
 gotoxy(left, 10);
 printf("³y: aumenta la frecuencia de Y                        ³");
 gotoxy(left, 11);
 printf("³>: aumenta los valores de evaluaci¢n de la ecuaci¢n  ³");
 gotoxy(left, 12);
 printf("³<: disminuye los valores de evaluaci¢n de la ecuaci¢n³");
 gotoxy(left, 13);
 printf("³M: aumenta la magnificaci¢n                          ³");
 gotoxy(left, 14);
 printf("³m: disminuye la magnificaci¢n                        ³");
 gotoxy(left, 15);
 printf("³p: rellena o no los pol¡gonos                        ³");
 gotoxy(left, 16);
 printf("³g: dibuja el eje de coordenadas                      ³");
 gotoxy(left, 17);
 printf("³i: cambia a la ecuaci¢n previa                       ³");
 gotoxy(left, 18);
 printf("³o: cambia a la ecuaci¢n siguiente                    ³");
 gotoxy(left, 19);
 printf("³T: aumenta el paso del tiempo                        ³");
 gotoxy(left, 20);
 printf("³t: disminuye el paso del tiempo                      ³");
 gotoxy(left, 21);
 printf("³?: despliega la ayuda                                ³");
 gotoxy(left, 22);
 printf("³ESC: TERMINA EL PROGRAMA                             ³");
 gotoxy(left, 23);
 printf("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ");
 getch();
}


//Funcion principal
void main(void){
 double xmin, ymin, xmax, ymax, detail, t = 0;
 double xfrec = 0.5, yfrec = 0.5;
 char prompt2[100];
 int magnification = 100;
 int angle = 0;
 detail = 17;
 xmin = -3;
 ymin = -3;
 xmax = 3;
 ymax = 3;
 _setcursortype(_NOCURSOR);
 init3dgraph();
 double x, y, z, h, w, d, xstep, ystep, newpage = 0, dt = 1;
 long pp = 0;
 int b, DrawGrid = 1, fun = 0;
 Point3d p[4];
 Point3d center;
 setcolor(4);
 h = .0125 * getmaxy();
 w = .5 * getmaxx();
 d = divix(h, 3500);
 center.x = 450;
 center.y = getmaxx() / 2;
 center.z = getmaxy() / 2;
 setvisualpage(1);
 scrmaxx = getmaxx();
 scrmaxy = getmaxy();
 do{
  xstep = (xmax - xmin) / detail;
  ystep = (ymax - ymin) / detail;
  if(DrawGrid){
	if(PolygonMode != 0){
	 setfillstyle(SOLID_FILL, 4);
	 bar(0, 0, scrmaxx, scrmaxy);
	}
	else cleardevice();
	for(z = 0; z <= scrmaxy; z += 24){
	 line3d(0, 0, z, 600, 0, z, h, w, d, 12);
	 lineto3d(600, scrmaxx, z, h, w, d, 12);
	 lineto3d(0, scrmaxx, z, h, w, d, 12);
	}
	for(y = 0; y <= scrmaxx; y += 32){
	 line3d(0, y, 0, 600, y, 0, h, w, d, 12);
	 lineto3d(600, y, scrmaxy, h, w, d, 12);
	 lineto3d(0, y, scrmaxy, h, w, d, 12);
	}
	for(x = 0; x <= 600; x += 30){
	 line3d(x, 0, 0, x, scrmaxx, 0, h, w, d, 12);
	 lineto3d(x, scrmaxx, scrmaxy, h, w, d, 12);
	 lineto3d(x, 0, scrmaxy, h, w, d, 12);
	 lineto3d(x, 0, 0, h, w, d, 12);
	}
  }
  else{
	setfillstyle(SOLID_FILL, 0);
	bar(0, 0, scrmaxx, scrmaxy);
  }
  for(x = xmin; x <= xmax; x += xstep){
	for(y = ymin; y <= ymax; y += ystep){
	 z = f(x, y, t, xfrec, yfrec, fun);
	 p[0].x = x;
	 p[0].y = y;
	 p[0].z = z;
	 p[1].x = x;
	 p[1].y = y + ystep;
	 p[1].z = f(p[1].x, p[1].y, t, xfrec, yfrec, fun);
	 p[2].x = x - xstep;
	 p[2].y = y + ystep;
	 p[2].z = f(p[2].x, p[2].y, t, xfrec, yfrec, fun);
	 p[3].x = x - xstep;
	 p[3].y = y;
	 p[3].z = f(p[3].x, p[3].y, t, xfrec, yfrec, fun);
	 for(int c = 0; c < 4; c++){
		p[c] = Scale(p[c], magnification, center);
	 }
	 Polygon3d(p, 4, h, w, d, 1, 9);
	 pp++;
	 if(kbhit()){
	  b = getch();
	  switch(b){
		case '+':
		case 'D':
		case 'd':
		 detail++;
		break;
		case '-':
		case 'F':
		case 'f':
		 detail--;
		 if(detail <= 3) detail = 3;
		 break;
		case 'g':
		case 'G':
		 DrawGrid++;
		 if(DrawGrid > 1) DrawGrid = 0;
	  }
	  setcolor(15);
	  sprintf(prompt2, "f(x)=sin(%1.1fx^2+%1.1fy^2+%1.1f)    Detalle: %d", xfrec, yfrec, t, (unsigned int)(detail));
	 }
	}
  }
  t += dt;
  switch(b){
	case 'x':
	case 'X':
	 xfrec = xfrec + 0.5;
	 if(xfrec > 5) xfrec = 0.0;
	break;
	case 'y':
	case 'Y':
	 yfrec = yfrec + 0.5;
	 if(yfrec > 5) yfrec = 0.0;
	break;
	case '>':
	 xmax = xmax + 1;
	 xmin = xmin - 1;
	 ymax = ymax + 1;
	 ymin = ymin - 1;
	break;
	case '<':
	 xmax = xmax - 1;
	 xmin = xmin + 1;
	 ymax = ymax - 1;
	 ymin = ymin + 1;
	break;
	case 'p':
	case 'P':
	 PolygonMode = PolygonMode + 1;
	 if(PolygonMode > 1) PolygonMode = 0;
	break;
	case 't':
	 dt -= 0.025;
	 if(dt < 0.025) dt = 0.025;
	 break;
	case 'T':
	 dt += 0.025;
	 break;
	case 'r':
	case 'R':
	 dt -= 0.1;
	 if(dt < 0.1) dt = 0.1;
	 break;
	case 'o':
	 fun = fun + 1;
	break;
	case 'i':
	 fun = fun - 1;
	 if(fun < 0) fun = 0;
	 break;
	case 'm':
	 magnification -= 5;
	 if(magnification <= 5) magnification = 5;
	 break;
	case 'M':
	 magnification += 5;
	 if(magnification > 200) magnification = 200;
	 break;
	case 'h':
	 h-=5;
	 if(h < 0) h = 0;
	 break;
	case 'H':
	 h+=5;
	 if(h > scrmaxy) h = scrmaxy;
	 break;
	case 's':
	 w-=5;
	 if(w < 0) w = 0;
	 break;
	case 'S':
	 w+=5;
	 if(w > scrmaxx) w = scrmaxx;
	 break;
	case 'a':
	 angle--;
	 if(angle < 1) angle = 1;
	 break;
	case 'A':
	 angle++;
	 if(angle > 179) angle = 179;
	 break;
	case '?':
	 displayhelp();
  }
  if(xmax <= 0) xmax = 1;
  if(xmin >= 0) xmin = -1;
  if(ymax <= 0) ymax = 1;
  if(ymin >= 0) ymin = -1;
  if(b != 27) b = 0;
  setcolor(15);
  switch(fun){
	case 0:
	 sprintf(prompt2, "f(x)=sin(%1.1fx+%1.1fy+%1.4f)    Puntos: %d", xfrec, yfrec, t, (unsigned int)((detail + 1) * (detail + 1)));
	break;
	case 1:
	 sprintf(prompt2, "f(x)=sin((%1.1f)(%1.4f))e-(xý+yý)    Puntos: %d", xfrec, t, (unsigned int)((detail + 1) * (detail + 1)));
	break;
	case 2:
	 sprintf(prompt2, "f(x)=sin(%1.1fxy + %1.1f)    Puntos: %d", xfrec, t, (unsigned int)((detail + 1) * (detail + 1)));
	 break;
	case 3:
	 sprintf(prompt2, "f(x)=cos(xý + yý + %1.4f)/(xý + yý + 1) Puntos: %d", t, (unsigned int)((detail + 1) * (detail + 1)));
	 break;
	default:
	 sprintf(prompt2, "f(x)=sin(%1.1fx+%1.1fy+%1.4f)    Puntos: %d", xfrec, yfrec, t, (unsigned int)((detail + 1) * (detail + 1)));
  }
  outtextxy(scrmaxx-scrmaxx+5, 5, prompt2);
  setvisualpage(newpage);
  newpage = newpage + 1;
  if(newpage > 1) newpage = 0;
  wtVerticalRetrace();
  setactivepage(newpage);
 }while(b != 27);
 closegraph();
 displaymessage();
 _setcursortype(_NORMALCURSOR);
}


