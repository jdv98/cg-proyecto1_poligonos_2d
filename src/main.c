#include "include/main.h"

COLOR **buffer;
COLOR *color_mapa;

int RESOLUCION_H,RESOLUCION_W;
bool DIBUJAR_TEXTURA=false;
bool DIBUJAR_RELLENO=false;

void draw_scene();
void init_colors();
void init_buffer();

int main(int argc, char **argv)
{

  RESOLUCION_W = 1000;
  RESOLUCION_H = 1000;

  const char *filename = "mapa/mapa.txt";
  if (argc < 4 || argc > 4)
  {
    (void)fprintf(stdout, "Usage: %s <resolucion> <width> <height>\n\n", argv[0]);
    exit(0);
  }
  else if (argc == 4)
  {
    RESOLUCION_W = atoi(argv[2])*atoi(argv[1]);
    RESOLUCION_H = atoi(argv[3])*atoi(argv[1]);
  }

  cargarProvincias(filename);
  init_colors();
  init_buffer();
  init_viewport(0,0,RESOLUCION_W,RESOLUCION_H);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(RESOLUCION_W, RESOLUCION_H);
  glutCreateWindow("Proyecto 1 - Poligonos 2D");
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(0, RESOLUCION_W, 0, RESOLUCION_H);
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  glutDisplayFunc(draw_scene);
  glutKeyboardFunc(normal_keys);
  glutKeyboardUpFunc(normal_keys_up);
  glutSpecialFunc(special_keys);
  glutSpecialUpFunc(special_keys_up);
  glutMainLoop();
}

void draw_scene()
{
  dibujar_mapa();
  int i, j;
  
  glBegin(GL_POINTS);
  for (i = 0; i < RESOLUCION_W; i++)
  {
    for (j = 0; j < RESOLUCION_H; j++)
    {
      glColor3f(buffer[i][j].r, buffer[i][j].g, buffer[i][j].b);
      glVertex2i(i, j);
    }
  }
  glEnd();
  glFlush();
}

void init_colors()
{
  color_mapa = malloc(sizeof(COLOR));

  color_mapa->r = (double)1.0;
  color_mapa->g = (double)1.0;
  color_mapa->b = (double)1.0;
}

void init_buffer(){
  int i, j;

  buffer = (COLOR **)malloc(RESOLUCION_W * sizeof(COLOR));
  for (i = 0; i < RESOLUCION_W; i++)
  {
    buffer[i] = (COLOR *)malloc(RESOLUCION_H * sizeof(COLOR));
  }

  for (i = 0; i < RESOLUCION_W; i++)
  {
    for (j = 0; j < RESOLUCION_H; j++)
    {
      buffer[i][j].r = 0.0;
      buffer[i][j].g = 0.0;
      buffer[i][j].b = 0.0;
    }
  }
}