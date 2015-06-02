//--------------------------------------------------------------------------
//    Mesh2.cpp
//    version: 2.0
//      Programa que permite la visualizaci¢n de graficas 3-D
//  						  por:     Juan V. Guerrero
//--------------------------------------------------------------------------

#include<dos.h>
#include<stdio.h>
#include<bios.h>
#include<conio.h>
#include<graphics.h>
#include"mesh.h"
#include"scancode.h"
#include"mouse.h"
#include"gui.h"

int main(){
 char ok = 1;               //Bandera que mantiene el flujo del programa
 char FxyActivate = 0;      //Indica si se debe activar el panel de funciones
 char OpActivate = 1;       //Indica si se debe activar el panel de opciones
 char status[80];
 int dontrotate = 0;
 Button salir, ayuda, render, transp;
 Button Tab[3];
 int key, axis, FxyGraph, Option;
 int ancho, largo, fx;
 float delta, theta, alfa = 0.0, beta = 0.0, gama = 0.0;
 Point3d center = { 450.0, 239.0, 131.0};
 Mesh mesh;
 ancho = 10.0;
 largo = 10.0;
 if(!IsMousePresent()){
  close3d();
  printf("\nImposible ejecutar si no hay un Mouse presente!!\n");
  printf("Para resolver el problema cargue un driver para mouse, el programa incluye un\n"
	    "driver. Para cargarlo teclee MOUSE en la l¡nea de comandos");
  return 1;
 }
 if(!init3d()){
  printf("\nERROR - BGI No puede encontrar driver\n");
  return 1;
 }
 CalculateMem(ancho, largo);
 FxyGraph = 0;
 fx = FxyGraph;
 GenerateFxyMesh(&mesh, -3.0, -3.0, 3.0, 3.0, ancho, largo, FxyGraph);
 ScaleMesh(&mesh, 60.0, 60.0, 60.0);
 TranslateMesh(&mesh, center.x, center.y, center.z);
 center.x = mesh.center.x;
 center.y = mesh.center.y;
 center.z = mesh.center.z;
 delta = 15.0;
 CreateTab(620, 100, &Tab[0], "Funciones");
 CreateTab(620, 14, &Tab[1], "Opciones");
 CreateButton(7, 326, &salir, "Salir");
 CreateButton(59, 326, &ayuda, "Ayuda");
 CreateButton(110, 326, &transp, "Transparente");
 CreateButton(217, 326, &render, "Gradiente de nivel");
 axis = XY;
 theta = delta;
 do{
  if(bioskey(1)) key = bioskey(0);
  switch(key){
   case 0:
    break;
   case SC_ESC:
    ok = 0;
    break;
   case SC_F2:
    delta += 1;
    theta = delta;
    if(theta > 45) theta = 0;
    key = 0;
    break;
   case SC_F3:
    delta -= 1;
    theta = delta;
    if(theta < 0) theta = 0;
    key = 0;
    break;
   case SC_ARRIBA:
    TranslateMesh(&mesh, 10.0, 0.0, 0.0);
    key = 0;
    break;
   case SC_ABAJO:
    TranslateMesh(&mesh, -10.0, 0.0, 0.0);
    key = 0;
    break;
   case SC_DER:
    TranslateMesh(&mesh, 0.0, 10.0, 0.0);
    key = 0;
    break;
   case SC_IZQ:
    TranslateMesh(&mesh, 0.0, -10.0, 0.0);
    key = 0;
    break;
   case SC_INICIO:
    TranslateMesh(&mesh, 0.0, 0.0, -10.0);
    key = 0;
    break;
   case SC_FIN:
    TranslateMesh(&mesh, 0.0, 0.0, 10.0);
    key = 0;
    break;
   case SC_F1:
    MeshHelp();
    key = 0;
    break;
   case SC_ENTER:
    if(++dontrotate > 1) dontrotate = 0;
    key = 0;
    break;
  }
  if(!dontrotate){
   center.x = mesh.center.x;
   center.y = mesh.center.y;
   center.z = mesh.center.z;
   RotateMesh(center, &mesh, theta, axis);
   if((axis == XY) || (axis == YX)) alfa+=theta;
   if((axis == ZY) || (axis == YZ)) beta+=theta;
   if((axis == XZ) || (axis == ZX)) gama+=theta;
   if(alfa > 360.0) alfa -= 360.0;
   if(alfa < -360.0) alfa += 360.0;
   if(beta > 360.0) beta -= 360.0;
   if(beta < -360.0) beta += 360.0;
   if(gama > 360.0) gama -= 360.0;
   if(gama < -360.0) gama += 360.0;
  }
  sprintf(status, "Posici¢n: X=%5.2f Y=%5.2f Z=%5.2f",
	  mesh.center.x, mesh.center.y, mesh.center.z);
  DrawMeshWindow();
  DrawCommandPanel(486, 14, 620, 346, Tab[0], FxyActivate);
  DrawCommandPanel(486, 14, 620, 346, Tab[1], OpActivate);
  setcolor(0);
  outtextxy(17, 285, status);
  sprintf(status, "Angulos: Alfa=%03g§ Beta=%03g§ Gama=%03g§", alfa, beta, gama);
  outtextxy(17, 300, status);
  sprintf(status, "Funci¢n #%d", fx + 1);
  setcolor(15);
  outtextxy(100, 2, status);
  if(bioskey(1)) key = bioskey(0);
  setviewport(3, 13, 482, 262, 1);
  DrawMesh(&mesh);
  setviewport(0, 0, 639, 349, 1);
  CheckIfPressed(&salir);
  CheckIfPressed(&ayuda);
  CheckIfPressed(&render);
  CheckIfPressed(&transp);
  DrawButton(salir);
  DrawButton(ayuda);
  DrawButton(render);
  DrawButton(transp);
  if(transp.status == HUNDIDO)
   if(++mesh.transparent > 1) mesh.transparent = 0;
  if(salir.status == HUNDIDO){
   DrawButton(salir);
   UpdateCursor();
  }
  if(MeshTabPanel(Tab[0])){
   FxyActivate = 1;
   OpActivate = 0;
  }
  if(MeshTabPanel(Tab[1])){
   FxyActivate = 0;
   OpActivate = 1;
  }
  FxyGraph = MeshFxyPanel(FxyActivate);
  Option   = MeshOptionPanel(OpActivate);
  if(FxyActivate) DrawCommandPanel(486, 14, 620, 346, Tab[0], 1);
  else if(OpActivate) DrawCommandPanel(486, 14, 620, 346, Tab[1], 1);
  switch(Option){
   case -1:
    break;
   case 0:
    axis = YZ;
    theta = delta;
    if(dontrotate == 1) dontrotate = 0;
    break;
   case 1:
    axis = YZ;
    theta = -delta;
    if(dontrotate == 1) dontrotate = 0;
    break;
   case 2:
    axis = XZ;
    theta = delta;
    if(dontrotate == 1) dontrotate = 0;
    break;
   case 3:
    axis = XZ;
    theta = -delta;
    if(dontrotate == 1) dontrotate = 0;
    break;
   case 4:
    axis = XY;
    theta = delta;
    if(dontrotate == 1) dontrotate = 0;
    break;
   case 5:
    axis = XY;
    theta = -delta;
    if(dontrotate == 1) dontrotate = 0;
    break;
   case 6:
    TranslateMesh(&mesh, 10.0, 0.0, 0.0);
    break;
   case 7:
    TranslateMesh(&mesh, -10.0, 0.0, 0.0);
    break;
   case 8:
    TranslateMesh(&mesh, 0.0, 5.0, 0.0);
    break;
   case 9:
    TranslateMesh(&mesh, 0.0, -5.0, 0.0);
    break;
   case 10:
    TranslateMesh(&mesh, 0.0, 0.0, -5.0);
    break;
   case 11:
    TranslateMesh(&mesh, 0.0, 0.0, 5.0);
    break;
   case 12:
    if(++dontrotate > 1) dontrotate = 0;
  }
  if(render.status == HUNDIDO)
   RenderMesh(-3.0, -3.0, 3.0, 3.0, fx);
  if(FxyGraph > -1){
   DestroyMesh(&mesh);
   GenerateFxyMesh(&mesh, -3.0, -3.0, 3.0, 3.0, ancho, largo, FxyGraph);
   ScaleMesh(&mesh, 60.0, 60.0, 60.0);
   TranslateMesh(&mesh, center.x, center.y, center.z);
   FxyActivate = 0;
   OpActivate = 1;
   fx = FxyGraph;
  }
  UpdateCursor();
  flippage();
  if(ayuda.status == HUNDIDO) MeshHelp();
  while(salir.status == HUNDIDO){
   CheckIfPressed(&salir);
   ok = 0;
  }
  if(bioskey(1)) key = bioskey(0);
 }while(ok);
 DestroyMesh(&mesh);
 close3d();
 iniciarModo13();
 cargarMSH("gracias.msh");
 delay(4000);
 FadeToBlack();
 cargarMSH("g1.msh");
 delay(4000);
 FadeToBlack();
 cargarMSH("g2.msh");
 delay(4000);
 FadeToBlack();
 cargarMSH("g3.msh");
 delay(4000);
 FadeToBlack();
 cargarMSH("g4.msh");
 delay(4000);
 FadeToBlack();
 cargarMSH("g5.msh");
 delay(4000);
 FadeToBlack();
 cargarMSH("credits.msh");
 getch();
 FadeToBlack();
 modoTexto();
}