#ifndef VERTICES_H
#define VERTICES_H

typedef struct Vertices
{
    int entrada;
    bool no_dibujar;
    bool frame;
    double x;
    double y;
    struct Vertices *sig;
    struct Vertices *ant;
    struct Vertices *vecino;
} Vertices;

#endif