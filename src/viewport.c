#include "include/viewport.h"
#include "include/matriz.h"

double ** viewport_log_cambios;
Vertices * viewport;

void asignar_valor(Vertices * vert,double x, double y){
    vert->x=x;
    vert->y=y;
}

void asignar_valor_viewport(double left, double bottom, double right, double top)
{
    asignar_valor(&viewport[LB_P],left,bottom);
    asignar_valor(&viewport[LT_P],left,top);
    asignar_valor(&viewport[RT_P],right,top);
    asignar_valor(&viewport[RB_P],right,bottom);
}

/**
 * @brief Vincula los vertices del viewport y quita posibles residuos
 *
 * @return ** void
 */
void reset_vertices(Vertices * medio,Vertices * ant,Vertices * sig){
    
    medio->vecino = NULL;
    medio->no_dibujar = false;
    medio->entrada = -1;
    medio->ant = ant;
    medio->sig = sig;
}

void reset_viewport_list()
{
    reset_vertices(&viewport[LB_P],&viewport[RB_P],&viewport[LT_P]);
    reset_vertices(&viewport[LT_P],&viewport[LB_P],&viewport[RT_P]);
    reset_vertices(&viewport[RT_P],&viewport[LT_P],&viewport[RB_P]);
    reset_vertices(&viewport[RB_P],&viewport[RT_P],&viewport[LB_P]);
}

/**
 * @brief Asigna memoria a los vertices del viewport
 *
 * @param left
 * @param right
 * @param top
 * @param bottom
 * @return ** void
 */
void init_viewport(double left, double bottom, double right, double top)
{
    viewport=malloc(4*sizeof(Vertices));
    asignar_valor_viewport(left, bottom, right, top);

    viewport_log_cambios=matriz_init(3,3,true);
}