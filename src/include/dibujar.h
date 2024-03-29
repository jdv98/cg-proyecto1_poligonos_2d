#ifndef DIBUJAR_H
#define DIBUJAR_H

#include <stddef.h>
#include <stdbool.h>

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

extern int RESOLUCION_H;
extern int RESOLUCION_W;

extern bool DIBUJANDO;

extern bool DIBUJAR_TEXTURA;
extern bool DIBUJAR_RELLENO;

void dibujar(int x, int y, COLOR * color);
void dibujar_mapa();

#include "algoritmo_bresenham.h"
#include "provincias.h"
#include "rellenado.h"
#include "clipping.h"

#endif