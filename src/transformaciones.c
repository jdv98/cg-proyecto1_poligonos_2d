#include "include/transformaciones.h"
#include "include/provincias.h"
#include "include/matriz.h"
#include "include/viewport.h"

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

double ** matriz_esca_anclado (double escalar, double x, double y) {
    double **m_trasladar = trasladar_matriz(x, y);
    double **m_escalar = escalar_matriz (escalar, escalar);
    double **m_trasladar_inv = trasladar_matriz(-x, -y);

    matriz_mul_r(&m_trasladar, 3, 3, &m_escalar, 3, 3);
    matriz_mul_r(&m_trasladar, 3, 3, &m_trasladar_inv, 3, 3);

    free_matriz(&m_escalar,3);
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

void rotacion_mapa(double angulo,double x, double y){
    double ** matriz_rotada=rotar_sobre_eje(angulo, x, y);
    double ** nuevo_log = matriz_mul(&matriz_rotada,3,3,&provincias->log_cambios_matriz,3,3);
    multiplicar_provincias(matriz_rotada);

    free_matriz(&provincias->log_cambios_matriz,3);
    provincias->log_cambios_matriz=nuevo_log;
}

void escalacion_mapa(double escalar, double x, double y){
    double ** matriz_escala = matriz_esca_anclado(escalar, x, y);
    double ** nuevo_log = matriz_mul(&matriz_escala,3,3,&provincias->log_cambios_matriz,3,3);
    multiplicar_provincias(matriz_escala);

    free_matriz(&provincias->log_cambios_matriz,3);
    provincias->log_cambios_matriz=nuevo_log;
}

void traslacion_mapa(double x, double y){
    double ** matriz_traslado = trasladar_matriz(x, y);
    double ** nuevo_log = matriz_mul(&matriz_traslado,3,3,&provincias->log_cambios_matriz,3,3);
    multiplicar_provincias(matriz_traslado);

    free_matriz(&provincias->log_cambios_matriz,3);
    provincias->log_cambios_matriz=nuevo_log;
}

void reset_mapa(){
    double *** matriz_recet = &provincias->log_cambios_matriz;
    double ** matriz_inversa=inversa_3x3((*matriz_recet));

    matriz_mul_r(matriz_recet,3,3,&matriz_inversa,3,3);
    multiplicar_provincias(matriz_inversa);
}


/***
 *  VIEWPORT 
 ***/

void pan_viewport(double x, double y){
    double ** trasladar=trasladar_matriz(x, y);
    double ** nuevo=matriz_init(3,2,false);

    nuevo[0][0]=viewport[LB_P].x;
    nuevo[1][0]=viewport[LB_P].y;
    nuevo[2][0]=1;

    nuevo[0][1]=viewport[RT_P].x;
    nuevo[1][1]=viewport[RT_P].y;
    nuevo[2][1]=1;

    double ** nuevo_viewport=matriz_mul(&trasladar,3,3,&viewport_log_cambios,3,3);
    double ** resultado=matriz_mul(&trasladar,3,3,&nuevo,3,2);

    asignar_valor_viewport(resultado[0][0], resultado[1][0], resultado[0][1], resultado[1][1]);

    free_matriz(&viewport_log_cambios,3);
    viewport_log_cambios=nuevo_viewport;
    free_matriz(&resultado,3);
    free_matriz(&trasladar,3);
    free_matriz(&nuevo,3);
}

void zoom_viewport(double zoom){
    double xc=(viewport[LB_P].x+viewport[RT_P].x)/2;
    double yc=(viewport[LB_P].y+viewport[RT_P].y)/2;

    /****/
    double ** nuevo=matriz_init(3,2,false);

    nuevo[0][0]=viewport[LB_P].x;
    nuevo[1][0]=viewport[LB_P].y;
    nuevo[2][0]=1;

    nuevo[0][1]=viewport[RT_P].x;
    nuevo[1][1]=viewport[RT_P].y;
    nuevo[2][1]=1;
    /****/

    double ** trasladar=trasladar_matriz(xc-(xc*zoom), yc-(yc*zoom));
    double ** escalar=escalar_matriz(zoom,zoom);
    matriz_mul_r(&trasladar,3,3,&escalar,3,3);
    

    double ** nuevo_viewport=matriz_mul(&trasladar,3,3,&viewport_log_cambios,3,3);
    double ** resultado=matriz_mul(&trasladar,3,3,&nuevo,3,2);

    asignar_valor_viewport(resultado[0][0], resultado[1][0], resultado[0][1], resultado[1][1]);

    free_matriz(&viewport_log_cambios,3);
    viewport_log_cambios=nuevo_viewport;

    free_matriz(&resultado,3);
    free_matriz(&trasladar,3);
    free_matriz(&escalar,3);
    free_matriz(&nuevo,3);

}

void reset_viewport(){
    /****/
    double ** nuevo=matriz_init(3,2,false);

    nuevo[0][0]=viewport[LB_P].x;
    nuevo[1][0]=viewport[LB_P].y;
    nuevo[2][0]=1;

    nuevo[0][1]=viewport[RT_P].x;
    nuevo[1][1]=viewport[RT_P].y;
    nuevo[2][1]=1;
    /****/

    double ** matriz_inversa=inversa_3x3(viewport_log_cambios);
    matriz_mul_r(&viewport_log_cambios,3,3,&matriz_inversa,3,3);

    double ** resultado=matriz_mul(&matriz_inversa,3,3,&nuevo,3,2);
    asignar_valor_viewport(resultado[0][0], resultado[1][0], resultado[0][1], resultado[1][1]);
    
    free_matriz(&matriz_inversa,3);
    free_matriz(&resultado,3);
    free_matriz(&nuevo,3);
}