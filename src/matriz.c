#include "include/matriz.h"

double **matriz_init(int row, int column, bool identidad)
{
    double **matriz = malloc(row * sizeof(double *));

    for (size_t i_row = 0; i_row < row; i_row++)
    {
        matriz[i_row] = malloc(column * sizeof(double));

        for (size_t i_column = 0; i_column < column; i_column++)
        {
            matriz[i_row][i_column] = 0;
        }
    }

    if (identidad)
    {
        int max = row;
        if (max > column)
            max = column;

        for (size_t i = 0; i < max; i++)
        {
            matriz[i][i] = 1;
        }
    }

    return matriz;
}

double **rotar_matriz(double angle)
{
    double **matriz = matriz_init(3, 3, true);

    matriz[0][0] = cos(angle);
    matriz[0][1] = -sin(angle);

    matriz[1][0] = sin(angle);
    matriz[1][1] = cos(angle);

    return matriz;
}

double **trasladar_matriz(double t_x, double t_y)
{
    double **matriz = matriz_init(3, 3, true);

    matriz[0][2] = t_x;
    matriz[1][2] = t_y;

    return matriz;
}

double ** escalar_matriz(double sx, double sy)
{
    double **matriz = matriz_init(3, 3, true);

    matriz[0][0] = sx;
    matriz[1][1] = sy;

    return matriz;
}

double **zoom_matriz(double z, double xc, double yc)
{
    double **matriz = matriz_init(3, 3, true);

    matriz[0][0] = z;
    matriz[1][1] = z;

    matriz[0][2] = xc - xc * z;
    matriz[1][2] = yc - yc * z;

    return matriz;
}

void matriz_mul_r(double ***matriz1, int r1, int c1, double ***matriz2, int r2, int c2)
{
    double **result;

    if (c1 == r2)
    {
        result = matriz_init(r1, c2, false);
        for (size_t row = 0; row < r1; row++)
        {
            for (size_t column = 0; column < c2; column++)
            {
                for (size_t i = 0; i < c2; i++)
                {
                    result[row][column]+=(*matriz1)[row][i]*(*matriz2)[i][column];
                }                
            }
        }
        free_matriz(matriz1,c1);
        (*matriz1)=result;
    }
}

double ** matriz_mul(double ***matriz1, int r1, int c1, double ***matriz2, int r2, int c2)
{
    double **result=NULL;

    if (c1 == r2)
    {
        result = matriz_init(r1, c2, false);
        for (size_t row = 0; row < r1; row++)
        {
            for (size_t column = 0; column < c2; column++)
            {
                for (size_t i = 0; i < c1; i++)
                {
                    result[row][column]+=(*matriz1)[row][i]*(*matriz2)[i][column];
                }                
            }
        }
    }
    return result;
}

double ** matriz_inversa (double ***matrizT)
{
    double ** matrizI = matriz_init(3,3,true);
    return matrizI;
}

void free_matriz(double *** matriz,int column){
    for (size_t i = 0; i < column; i++)
    {
        free((*matriz)[i]);
        (*matriz)[i]=NULL;
    }
    
    free((*matriz));
    (*matriz)=NULL;
}

double ** inversa_3x3(double ** invertir){
    double determinante=
        invertir[0][0]*( (invertir[1][1]*invertir[2][2]) - (invertir[2][1]*invertir[1][2]) )-
        invertir[0][1]*( (invertir[1][0]*invertir[2][2]) - (invertir[2][0]*invertir[1][2]) )+
        invertir[0][2]*( (invertir[1][0]*invertir[2][1]) - (invertir[2][0]*invertir[1][1]) );

    double ** inversa=matriz_init(3,3,false);

    inversa[0][0]=((invertir[1][1]*invertir[2][2])-(invertir[1][2]*invertir[2][1]))/determinante;
    inversa[1][0]=((invertir[1][2]*invertir[2][0])-(invertir[1][0]*invertir[2][2]))/determinante;
    inversa[2][0]=((invertir[1][0]*invertir[2][1])-(invertir[1][1]*invertir[2][0]))/determinante;
    
    inversa[0][1]=((invertir[0][2]*invertir[2][1])-(invertir[0][1]*invertir[2][2]))/determinante;
    inversa[1][1]=((invertir[0][0]*invertir[2][2])-(invertir[0][2]*invertir[2][0]))/determinante;
    inversa[2][1]=((invertir[0][1]*invertir[2][0])-(invertir[0][0]*invertir[2][1]))/determinante;
    
    inversa[0][2]=((invertir[0][1]*invertir[1][2])-(invertir[0][2]*invertir[1][1]))/determinante;
    inversa[1][2]=((invertir[0][2]*invertir[1][0])-(invertir[0][0]*invertir[1][2]))/determinante;
    inversa[2][2]=((invertir[0][0]*invertir[1][1])-(invertir[0][1]*invertir[1][0]))/determinante;

    return inversa;
}