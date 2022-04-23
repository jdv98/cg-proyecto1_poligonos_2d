#include "include/main.h"

COLOR **buffer;
COLOR *color_mapa;
COLOR *rojo;

int resolucion;
void draw_scene();
void init_colors();
void init_buffer();
void prueba();

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
  
  //bresenham (0, 0, 999, 999, color_mapa);
  //glutDisplayFunc(prueba);
  prueba ();

  glutKeyboardFunc(normal_keys);
  glutKeyboardUpFunc(normal_keys_up);
  glutSpecialFunc(special_keys);
  glutSpecialUpFunc(special_keys_up);
  glutMainLoop();
}

void draw_scene()
{
  //dibujar_mapa();
  int i, j;
  
  glBegin(GL_POINTS);
  for (i = 0; i < resolucion; i++)
  {
    for (j = 0; j < resolucion; j++)
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
  
  rojo = malloc(sizeof(COLOR));
  rojo->r = (double)1.0;
  rojo->g = (double)0.0;
  rojo->b = (double)0.0;

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

void prueba () {

  double ** m_pt1 = matriz_init (3,3,false);
  double ** m_escalar = escalar_matriz (2, 2);
  double ** m_traslado = matriz_init (3,3,true);

  m_pt1 [0][0] = 200; m_pt1 [0][1] = 400; m_pt1 [0][2] = 400;
  m_pt1 [1][0] = 200; m_pt1 [1][1] = 200; m_pt1 [1][2] = 400;
  m_pt1 [2][0] = 1;   m_pt1 [2][1] = 1;   m_pt1 [2][2] = 1;
  
  bresenham ((int)m_pt1[0][0], (int)m_pt1[1][0], (int)m_pt1[0][1], (int)m_pt1[1][1], color_mapa);
  bresenham ((int)m_pt1[0][1], (int)m_pt1[1][1], (int)m_pt1[0][2], (int)m_pt1[1][2], color_mapa);
  bresenham ((int)m_pt1[0][2], (int)m_pt1[1][2], (int)m_pt1[0][0], (int)m_pt1[1][0], color_mapa);
  
  for (size_t i = 0; i < 3; i++)
  {
    printf("\nMatriz >> %lf %f %lf", m_pt1[i][0], m_pt1[i][1], m_pt1[i][2]);
  } printf("\n");
  
  matriz_mul_r_dos(&m_pt1,3,3,&m_escalar,3,3);
  //m_traslado [1][2] = -200; m_traslado [0][2] = -200; Aplicando esta traslacion obtenemos el anclaje a uno de los vertices.
  matriz_mul_r_dos(&m_pt1,3,3,&m_traslado,3,3);
  

  bresenham ((int)m_pt1[0][0], (int)m_pt1[1][0], (int)m_pt1[0][1], (int)m_pt1[1][1], rojo);
  bresenham ((int)m_pt1[0][1], (int)m_pt1[1][1], (int)m_pt1[0][2], (int)m_pt1[1][2], rojo);
  bresenham ((int)m_pt1[0][2], (int)m_pt1[1][2], (int)m_pt1[0][0], (int)m_pt1[1][0], rojo);
  
  for (size_t i = 0; i < 3; i++)
  {
    printf("\nMatriz trasl>> %lf %f %lf", m_traslado[i][0], m_traslado[i][1], m_traslado[i][2]);
  } printf("\n");

  for (size_t i = 0; i < 3; i++)
  {
    printf("\nMatriz >> %lf %f %lf", m_pt1[i][0], m_pt1[i][1], m_pt1[i][2]);
  } printf("\n");

  free_matriz (&m_pt1, 3); free_matriz (&m_escalar, 3); free_matriz (&m_traslado, 3);
  //bresenham (10, 10, 600, 600, color_mapa);
  printf("\nend --Pruebas\n");
}