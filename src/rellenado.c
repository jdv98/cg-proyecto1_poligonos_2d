#include "include/rellenado.h"

COLOR * scanline_a_pantalla(TEXTURA ** xy,int x,int y){
	
	int xk=( ((*xy)->width)*x )/resolucion,
		yk=( ((*xy)->height)*y )/resolucion;

	return &(*xy)->pixeles[yk][xk];
}

void rellenado_Poligono(double ***matriz, int *size,COLOR *color,TEXTURA ** textura)
{
	double  Y, dx, dy, xi[(*size)+2], gm, gd, temp;
	int n,k=0;

	float slope[(*size)+2];
	n = (*size);
	double ymin = (*matriz)[0][1];
	double ymax = (*matriz)[0][1];

	for (int i = 0; i < n; i++)
	{
		if (ymin > (*matriz)[i][1])
			ymin = (*matriz)[i][1];

		if (ymax < (*matriz)[i][1])
			ymax = (*matriz)[i][1];
	}

	/***/
	(*size)++;
	(*matriz)=realloc((*matriz),(*size)*sizeof(double*));
	(*matriz)[n]=malloc(2*sizeof(double));
    /**/
	(*matriz)[n][0] = (*matriz)[0][0];
	(*matriz)[n][1] = (*matriz)[0][1];


	for (int i = 0; i < n; i++)
	{
		dx = ((*matriz)[i + 1][0]) - ((*matriz)[i][0]);
		dy = (*matriz)[i + 1][1] - (*matriz)[i][1];

		if (dy == 0)
			slope[i] = 1.0;

		if (dx == 0)
			slope[i] = 0.0;

		if (dx != 0 && dy != 0)
			slope[i] = (float)dx / dy;
	}

	for (int j = 0; j <= ymax; j++)
	{
		k = 0;
		for (int i = 0; i < n-1; i++)
		{
			if ((((*matriz)[i][1] <= j) && ((*matriz)[i + 1][1] > j)) || (((*matriz)[i][1] > j) && ((*matriz)[i + 1][1] <= j)))
			{
				xi[k] = ((*matriz)[i][0] + slope[i] * (j - (*matriz)[i][1]));
				k++;
			}
		}

		for (int m = 0; m < k - 1; m++)
		{
			for (int i = 0; i < k - 1; i++)
			{
				if (xi[i] > xi[i + 1])
				{
					temp = xi[i];
					xi[i] = xi[i + 1];
					xi[i + 1] = temp;
				}
			}

			for (int i = 0; i < k; i += 2)
			{
				for (size_t p =(int)xi[i]; p < (int)xi[i + 1]; p++)
				{
					if (DIBUJAR_TEXTURA)
						dibujar(p,j,scanline_a_pantalla(textura,p,j));
					else
						dibujar(p,j,color);
				}
				
			}
		}
	}
}