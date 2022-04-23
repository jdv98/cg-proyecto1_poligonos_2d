#ifndef DIBUJAR_H
#define DIBUJAR_H

#include <stddef.h>

typedef struct {
  double r;
  double g;
  double b;
} COLOR;

typedef struct {
  COLOR ** pixeles;
  int height;
  int width;
} TEXTURA;


extern COLOR **buffer;
extern COLOR *color_mapa;

extern int resolucion;

void dibujar(int x, int y, COLOR * color);

#include "algoritmo_bresenham.h"
#include "provincias.h"

#endif