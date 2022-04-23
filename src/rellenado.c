#include "include/rellenado.h"

void rellenado_Poligono(double ***matriz, int *size,COLOR *color,double ***textura)
{
	double  Y, dx, dy, xi[100], gm, gd, temp;
	int n,k=0;

	float slope[100];
	n = (*size);
	double ymin = (*matriz)[0][1];
	double ymax = (*matriz)[0][1];
	for (int i = 0; i < n; i++)
	{
		//bresenham((int)(*matriz)[i][0], (int)(*matriz)[i][1], (int)(*matriz)[i + 1][0], (int)(*matriz)[i + 1][1], color_mapa);
		if (ymin > (*matriz)[i][1])
		{
			ymin = (*matriz)[i][1];
		}
		if (ymax < (*matriz)[i][1])
		{
			ymax = (*matriz)[i][1];
		}
	}
	
	// x[n]=x[0];
	// y[n]=y[0];

	/***/
	(*size)++;
	(*matriz)=realloc((*matriz),(*size)*sizeof(double*));
	(*matriz)[n]=malloc(2*sizeof(double));
    /**/

	//double **n_matriz=realloc((*matriz),sizeof(double *)*((*size)+1));
	//matriz[n]=malloc(2*sizeof(double));
	(*matriz)[n][0] = (*matriz)[0][0];
	(*matriz)[n][1] = (*matriz)[0][1];
	for (int i = 0; i < n; i++)

	{

		// dx=x[i+1]-x[i];
		dx = ((*matriz)[i + 1][0]) - ((*matriz)[i][0]);
		// dy=y[i+1]-y[i];
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

		int k = 0;

		for (int i = 0; i < n-1; i++)
		{

			// if(((y[i]<=j) && (y[i+1]>j)) || ((y[i]>j) && (y[i+1]<=j))){
			if ((((*matriz)[i][1] <= j) && ((*matriz)[i + 1][1] > j)) || (((*matriz)[i][1] > j) && ((*matriz)[i + 1][1] <= j)))
			{

				// xi[k]=(int)(x[i]+slope[i]*(j-y[i]));
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

			// setcolor(2);

			for (int i = 0; i < k; i += 2)
			{

				// line(xi[i],j,xi[i+1]+1,j);
				// delay(100);
				//bresenham((int)xi[i], (int)j, (int)xi[i + 1], (int)j,color_mapa);
				for (size_t p =(int)xi[i]; p < (int)xi[i + 1]; p++)
				{
					dibujar(p,j,color_mapa);
				}
				
			}
		}
	}
}