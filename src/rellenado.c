void rellenarTriangulo(double **matriz,int size)
{
  int x0, x1, y0, y1;

  bresenham(200, 200, 500, 500, color_mapa, dibujar);
  bresenham(500, 500, 800, 200, color_mapa, dibujar);
  bresenham(200, 200, 800, 200, color_mapa, dibujar);
  
  //-------------------------------------------------------------
	int n,x[10],y[10],k=0,ymin=1000000,ymax=0,Y,dx,dy,xi[100],gm,gd,temp;

	float slope[100];
  n=5;
  
    x[0]=30; 
    y[0]=30;
    x[1]=30; 
    y[1]=150;
    x[2]=120; 
    y[2]=60;
    x[3]=120; 
    y[3]=120;
    x[4]=210; 
    y[4]=30;

    ymin=30;
    ymax=150;
  
 /*
    x[0]=200; 
    y[0]=200;
    x[1]=500; 
    y[1]=500;
    x[2]=800; 
    y[2]=200;

    ymin=200;
    ymax=500;
  */

	x[n]=x[0];y[n]=y[0];

	//draw polygon using all the edges

	for(int i=0;i<n;i++)

	{

		//line(x[i],y[i],x[i+1],y[i+1]);
    bresenham(x[i],y[i],x[i+1],y[i+1], color_mapa, dibujar);

	}

	//

	for(int i=0;i<n;i++)

	{

		dx=x[i+1]-x[i];

		dy=y[i+1]-y[i];

		if(dy==0)slope[i]=1.0;

		if(dx==0)slope[i]=0.0;

		if(dx!=0 && dy!=0)

		slope[i]=(float)dx/dy;

	}

	for(int j=0;j<=ymax;j++)

	{

		int k=0;

		for(int i=0;i<n;i++){

			if(((y[i]<=j) && (y[i+1]>j)) || ((y[i]>j) && (y[i+1]<=j))){

				xi[k]=(int)(x[i]+slope[i]*(j-y[i]));

				k++;

			}

		}

		for(int m=0;m<k-1;m++){

			for(int i=0;i<k-1;i++){

				if(xi[i]>xi[i+1]){

					temp=xi[i];

					xi[i]=xi[i+1];

					xi[i+1]=temp;

				}

			}

			//setcolor(2);

			for(int i=0;i<k;i+=2){

				//line(xi[i],j,xi[i+1]+1,j);
        //delay(100);
        bresenham(xi[i],j,xi[i+1]+1,j, color_mapa, dibujar);

			}

		}

	}
  //-------------------------------------------------------------
  
   
  glutPostRedisplay();
}