#ifndef CLIPPING_H
#define CLIPPING_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/***************************/
#include "viewport.h"
#include "dibujar.h"
#include "vertices.h"
/***************************/

void clipping_poligono(double **vertices,double *** nuevo_vertice,int * nuevo_vertice_size);

#endif