#ifndef DIBUJAR_H
#define DIBUJAR_H

#include <stddef.h>

typedef struct {
  double r;
  double g;
  double b;
} COLOR;

extern COLOR **buffer;
extern COLOR *color_mapa;

extern int resolucion;

void dibujar(int x, int y, COLOR * color);
void dibujar_poligono(double **vertices, int size);

#include "algoritmo_bresenham.h"
#include "provincias.h"
#include "rellenado.h"

#endif