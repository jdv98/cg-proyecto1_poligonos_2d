#ifndef PROVINCIAS_H
#define PROVINCIAS_H

#include "dibujar.h"

typedef struct{
    int size;
    double ** vertices;
} POLIGONO;

typedef struct {
    int numero;
    int size;

    TEXTURA * textura;
    COLOR * color_mapa;
    COLOR * relleno_mapa;
    
    POLIGONO ** poligonos;
} PROVINCIA;

typedef struct {
    int size;
    PROVINCIA ** provincias;
} PROVINCIAS;

extern PROVINCIAS *provincias;

#endif