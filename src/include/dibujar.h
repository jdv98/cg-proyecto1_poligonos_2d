#ifndef DIBUJAR_H
#define DIBUJAR_H

typedef struct {
  double r;
  double g;
  double b;
} COLOR;

extern COLOR **buffer;
extern COLOR *color_mapa;

extern int resolucion;

void dibujar(int x, int y, COLOR * color);

#endif