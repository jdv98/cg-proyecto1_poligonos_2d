#include "include/clipping.h"

/**
 * @brief Inserta un nuevo vertice al anterior al `A` y vinculo `medio` con su homologo en el viewport
 *
 * @param A
 * @param medio
 * @return ** void
 */
void ins_ant_vert_viewport(Vertices *A, Vertices *medio);

/**
 * @brief Indica si no se debe dibujar la linea y en caso de ser necesario en donde debe ser cortada la linea
 *
 * @param p
 * @param q
 * @param t0
 * @param t1
 * @return true
 * @return false
 */
bool cond_no_dibujar(double p, double q,double * t0, double * t1);

/**
 * @brief Inserta vertices/cortes en el viewport
 *
 * @param medio
 * @return ** void
 */
void insertar_en_viewport(Vertices *medio);

/**
 * @brief Inserta nuevos vertices/cortes en el poligono
 *
 * @param Poly
 * @param x
 * @param y
 * @param entrada
 * @return ** void
 */
void insertar_en_poligono(Vertices *Poly, double x, double y, bool entrada);

/**
 * @brief Crea los nuevos vertices a insertar en el viewport y el poligono
 *
 * @param entradaPoly
 * @return ** Vertices*
 */
Vertices *liang_barsky_weiler_atherton(Vertices *entradaPoly);

void limpiar_memoria_poligono(Vertices *iter);

/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/

void clipping_a_pantalla(double ** xy,double x,double y){
    (*xy)[0]=(resolucion-1)*((x-viewport[LB_P].x)/(viewport[RT_P].x-viewport[LB_P].x));
    (*xy)[1]=(resolucion-1)*((y-viewport[LB_P].y)/(viewport[RT_P].y-viewport[LB_P].y));
}

void clipping_poligono(double **vertices,int size,double *** nuevo_vertice,int * nuevo_vertice_size)
{
    Vertices
        * iterator,
        * primera_entrada,
        * checkPoint,
        * tmp,
        * poligono;
    reset_viewport_list();

    poligono = malloc(sizeof(Vertices));

    iterator = poligono;


    for (size_t i = 0; i < size; i++)
    {
        iterator->x = vertices[i][0];
        iterator->y = vertices[i][1];
        iterator->entrada = -1;
        iterator->no_dibujar = false;
        iterator->vecino = NULL;

        if (i < size-1)
            iterator->sig = malloc(sizeof(Vertices));
        else
            iterator->sig = poligono;
        iterator->sig->ant = iterator;
        iterator = iterator->sig;
    }

    iterator = poligono;
    do
    {
        iterator = liang_barsky_weiler_atherton(iterator);
    } while (iterator!=poligono);
    

    iterator = poligono;
    /**
     * @brief Cambia el primer vertice a uno que sea dibujable en caso de ser necesario.
     *
     */
    if (poligono->no_dibujar)
    {
        do
        {
            iterator = iterator->sig;
            if (iterator == poligono)
            {
                limpiar_memoria_poligono(poligono);
                return;
            }
        } while (iterator->no_dibujar);
        poligono = (struct Vertices *)iterator;
    }

    primera_entrada = poligono;
    /**
     * @brief libera la memoria de los vertices que no van a ser pintados
     *
     */
    do
    {
        if (primera_entrada->no_dibujar && primera_entrada != NULL)
        {
            primera_entrada->ant->sig = primera_entrada->sig;
            primera_entrada->sig->ant = primera_entrada->ant;
            tmp = primera_entrada;
            primera_entrada = primera_entrada->sig;
            free(tmp);
            tmp = NULL;
        }
        else
            primera_entrada = primera_entrada->sig;
    } while (primera_entrada != poligono && primera_entrada != NULL && poligono != NULL);

    checkPoint = primera_entrada;

    bool frame = false;
    bool brake=false;
    do
    {
        /***/
        (*nuevo_vertice_size)++;
        (*nuevo_vertice)=realloc((*nuevo_vertice),(*nuevo_vertice_size)*sizeof(double*));
        (*nuevo_vertice)[(*nuevo_vertice_size)-1]=malloc(2*sizeof(double));
        clipping_a_pantalla(&(*nuevo_vertice)[(*nuevo_vertice_size)-1],primera_entrada->x,primera_entrada->y);
        /**/

        //bresenham((int)primera_entrada->x, (int)primera_entrada->y, (int)primera_entrada->sig->x, (int)primera_entrada->sig->y, color_mapa);
        primera_entrada->no_dibujar = true;
        do
        {
            primera_entrada = primera_entrada->sig;
            if (poligono == primera_entrada)
                brake=true;
        } while (primera_entrada->no_dibujar && !brake);

        if (primera_entrada->entrada == 0 && !frame)
        {
            if (primera_entrada->vecino == NULL)
                break;
            primera_entrada = primera_entrada->vecino;
            frame = !frame;
        }
        else if (primera_entrada->entrada == 1 && frame)
        {
            if (primera_entrada->vecino == NULL)
                break;
            primera_entrada = primera_entrada->vecino;
            frame = !frame;
        }
    } while (poligono != primera_entrada && !brake);

    (*nuevo_vertice_size)++;
    (*nuevo_vertice)=realloc((*nuevo_vertice),(*nuevo_vertice_size)*sizeof(double*));
    (*nuevo_vertice)[(*nuevo_vertice_size)-1]=malloc(2*sizeof(double));
    clipping_a_pantalla(&(*nuevo_vertice)[(*nuevo_vertice_size)-1],primera_entrada->x,primera_entrada->y);
    limpiar_memoria_poligono(poligono);
}

Vertices *liang_barsky_weiler_atherton(Vertices *entradaPoly)
{
    Vertices *ultimo = entradaPoly->sig;
    double t0 = 0.0;
    double t1 = 1.0;
    double xdelta = ultimo->x - entradaPoly->x;
    double ydelta = ultimo->y - entradaPoly->y;
    if (cond_no_dibujar(-xdelta, -(viewport[LB_P].x - entradaPoly->x), &t0, &t1)      // izquierda
        || cond_no_dibujar(xdelta, (viewport[RT_P].x - entradaPoly->x), &t0, &t1)    // derecha
        || cond_no_dibujar(-ydelta, -(viewport[LB_P].y - entradaPoly->y), &t0, &t1) // abajo
        || cond_no_dibujar(ydelta, (viewport[RT_P].y - entradaPoly->y), &t0, &t1)      // arriba
        || t0 >= 1.0 || t1 <= 0.0)                                             //
    {
        entradaPoly->no_dibujar = true;
        return ultimo;
    }
    if (t0 < 1 && t0 > 0)
    {
        insertar_en_poligono(ultimo, entradaPoly->x + t0 * xdelta, entradaPoly->y + t0 * ydelta, true);
        insertar_en_viewport(ultimo->ant);
        entradaPoly->no_dibujar = true;
    }
    else if (t0 < 1)
    { // No crea ningun corte e inserta el primer vertice de la linea en el viewport
        entradaPoly->entrada = true;
        insertar_en_viewport(entradaPoly);
    }
    if (t1 < 1 && t1 > 0)
    {
        insertar_en_poligono(ultimo, entradaPoly->x + t1 * xdelta, entradaPoly->y + t1 * ydelta, false);
        insertar_en_viewport(ultimo->ant);
    }
    else if (t1 > 0)
    { // No crea ningun corte e inserta el ultimo vertice de la linea en el viewport
        ultimo->entrada = true;
        insertar_en_viewport(ultimo);
    }

    return ultimo;
}

void insertar_en_poligono(Vertices *Poly, double x, double y, bool entrada)
{
    Poly->ant->sig = malloc(sizeof(Vertices));
    Poly->ant->sig->ant = Poly->ant;
    Poly->ant->sig->sig = Poly;
    Poly->ant = Poly->ant->sig;

    Poly->ant->x = x;
    Poly->ant->y = y;
    Poly->ant->entrada = entrada;
    Poly->ant->no_dibujar = false;
}

void ins_ant_vert_viewport(Vertices *A, Vertices *medio)
{
    Vertices *A_ant = A->ant;
    A->ant = malloc(sizeof(Vertices));
    A->ant->x = medio->x;
    A->ant->y = medio->y;
    A->ant->entrada = medio->entrada;
    A->ant->no_dibujar = medio->no_dibujar;

    medio->vecino = A->ant;
    A->ant->vecino = medio;

    A->ant->sig = A;
    A->ant->ant = A_ant;

    A_ant->sig = A->ant;
}

void insertar_en_viewport(Vertices *medio)
{
    Vertices *tmp = &viewport[LB_P];
    // LEFT
    if (fabs(medio->x - tmp->x) < 0.00001)
    {
        do
        {
            if (medio->y < tmp->sig->y)
            {
                ins_ant_vert_viewport(tmp->sig, medio);
                return;
            }
            tmp = tmp->sig;
        } while (tmp != viewport[LT_P].sig);
    }
    else if (fabs(medio->y - tmp->y) < 0.00001) // BOTTOM
    {
        do
        {
            if (medio->x < tmp->x)
            {
                ins_ant_vert_viewport(tmp->sig, medio);
                return;
            }
            tmp = tmp->ant;
        } while (tmp != viewport[RB_P].ant);
    }

    tmp = &viewport[RT_P];

    if (fabs(medio->x - tmp->x) < 0.00001) // RIGHT
    {
        do
        {
            if (medio->y > tmp->sig->y)
            {
                ins_ant_vert_viewport(tmp->sig, medio);
                return;
            }
            tmp = tmp->sig;
        } while (tmp != viewport[RB_P].sig);
    }

    tmp = &viewport[LT_P];
    if (fabs(medio->y - tmp->y) < 0.00001) // TOP
    {
        do
        {
            if (medio->x < tmp->sig->x)
            {
                ins_ant_vert_viewport(tmp->sig, medio);
                return;
            }
            tmp = tmp->sig;
        } while (tmp != viewport[RT_P].sig);
    }
}

bool cond_no_dibujar(double p, double q,double * t0, double *t1)
{
    double r = q / p;
    if (p == 0 && q < 0)
        return true;

    if (p < 0)
    {
        if (r > (*t1))
            return true;
        else if (r > (*t0))
            (*t0) = r;
    }
    else if (p > 0)
    {
        if (r < (*t0))
            return true;
        else if (r < (*t1))
            (*t1) = r;
    }
    return false;
}

void limpiar_memoria_poligono(Vertices *iter)
{
    Vertices *tmp, *tmp_vecino;
    Vertices *head = iter;

    do
    {
        tmp = iter;
        if (iter->vecino != NULL)
        {
            free(iter->vecino);
            iter->vecino = NULL;
        }
        iter = iter->sig;
        free(tmp);
        tmp = NULL;
    } while (iter != head);
}
