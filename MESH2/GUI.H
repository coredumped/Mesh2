//---------------------------------------------------------------------------
//  GUI.h
//
//  ver 1.0
//    Cabecera encargada de la interfaz gr fica de usuario
//                                                       Juan V. Guerrero
//                                                                 1998
//---------------------------------------------------------------------------
#define HUNDIDO 0
#define ELEVADO 1


typedef struct{
 int x, y;
 int r, b;
 char caption[20];
 char status;
}Button;

extern void DrawPanel(int l, int t, int r, int b, int tipo);
extern void DrawMeshWindow();
extern void CreateButton(int x, int y, Button *btn, char *caption);
extern void DrawButton(Button btn);
extern int CheckIfPressed(Button *btn);
extern void Message(char *title, char *msg);
extern void CreateTab(int x, int y, Button *btn, char *caption);
extern void DrawTab(Button btn);
extern void DrawCommandPanel(int x, int y, int r, int b, Button Tab, int isactive);
extern int MeshTabPanel(Button Tab);
extern void DrawCommandPanel(int x, int y, int r, int b, Button Tab);
extern int MeshFxyPanel(int active);
extern int MeshOptionPanel(int active);
extern void MeshHelp();
