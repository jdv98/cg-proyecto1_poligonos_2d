#ifndef PROVINCIAS_H
#define PROVINCIAS_H

typedef struct{
    int size;
    double ** vertices;
} POLIGONO;

typedef struct {
    int numero;
    int size;
    
    POLIGONO ** poligonos;
} PROVINCIA;

typedef struct {
    int size;
    PROVINCIA ** provincias;
} PROVINCIAS;

extern PROVINCIAS *provincias;

#endif