#include "include/dibujar.h"

double **matriz_dibujo = NULL;
int matriz_size = 0;

void dibujar(int x, int y, COLOR *color)
{
    buffer[x][y] = (COLOR)*color;
}

void free_matriz_dibujo(double ***matriz, int *matriz_size)
{
    for (size_t i = 0; i < (*matriz_size); i++)
    {
        free((*matriz)[i]);
    }
    free((*matriz));
    (*matriz) = malloc(0);
    (*matriz_size) = 0;
}

void dibujar_poligono(double **vertices, int size)
{
    if (matriz_dibujo == NULL)
        matriz_dibujo = malloc(0);
    clipping_poligono(vertices, size, &matriz_dibujo, &matriz_size);
    if (matriz_size)
    {
        for (size_t z = 0; z < matriz_size - 1; z++)
        {
            bresenham((int)matriz_dibujo[z][0], (int)matriz_dibujo[z][1], (int)matriz_dibujo[z + 1][0], (int)matriz_dibujo[z + 1][1], color_mapa);
        }
        free_matriz_dibujo(&matriz_dibujo, &matriz_size);
    }
}

void reset_buffer()
{
    for (int i = 0; i < resolucion; i++)
    {
        for (int j = 0; j < resolucion; j++)
        {
            buffer[i][j].r = 0.0;
            buffer[i][j].g = 0.0;
            buffer[i][j].b = 0.0;
        }
    }
}

void dibujar_mapa()
{
    reset_buffer();
    POLIGONO *poligono_iter;
    PROVINCIA *provincia_iter;
    for (size_t i = 0; i < provincias->size; i++)
    {
        provincia_iter = provincias->provincias[i];
        for (size_t j = 0; j < provincia_iter->size; j++)
        {
            poligono_iter = provincia_iter->poligonos[j];
            dibujar_poligono(provincia_iter->poligonos[j]->vertices, provincia_iter->poligonos[j]->size);
        }
    }
}