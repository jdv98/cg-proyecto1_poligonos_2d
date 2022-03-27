#ifndef PROVINCIAS_H
#define PROVINCIAS_H

typedef struct{
    int size;
    double ** vertices;
} POLIGONO;

typedef struct {
    char * nombre;
    int size;
    
    POLIGONO * poligonos;
} PROVINCIA;

typedef struct {
    int size;
    PROVINCIA * provincias;
} PROVINCIAS;

extern PROVINCIAS *provincias;

#endif