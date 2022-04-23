#include "include/transformaciones.h"
#include "include/provincias.h"
#include "include/matriz.h"

double ** triangulo_a_matriz(double ** poligono){
    double ** nuevo= matriz_init(3,3,false);

    for (size_t i = 0; i < 3; i++)
    {
        nuevo[0][i]=poligono[i][0];
        nuevo[1][i]=poligono[i][1];
        nuevo[2][i]=1;
    }
    
    return nuevo;
}

double ** rotar_sobre_eje(double grados, double x, double y)
{
    double **m_trasladar = trasladar_matriz(x, y);
    double **m_rotate = rotar_matriz(grados);
    double **m_trasladar_inv = trasladar_matriz(-x, -y);

    matriz_mul_r(&m_trasladar, 3, 3, &m_rotate, 3, 3);
    matriz_mul_r(&m_trasladar, 3, 3, &m_trasladar_inv, 3, 3);

    free_matriz(&m_rotate,3);
    free_matriz(&m_trasladar_inv,3);

    return m_trasladar;
}

void multiplicar_provincias(double ** operador)
{
    POLIGONO *poligono_iter;
    PROVINCIA *provincia_iter;
    double ** triangulo_matriz;
    double ** resultado;

    for (size_t i = 0; i < provincias->size; i++)
    {
        provincia_iter = provincias->provincias[i];
        for (size_t j = 0; j < provincia_iter->size; j++)
        {
            triangulo_matriz=triangulo_a_matriz(provincia_iter->poligonos[j]->vertices);
            resultado = matriz_mul(&operador,3,3,&triangulo_matriz,3,3);

            for (size_t column = 0; column < 3; column++)
            {
                provincia_iter->poligonos[j]->vertices[column][0]=resultado[0][column];
                provincia_iter->poligonos[j]->vertices[column][1]=resultado[1][column];
            }
            free_matriz(&triangulo_matriz,3);
            free_matriz(&resultado,3);
        }
    }
}


void rotar(){
    double ** matriz_rotada=rotar_sobre_eje(0.5, 500, 500);

    matriz_mul_r(&provincias->log_cambios_matriz,3,3,&matriz_rotada,3,3);

    multiplicar_provincias(matriz_rotada);
}