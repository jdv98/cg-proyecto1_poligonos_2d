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
 * @brief Matriz para mover en los ejes de un plano 2D
 * 
 * @param sx 
 * @param sy 
 * @return double** 
 */
double **escalar_matriz(double sx, double sy);

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
 * @brief Retorna matriz inversa de una matriz dada.
 *
 * @param matriz
 * @return double** 
 */
double ** matriz_inversa (double ***matriz1);

/**
 * @brief Libera la memoria de la matriz
 * 
 * @param matriz 
 * @param column 
 */
void free_matriz(double *** matriz, int column);

#endif