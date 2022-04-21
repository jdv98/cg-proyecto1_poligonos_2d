#include "include/main.h"

COLOR **buffer;
COLOR *color_mapa;

int resolucion;
void draw_scene();
void init_colors();
void init_buffer();

int main(int argc, char **argv)
{
  const char *filename = "mapa/mapa.txt";
  if (argc < 2 || argc > 2)
  {
    (void)fprintf(stdout, "Usage: %s <resolucion>", argv[0]);
    exit(0);
  }
  else if (argc == 2)
  {
    resolucion = atoi(argv[1]);
  }

  cargarProvincias(filename);
  init_colors();
  init_buffer();
  init_viewport(0,0,resolucion-1,resolucion-1);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(resolucion, resolucion);
  glutCreateWindow("Proyecto 1 - Poligonos 2D");
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(0, resolucion, 0, resolucion);
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
  int i, j;
  for (i = 0; i < resolucion; i++)
  {
    for (j = 0; j < resolucion; j++)
    {
      glColor3f(buffer[i][j].r, buffer[i][j].g, buffer[i][j].b);
      glBegin(GL_POINTS);
      glVertex2i(i, j);
      glEnd();
    }
  }

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

  buffer = (COLOR **)malloc(resolucion * sizeof(COLOR));
  for (i = 0; i < resolucion; i++)
  {
    buffer[i] = (COLOR *)malloc(resolucion * sizeof(COLOR));
  }

  for (i = 0; i < resolucion; i++)
  {
    for (j = 0; j < resolucion; j++)
    {
      buffer[i][j].r = 0.0;
      buffer[i][j].g = 0.0;
      buffer[i][j].b = 0.0;
    }
  }
}