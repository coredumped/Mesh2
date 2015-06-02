//------------------------------------------------------------------------
//  3-D Engine
//
//     Motor para graficos 3-D
//  ver 1.0                                       Juan V. Guerrero   1998
//------------------------------------------------------------------------
#include<dos.h>
#include<alloc.h>
#include<mem.h>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>
#include"mesh.h"
#include"gui.h"
#include"supervga.h"
#include"mouse.h"

unsigned int maxcolors;
unsigned char rr[256], gg[256], bb[256];
float Xbuffer[8000], xvanish, yvanish, divi, deep3d;
float CosBuffer[720], SinBuffer[720];
int _vpage;

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


void ajustarpaleta(unsigned int c, char r, char g, char b){
 if(r < 0) r = 0;
 if(g < 0) g = 0;
 if(b < 0) b = 0;
 if(r > 63) r = 63;
 if(g > 63) g = 63;
 if(b > 63) b = 63;
 asm{
  mov ax, [c]
  mov dx, 0x03c8
  out dx, al
  mov al, [r]
  mov dx, 0x03c9
  out dx, al
  mov al, [g]
  mov dx, 0x03c9
  out dx, al
  mov al, [b]
  mov dx, 0x03c9
  out dx, al
 }
}

void iniciarModo13(){
 asm mov ax, 0x0013
 asm int 0x10
 maxcolors = 256;
}

void modoTexto(){
 asm mov ax, 0x0003
 asm int 0x10
 maxcolors = 16;
}

void putpixel13(int x, int y, int c){
 unsigned char *pixel = NULL;
 if(x < 0) return;
 if(x > 319) return;
 if(y < 0) return;
 if(y > 199) return;
 pixel = (unsigned char *)MK_FP(0xA000, x + y * 320);
 *pixel = (unsigned char)c;
}

float seno(float ang){
 if(ang < -360.0) ang += 360.0;
 if(ang > 360.0) ang -= 360.0;
 return SinBuffer[(int)(ang + 360)];
}

float coseno(float ang){
 if(ang < -360.0) ang += 360.0;
 if(ang > 360.0) ang -= 360.0;
 return CosBuffer[(int)(ang + 360)];
}

int cargarMSH(char *fname){
 unsigned w, h;
 int c, d;
 FILE *f;
 void *pic;
 f = fopen(fname, "rb");
 pic = MK_FP(0xA000, 0x0);
 memset(pic, '\0', 64000U);
 if(f == NULL){
  return 0;
 }
 fread(&w, sizeof(unsigned), 1, f);
 fread(&h, sizeof(unsigned), 1, f);
 for(c = 1; c < 256; c++){
  fread(&rr[c], 1, 1, f);
  fread(&gg[c], 1, 1, f);
  fread(&bb[c], 1, 1, f);
  ajustarpaleta(c, 0, 0, 0);
 }
 fread(pic, 1, 64000U, f);
 for(d = 1; d <= 63; d++){
  for(c = 1; c < maxcolors; c++){
   ajustarpaleta(c, d + (rr[c] - 63), d + (gg[c] - 63), d + (bb[c] - 63));
  }
  delay(10);
 }
 fclose(f);
 return 1;
}

void FadeToBlack(){
 int c, d;
 for(d = 63; d >= 1; d--){
  wtVerticalRetrace();
  for(c = 1; c < maxcolors; c++)
   ajustarpaleta(c, d + (rr[c] - 63), d + (gg[c] - 63), d + (bb[c] - 63));
  delay(8);
 }
}

double xxxtemp, lastxxxtemp, lastx;
void c3dto2d(Point3d *p, Point2d *punto){
 float xxxtemp;
 if(p->x == 0.0){
  punto->x = p->y;
  punto->y = p->z;
  return;
 }
 if(p->x == lastx) xxxtemp = lastxxxtemp;
 else
  if(p->x > -2000.0 && p->x < 6000.0) xxxtemp = Xbuffer[(int)(p->x + 2000.0)];
  else
   xxxtemp = 1.0 - pow(divi, p->x);

 punto->x = p->y + xxxtemp * (xvanish - p->y);
 punto->y = p->z + xxxtemp * (yvanish - p->z);
 lastx = p->x;
 lastxxxtemp = xxxtemp;
}

Point3d rotate(Point3d o, Point3d p, float theta, int axis){
 float xt, yt, zt, ct, st;
 xt = p.x - o.x;
 yt = p.y - o.y;
 zt = p.z - o.z;
 ct = coseno(theta);
 st = seno(theta);
 switch(axis){
  case YZ:
  case ZY:
   p.y = yt * ct - zt * st + o.y;
   p.z = zt * ct + yt * st + o.z;
   break;
  case XZ:
  case ZX:
   p.x = xt * ct - zt * st + o.x;
   p.z = zt * ct + xt * st + o.z;
   break;
  caseXY:
  default:
   p.x = xt * ct - yt * st + o.x;
   p.y = yt * ct + xt * st + o.y;
 }
 return p;
}

Point3d translate(Point3d p, float dx, float dy, float dz){
 p.x += dx;
 p.y += dy;
 p.z += dz;
 return p;
}

Point3d scale(Point3d p, float dx, float dy, float dz){
 p.x *= dx;
 p.y *= dy;
 p.z *= dz;
 return p;
}

float divix(){
 float xdivi;
 yvanish = fabs(yvanish);
 if(yvanish <= 0) yvanish = yvanish + 0.00001;
 xdivi = exp((log(yvanish)) / deep3d);
 return(1 / xdivi);
}


int init3d(){
 int gdriver = DETECT, gmode, err;
 float i, tmp;
 initgraph(&gdriver, &gmode, "c:\\borlandc\\bgi");
 err = graphresult();
 if(err != grOk){
  initgraph(&gdriver, &gmode, "c:\\bc5\\bgi");
  err = graphresult();
 }
 if(err != grOk){
  initgraph(&gdriver, &gmode, "a:\\");
  err = graphresult();
 }
 if(err != grOk) return 0;
 setgraphmode(VGAMED);
 yvanish = 3 * (getmaxy() / 2) / 4;
 xvanish = 3 * (getmaxx() / 2) / 4;
 restorecrtmode();
 iniciarModo13();
 cargarMSH("MeshII.msh");
 delay(2000);
 FadeToBlack();
 cargarMSH("meshload.msh");
 delay(2000);
 deep3d  = 8000;
 divi = divix();
 for(i = -2000.0; i < 6000.0; i++) Xbuffer[(int)(i + 2000)] = 1 - pow(divi, i);
 for(i = 0; i < 720.0; i++){
  tmp = i * M_PI_2 / 360 - M_PI_2;
  CosBuffer[(int)i] = cos(tmp);
  SinBuffer[(int)i] = sin(tmp);
 }
 _vpage = 0;
 FadeToBlack();
 setgraphmode(VGAMED);  // VGAMED proporciona 2 p ginas de video
 setvisualpage(1);
 maxcolors = getmaxcolor();
 return 1;
}

void close3d(){
 closegraph();
 modoTexto();
}


void flippage(){
 setvisualpage(_vpage);
 _vpage++;
 if(_vpage > 1) _vpage = 0;
 wtVerticalRetrace();
 setactivepage(_vpage);
 cleardevice();
}

void MeshTo2d(Point3d *p3, Point2d *p2, int n){
 register int i;
 for(i = 0; i < n; i++) c3dto2d(&p3[i], &p2[i]);
}

//Calcula el centro de un mesh
void CalcMeshCenter(Mesh *m){
 register int i;
 float dx = 0, dy = 0, dz = 0;
 for(i = 0; i < m->numpoints; i++){
  dx += m->p[i].x;
  dy += m->p[i].y;
  dz += m->p[i].z;
 }
 if(m->numpoints == 0){
  Message("ERROR", "CalcMeshCenter: imposible dividir por cero!!");
  close3d();
  exit(1);
 }
 m->center.x = dx / m->numpoints;
 m->center.y = dy / m->numpoints;
 m->center.z = dz / m->numpoints;
}


//Calcula la posicion del centro de un pol¡gono
void CalcPolygonCenter(Mesh *m, int poly){
 register int i;
 float dx = 0, dy = 0, dz = 0;
 for(i = 0; i < m->ref[poly].num; i++){
  dx+=m->p[m->ref[poly].points[i]].x;
  dy+=m->p[m->ref[poly].points[i]].y;
  dz+=m->p[m->ref[poly].points[i]].z;
 }
 if(m->ref[poly].num == 0){
  Message("ERROR", "CalcPolygonCenter: imposible dividir por cero!!");
  close3d();
  exit(1);
 }
 m->ref[poly].center.x = dx / m->ref[poly].num;
 m->ref[poly].center.y = dy / m->ref[poly].num;
 m->ref[poly].center.z = dz / m->ref[poly].num;
}


void RotateMesh(Point3d o, Mesh *m, float ang, int axis){
 float dx = 0, dy = 0, dz = 0;
 register int i;
 float ct, st, xt, yt, zt;
 ct = coseno(ang);
 st = seno(ang);
 for(i = 0; i < m->numpoints; i++){
  xt = m->p[i].x - o.x;
  yt = m->p[i].y - o.y;
  zt = m->p[i].z - o.z;
  switch(axis){
   case YZ:
   case ZY:
    m->p[i].y = yt * ct - zt * st + o.y;
    m->p[i].z = zt * ct + yt * st + o.z;
    break;
   case XZ:
   case ZX:
    m->p[i].x = xt * ct - zt * st + o.x;
    m->p[i].z = zt * ct + xt * st + o.z;
    break;
   caseXY:
   default:
    m->p[i].x = xt * ct - yt * st + o.x;
    m->p[i].y = yt * ct + xt * st + o.y;
  }
  dx += m->p[i].x;
  dy += m->p[i].y;
  dz += m->p[i].z;
 }
 m->center.x = dx / m->numpoints;
 m->center.y = dy / m->numpoints;
 m->center.z = dz / m->numpoints;
 for(i = 0; i < m->numpolys; i++)
  CalcPolygonCenter(m, i);
}

void ScaleMesh(Mesh *m, float dx, float dy, float dz){
 register int i;
 for(i = 0; i < m->numpoints; i++){
  m->p[i].x *= dx;
  m->p[i].y *= dy;
  m->p[i].z *= dz;
 }
}

void TranslateMesh(Mesh *m, float dx, float dy, float dz){
 register int i;
 float deltax = 0, deltay = 0, deltaz = 0;
 for(i = 0; i < m->numpoints; i++){
  m->p[i].x += dx;
  m->p[i].y += dy;
  m->p[i].z += dz;
  deltax += m->p[i].x;
  deltay += m->p[i].y;
  deltaz += m->p[i].z;
 }
 m->center.x = deltax / m->numpoints;
 m->center.y = deltay / m->numpoints;
 m->center.z = deltaz / m->numpoints;
 for(i = 0; i < m->numpolys; i++)
  CalcPolygonCenter(m, i);
}


void CalculateNormal(Point3d p1, Point3d p2, Point3d p3, Point3d *normal){
 float dx1, dx2;
 float dy1, dy2;
 float dz1, dz2;
 dx1 = p2.x - p1.x;
 dx2 = p3.x - p1.x;
 dy1 = p2.y - p1.y;
 dy2 = p3.y - p1.y;
 dz1 = p2.z - p1.z;
 dz2 = p3.z - p1.z;
 normal->x = dy1 * dz2 - dz1 * dy2;
 normal->y = dz1 * dx2 - dx1 * dz2;
 normal->z = dx1 * dy2 - dy1 * dx2;
}

void CalculateBright(Mesh *m, int poly){
 float incl;
 Point3d normal;
 CalculateNormal(m->p[m->ref[poly].points[0]], m->p[m->ref[poly].points[1]],
		 m->p[m->ref[poly].points[2]], &normal);

 incl = (normal.x + normal.y + normal.z) / (sqrt(3.0) * sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z));
 if(incl > 0.5 && incl <= 1.0) m->ref[poly].color = 9;
 else m->ref[poly].color = 1;
}


void DrawMesh(Mesh *m){
 register int i, j, poly[16], k;
 Point2d *p2d;
 p2d = (Point2d *)mmalloc(m->numpoints * sizeof(Point2d));
 if(p2d == NULL){
  Message("ERROR", "DrawMesh: Imposible crear buffer para conversion de 3-D a 2-D!!");
  close3d();
  exit(1);
 }

 //Convertir puntos 3-D a 2-D...
 MeshTo2d(m->p, p2d, m->numpoints);

 //Ordenar Poligonos...
 if(!m->isclosed && !m->transparent) SortMeshPolygons(m);

 //Ahora leer buffer de poligonos...
 for(i = 0; i < m->numpolys; i++){
  k = 0;
  if(m->ref[i].center.x > -((int)deep3d >> 2))
  if(m->transparent){
   setcolor(10);
   moveto(p2d[m->ref[i].points[0]].x, p2d[m->ref[i].points[0]].y);
   for(j = 1; j < 4; j++)
   lineto(p2d[m->ref[i].points[j]].x, p2d[m->ref[i].points[j]].y);
   lineto(p2d[m->ref[i].points[0]].x, p2d[m->ref[i].points[0]].y);
  }
  else
  if(m->isclosed){
   if(m->center.x >= m->ref[i].center.x){
    for(j = 0; j < m->ref[i].num; j++){
	poly[k++] = p2d[m->ref[i].points[j]].x;
     poly[k++] = p2d[m->ref[i].points[j]].y;
    }
    CalculateBright(m, i);
    if(m->ref[i].color == 1) setcolor(9);
    else setcolor(1);
    setfillstyle(SOLID_FILL, m->ref[i].color);
    fillpoly(m->ref[i].num, poly);
   }
  }
  else{
   for(j = 0; j < m->ref[i].num; j++){
    poly[k++] = p2d[m->ref[i].points[j]].x;
    poly[k++] = p2d[m->ref[i].points[j]].y;
   }
   CalculateBright(m, i);
   if(m->ref[i].color == 1) setcolor(9);
   else setcolor(1);
   setfillstyle(SOLID_FILL, m->ref[i].color);
   fillpoly(m->ref[i].num, poly);
  }
 }
 free(p2d);
}


void DestroyMesh(Mesh *m){
 int i;
 for(i = 0; i < m->numpolys; i++)
  free(m->ref[i].points);
 free(m->ref);
 free(m->p);
 m->ref = NULL;
 m->p   = NULL;
}

void ExchPolygons(polygon *p1, polygon *p2){
 int tnum, tcolor;
 int points[16];
 Point3d tcenter;
/* if(p1->num != p2->num){
			     Modificar tama¤o si son diferentes
			     y hacer otro procedimiento de
			     intercambio
 }*/
 tnum = p1->num;
 tcolor = p1->color;
 memcpy(points, p1->points, p1->num << 1);
 memcpy(p1->points, p2->points, p1->num << 1);
 memcpy(p2->points, points, p1->num << 1);
 tcenter.x = p1->center.x;
 tcenter.y = p1->center.y;
 tcenter.z = p1->center.z;
 p1->num   = p2->num;
 p1->color = p2->color;
 p1->center.x = p2->center.x;
 p1->center.y = p2->center.y;
 p1->center.z = p2->center.z;
 p2->num   = tnum;
 p2->color = tcolor;
 p2->center.x = tcenter.x;
 p2->center.y = tcenter.y;
 p2->center.z = tcenter.z;
}

void SortMeshPolygons(Mesh *m){
 char change;
 register int gap, i;
 gap = m->numpolys >> 1;
 do{
  do{
   change = 0;
   for(i = 0; i < m->numpolys - gap; i++){
    if(m->ref[i].center.x < m->ref[i + gap].center.x){
     ExchPolygons(&m->ref[i], &m->ref[i + gap]);
     change = 1;
    }
   }
  }while(change);
 }while((gap >>= 1) > 0);
}

void *mmalloc(unsigned size){
 if(size > coreleft()) return NULL;
 return malloc(size);
}

void CalculateMem(int w, int h){
 unsigned long np, npoly;
 unsigned long size;
 np = (unsigned long)(w * h);
 npoly = (w - 1) * (h - 1);
 size = (unsigned long)sizeof(Mesh) + (unsigned long)sizeof(Point3d) * np + (unsigned long)sizeof(polygon) * npoly * 8 +
	(unsigned long)sizeof(Point2d) * np;
 if(size > coreleft()){
  Message("Error", "Imposible ejecutar Mesh II: no hay memoria disponible!!");
  close3d();
  exit(1);
 }
}

void GenerateFxyMesh(Mesh *m, float xmin, float ymin, float xmax, float ymax,
		     float ancho, float largo, int fx){

 int i, j, k;
 char xc = 9;
 float x, y, xstep, ystep, temp1, temp2;
 m->numpoints = ancho * largo;
 m->numpolys = (ancho - 1) * (largo - 1);
 m->isclosed = 0;
 m->transparent = 0;
 CalculateMem(ancho, largo);
 m->p = (Point3d *)mmalloc(m->numpoints * sizeof(Point3d));
 if(m->p == NULL){
  Message("ERROR", "GenerateFxyMesh: Imposible crear buffer 3-D para hacer FxyMesh!!");
  close3d();
  exit(1);
 }
 m->ref = (polygon *)mmalloc(m->numpolys * sizeof(polygon));
 if(m->ref == NULL){
  free(m->p);
  Message("ERROR", "GenerateFxyMesh: Imposible crear buffer de poligonos para FxyMesh!!");
  close3d();
  exit(1);
 }
 for(i = 0; i < m->numpolys; i++){
  m->ref[i].num = 4;
  m->ref[i].points = (int *)mmalloc(m->ref[i].num);
  if(m->ref[i].points == NULL){
   DestroyMesh(m);
   Message("ERROR", "GenerateFxyMesh: Imposible crear buffer para poligono!!");
   close3d();
   exit(1);
  }
 }
 xstep = (xmax - xmin) / largo;
 ystep = (ymax - ymin) / ancho;
 i = 0;
 //Generando puntos 3-D...
 for(x = xmin; x < xmax; x += xstep){
  for(y = ymin; y < ymax; y += ystep){
   m->p[i].x = x;
   m->p[i].y = y;
   //---------Define las funciones que le da forma al MeshII----------------//
   switch(fx){
    case 0:
     m->p[i].z = -sin(x * y);
     break;
    case 1:
     m->p[i].z = cos(x * x + y * y) / (x * x + y * y + 0.5);
     break;
    case 2:
     m->p[i].z = 0.333 * x * x - 0.333 * y * y;
	break;
    case 3:
     m->p[i].z = -sin(x + y);
     break;
    case 4:
     m->p[i].z = -cos(pow(y, 2)) * exp(-hypot(x, y));
     break;
    case 5:
     m->p[i].z = 0.3333 * cos(2 * x + y + 0.02) +
		 0.3333 * cos(2 * y + x + 0.1) +
		 0.3333 * cos(3 * x + 3 * y + 0.01) +
		 0.3333 * cos(x + y + 0.001);
     break;
    case 6:
     m->p[i].z = -0.1 * exp(-x) * sin(y);
     break;
    case 7:
     m->p[i].z = 4 * x / (x * x + y * y + 1);
     break;
    case 8:
	m->p[i].z = sin(2 * x) + cos (2 * y);
     break;
    case 9:
     m->p[i].z = log(fabs(x * x + y * y + 1));
     break;
    case 10:
     m->p[i].z = -0.5 * (x * x + 4 * y * y) * exp(1 - x * x - y * y);
	break;
    case 11:
     m->p[i].z = -(0.5 - x * x + y * y) * exp(1 - x * x - y * y);
     break;
    case 12:
     m->p[i].z = -(2.0 - pow(x * x + y * y, 1.0 / 3.0));
     break;
    case 13:
     temp1 = sin(x * y);
     temp2 = x * y;
     if(temp2 == 0) m->p[i].z = -1.0;
     else m->p[i].z = -temp1 / temp2;
     break;
    case 14:
     m->p[i].z = -(-pow(x, 3.0) + 4 * x * y - 2 * pow(y, 2.0));
     if(m->p[i].z < -1.0) m->p[i].z = -1.0;
     if(m->p[i].z > 2.0) m->p[i].z = 4.0;
     break;
    case 15:
     temp1 = 3 * x * y;
	temp2 = x * x + y * y;
     if(temp2 == 0.0) m->p[i].z = 0;
     else m->p[i].z =  temp1 / temp2;
     break;
    case 16:
     m->p[i].z = sin(x * x + y * y - 0.01);   //Inventada, verificar
     break;
    case 17:
     m->p[i].z = (x * x + y * y) / -3.0;
     break;
    case 18:
     m->p[i].z = x * x * sin(y) / 3.0;
     break;
    case 19:
     m->p[i].z = -cos(x * y);
   }
   i++;
  }
 }
 k = 0;
 //Conectando puntos para formar los poligonos...
 for(i = 0; i < (largo - 1); i++){
  for(j = 0; j < (ancho - 1); j++){
   m->ref[k].points[0] = i + largo * j;
   m->ref[k].points[1] = i + largo * (j + 1);
   m->ref[k].points[2] = i + largo * (j + 1) + 1;
   m->ref[k].points[3] = i + largo * j + 1;
   CalcPolygonCenter(m, k);
   m->ref[k].color = xc;
   m->ref[k].center.x = 0;
   m->ref[k].center.y = 0;
   m->ref[k].center.z = 0;
   k++;
  }
 }
 //Calcular el centro del FxyMesh...
 CalcMeshCenter(m);
}


void gradiente(int brillo){
 int c, rc;
 for(c = 0; c < 64; c++)    ajustarpaleta(c, brillo + c, brillo, brillo);
 for(c = 64, rc = 63; c < 128; c++, rc--)  ajustarpaleta(c, brillo + rc, brillo + rc , brillo);
 for(c = 128; c < 192; c++) ajustarpaleta(c, 0, brillo + c - 128, brillo + c - 128);
 for(c = 192, rc = 63; c < 256; c++, rc--) ajustarpaleta(c, brillo, brillo, brillo + rc);
}


//Renderizar el gradiente de niveles del mesh
void RenderMesh(float xmin, float ymin, float xmax, float ymax, int fx){
 double deltax, deltay, temp1, temp2, x, y, z;
 int sx, sy;
 int c, key, brillo = 0;
 restorecrtmode();
 if(!SetSVGAMode(0x101)){
  setactivepage(0);
  setvisualpage(0);
  Message("ERROR", "Imposible iniciar modo de video VESA 640x480!!");
  return;
 }
 deltax = (xmax - xmin) / (float)SVGAgetmaxx();
 deltay = (ymax - ymin) / (float)SVGAgetmaxy();
 gradiente(brillo);
 for(sy = 0; sy < SVGAgetmaxy(); sy++){
  for(sx = 0; sx < SVGAgetmaxx(); sx++){
   x = xmin + (float)(sx * deltax);
   y = ymin + (float)(sy * deltay);
   switch(fx){
    case 0:
	z = sin(x * y) + 1;
	break;
    case 1:
	temp1 = x * x;
	temp2 = y * y;
	z = cos(temp1 + temp2) / (temp1 + temp2 + 0.5) + 1;
	break;
    case 2:
	temp1 = x * x;
	temp2 = y * y;
	z = 0.333 * temp1 - 0.333 * temp2;
	break;
    case 3:
	z = -sin(x + y);
	break;
    case 4:
	z = cos(pow(y, 2.0)) * exp(-hypot(x, y)) + 1;
	z += 1;
	break;
    case 5:
	z = 0.3333 * cos(2.0 * x + y + 0.02) +
	 0.3333 * cos(2.0 * y + x + 0.1) +
	 0.3333 * cos(3.0 * x + 3.0 * y + 0.01) +
	 0.3333 * cos(x + y + 0.001);
	z = z * 2 / 2.6664 + 1;
	break;
    case 6:
	z = 0.1 * exp(-x) * sin(y);
	break;
    case 7:
	temp1 = x * x;
	temp2 = y * y;
	z = 4.0 * x / (temp1 + temp2 + 1.0);
	break;
    case 8:
	z = sin(2.0 * x) + cos (2.0 * y);
	break;
    case 9:
	z = log(fabs(x * x + y * y + 1));
	break;
    case 10:
	temp1 = x * x;
	temp2 = y * y;
	z = 0.5 * (temp1 + 4 * temp2) * exp(1.0 - temp1 - temp2);
	break;
    case 11:
	temp1 = x * x;
	temp2 = y * y;
	z = (0.5 - temp1 + temp2) * exp(1.0 - temp1 - temp2);
	break;
    case 12:
	z = (2.0 - pow(x * x + y * y, 1.0 / 3.0));
	break;
    case 13:
	temp1 = sin(x * y);
	temp2 = x * y;
	if(temp2 == 0) z = 1.0;
	else z = temp1 / temp2;
	break;
    case 14:
	z = (-pow(x, 3.0) + 4 * x * y - 2 * pow(y, 2.0));
	if(z < -1.0) z = -1.0;
	if(z > 2.0) z = 4.0;
	break;
    case 15:
	temp1 = 3.0 * x * y;
	temp2 = x * x + y * y;
	if(temp2 == 0.0) z = 0;
	else z =  temp1 / temp2;
	break;
    case 16:
	z = sin(x * x + y * y - 0.01) + 1.0;
	break;
    case 17:
	z = (x * x + y * y) / 3.0;
	break;
    case 18:
	z = x * x * sin(y) / 9.0;
	break;
    case 19:
	z = cos(x * y) + 1;
    }
    c = 128 * z / 2 + 128;
    if(c > 255) c = 255;
    SVGAputpixel(sx, sy, c);
   }
  c++;
  if(c > 255) c = 1;
 }
 do{
  key = getch();
  switch(key){
   case '+':
    brillo++;
    wtVerticalRetrace();
    gradiente(brillo);
    delay(5);
    break;
   case '-':
    brillo--;
    wtVerticalRetrace();
    gradiente(brillo);
    delay(5);
  }
 }while(key != 27);
 for(; brillo > 0; brillo--){
  gradiente(brillo);
  delay(10);
 }
 modoTexto();
 setgraphmode(VGAMED);
}