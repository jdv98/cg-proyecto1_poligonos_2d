#include "include/keys.h"

void dibujar_mapa(int div);

void normal_keys(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27: // Esc
    exit(0);
    break;
  
  case 49:
    dibujar_mapa(700);
    break;

  default:
    break;
  }
}

void special_keys(int key, int x, int y)
{
  switch (key)
  {
  default:
    break;
  }
}

void dibujar_mapa(int div)
{
  int x0, x1, y0, y1;

  for (size_t i = 0; i < provincias->size; i++)
  {
    PROVINCIA * provincia_iter = provincias->provincias[i];
    for (size_t j = 0; j < provincia_iter->size; j++)
    {
      POLIGONO * poligono_iter = provincia_iter->poligonos[j];
      for (size_t k = 0; k < poligono_iter->size - 1; k++)
      {
        x0 = (int)(poligono_iter->vertices[k][0] / div);
        y0 = (int)(poligono_iter->vertices[k][1] / div);
        x1 = (int)(poligono_iter->vertices[k + 1][0] / div);
        y1 = (int)(poligono_iter->vertices[k + 1][1] / div);
        bresenham(x0, y0, x1, y1, color_mapa);
      }
    }
  }
  glutPostRedisplay();
}