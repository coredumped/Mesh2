//--------------------------------------------------------------------------
//   Mesh.h
//      Declaraciones de funciones y variables utilizadas en Mesh II
//
//                                                Juan V. Guerrero    1998
//   Mesh ver 2.0
//--------------------------------------------------------------------------

#define XY 1
#define YZ 2
#define XZ 3
#define YX 4
#define ZY 5
#define ZX 6
#define MAXFXY 20

extern float xvanish, yvanish;

typedef struct{
 int x;
 int y;
} Point2d;

typedef struct{
 float x;
 float y;
 float z;
} Point3d;

typedef struct{
 int num;         //Cantidad de puntos que forman el pol¡gono
 char color;      //Define el color del pol¡gono
 int *points;     //Puntero al indexador de puntos 2-D
 Point3d center;  //Almacena el centro del poligono
}polygon;

typedef struct{
 int numpoints;     //Cantidad de puntos en el Mesh
 int numpolys;      //Cantidad de pol¡gonos que lo forman
 char isclosed;     //Dice si se trata de un objeto cerrado o no
 char transparent;  //Indica si el mesh es transparente
 Point3d center;
 Point3d *p;        //Puntero al buffer de puntos 3-D
 polygon *ref;      //Puntero al buffer de poligonos
} Mesh;


extern int cargarMSH(char *fname);
extern void modoTexto();
extern void iniciarModo13();
extern void FadeToBlack();
extern int init3d();
extern void close3d();
extern Point3d rotate(Point3d o, Point3d p, float theta, int axis);
extern Point3d scale(Point3d p, float dx, float dy, float dz);
extern Point3d translate(Point3d p, float dx, float dy, float dz);
extern void DrawPolygon(Point3d *p, int n);
extern void DrawPolyLine(Point3d *p, int n);
extern void MeshTo2d(Point3d *p3, Point2d *p2, int n);
extern void DrawMesh(Mesh *m);
extern void CreateMesh(Mesh *m, int npoints, int npolys, int *npp);
extern void DestroyMesh(Mesh *m);
extern void CalcMeshCenter(Mesh *m);
extern void CalcPolygonCenter(Mesh *m, int poly);
extern void RotateMesh(Point3d o, Mesh *m, float ang, int axis);
extern void SortMeshPolygons(Mesh *m);
extern void  flippage();
extern void *mmalloc(unsigned size);
extern void CalculateMem(int w, int h);
extern void TranslateMesh(Mesh *m, float dx, float dy, float dz);
extern void ScaleMesh(Mesh *m, float dx, float dy, float dz);
extern void RenderMesh(float xmin, float ymin, float xmax, float ymax, int fx);
extern void GenerateFxyMesh(Mesh *m, float xmin, float ymin, float xmax,
			    float ymax, float ancho, float largo, int fx);
