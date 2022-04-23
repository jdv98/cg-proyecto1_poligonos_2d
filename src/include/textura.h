#ifndef TEXTURA_H
#define TEXTURA_H

#include <MagickWand/MagickWand.h>
#include "dibujar.h"

#define ThrowWandException(wand) \
{ \
  char \
    *description; \
 \
  ExceptionType \
    severity; \
 \
  description=MagickGetException(wand,&severity); \
  (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); \
  description=(char *) MagickRelinquishMemory(description); \
  exit(-1); \
}

void cargar_textura(char * archivo, COLOR *** matriz_textura,int * height, int * width);
#endif