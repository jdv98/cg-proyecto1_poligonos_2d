#ifndef MATRIZ_H
#define MATRIZ_H

#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/******************/
/******************/

/**
 * @brief Crea matriz en ceros o como matriz identidad
 *
 * @param row
 * @param column
 * @param identidad
 * @return double**
 */
double **matriz_init(int row, int column, bool identidad);

/**
 * @brief Crea una matriz 3x3 para girar en un plano 2D
 * 
 * @param angle 
 * @return double** 
 */
double **rotar_matriz(double angle);

/**
 * @brief Matriz para mover en los ejes de un plano 2D
 * 
 * @param t_x 
 * @param t_y 
 * @return double** 
 */
double **trasladar_matriz(double t_x, double t_y);


/**
 * @brief Zoom
 * 
 * @param z 
 * @param xc 
 * @param yc 
 * @return double** 
 */
double **zoom_matriz(double z, double xc, double yc);

/**
 * @brief Matriz escalar
 * 
 * @param sx //Estos son los valores que van a multiplicar a las x
 * @param sy //y estos a las y.
 * @return double** 
 */
double **escalar_matriz(double sx, double sy);

/**
 * @brief Multiplica 2 matrices y guarda el resultado en la primera matriz
 * 
 * @param matriz1 
 * @param r1 
 * @param c1 
 * @param matriz2 
 * @param r2 
 * @param c2 
 */
void matriz_mul_r(double ***matriz1, int r1, int c1, double ***matriz2, int r2, int c2);

/**
 * @brief Multiplica 2 matrices y guarda el resultado en la primera matriz
 *      //Segunda vercion.
 * 
 * @param matriz1 
 * @param fila1 
 * @param colu1 
 * @param matriz2 
 * @param fila2 
 * @param colu2 
 */
void matriz_mul_r_dos(double ***matriz1, int fila1, int colu1, double ***matriz2, int fila2, int colu2);


/**
 * @brief Multiplica 2 matrices y retorna la matriz resultante
 * 
 * @param matriz1 
 * @param r1 
 * @param c1 
 * @param matriz2 
 * @param r2 
 * @param c2 
 * @return double** 
 */
double ** matriz_mul(double ***matriz1, int r1, int c1, double ***matriz2, int r2, int c2);

/**
 * @brief Libera la memoria de la matriz
 * 
 * @param matriz 
 * @param column 
 */
void free_matriz(double *** matriz, int column);

#endif