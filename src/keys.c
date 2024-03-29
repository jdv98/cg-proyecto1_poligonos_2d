#include "include/transformaciones.h"
#include "include/keys.h"
#include <pthread.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

pthread_t thread_id;
pthread_t render_id;
struct timespec ts;

bool thread_running=false,
    left_key=false,
    right_key=false,
    up_key=false,
    down_key=false,
    down_shift=false,
    down_ctrl=false,
    down_alt=false,
    zoom_in=false,
    zoom_out=false,
    rotacion_viewport=false,
    rotacion_cero=false,
    rv_clockwise=true,
    rc_clockwise=true,
    down_escalar_arriba=false,
    down_escalar_abajo=false;

double pan_x=0,
      pan_y=0,
      velocidad_pan=0,
      velocidad_base_pan=2;
void set_velocidad_pan(double v);
void print();
void * teclaPresionada(void *vargp){

  POLIGONO *poligono_iter;
  PROVINCIA *provincia_iter;
  int escalar_int=0,r_l=0,u_d=0;
  
    while(left_key || right_key || up_key || down_key || zoom_in || zoom_out || rotacion_viewport || rotacion_cero || down_escalar_arriba || down_escalar_abajo){

      if(!DIBUJANDO){

        if(down_escalar_arriba){
          escalacion_mapa(10.0/9.0,0,0);
          down_escalar_arriba=false;
        }
        else if(down_escalar_abajo){
          escalacion_mapa(9.0/10.0,0,0);
          down_escalar_abajo=false;
        }

        if(zoom_in){
          if(down_ctrl){//rapido
            zoom_viewport((double)1/10);
          }
          else if(down_alt){//lento
            zoom_viewport((double)9/10);
          }
          else{
            zoom_viewport((double)0.5);
          }
          set_velocidad_pan( (viewport[RT_P].x-viewport[LB_P].x)/1000.0 );
          zoom_in=false;
        }
        else if(zoom_out){
          if(down_ctrl){
            zoom_viewport((double)10);
          }
          else if(down_alt){
            zoom_viewport((double)10/9);
          }
          else{
            zoom_viewport((double)2);
          }
          set_velocidad_pan( (viewport[RT_P].x-viewport[LB_P].x)/1000.0 );
          zoom_out=false;
        }

        if(rotacion_viewport){
          double velocidad;
          if(down_ctrl){//rapido
            velocidad=1;
          }
          else if(down_alt){//lento
            velocidad=0.05;
          }
          else{
            velocidad=0.5;
          }
          if(rv_clockwise)
            velocidad*=-1;
          rotacion_mapa(velocidad,(double)(viewport[LB_P].x+viewport[RT_P].x)/2,(double)(viewport[LB_P].y+viewport[RT_P].y)/2);

          rotacion_viewport=false;
        }
        else if(rotacion_cero){
          double velocidad;
          if(down_ctrl){//rapido
            velocidad=1;
          }
          else if(down_alt){//lento
            velocidad=0.05;
          }
          else{
            velocidad=0.5;
          }
          if(rc_clockwise)
            velocidad*=-1;
          rotacion_mapa(velocidad,0.0,0.0);

          rotacion_cero=false;

        }

        if(down_ctrl){
          velocidad_pan=(velocidad_base_pan/4.0);
        }
        else if(down_shift){
          velocidad_pan=(double)(velocidad_base_pan*4.0);
        }
        else{
          velocidad_pan=velocidad_base_pan;
        }

        if(right_key || left_key || up_key || down_key){

          if(right_key){
            pan_x=velocidad_pan;
          }
          else if(left_key){
            pan_x=-velocidad_pan;
          }
          else{
            pan_x=0;
          }

          if(up_key){
            pan_y=velocidad_pan;
          }
          else if(down_key){
            pan_y=-velocidad_pan;
          }
          else{
            pan_y=0;
          }

          pan_viewport(pan_x,pan_y);
        }
        
        glutPostRedisplay();
      }
      usleep(10*1000);
  }
  thread_running=false;
  glutPostRedisplay();
  velocidad_pan=velocidad_base_pan;
}

void init_thread(){
  if(!thread_running){
    pthread_create(&thread_id,NULL,teclaPresionada,NULL);
    thread_running=true;
  }
}

void set_velocidad_pan(double v){
    velocidad_base_pan=v;
}

void free_mapa(){
  TEXTURA * textura_iter;
  POLIGONO *poligono_iter;
  PROVINCIA *provincia_iter;
  for (size_t i = 0; i < provincias->size; i++)
  {
      provincia_iter = provincias->provincias[i];
      for (size_t j = 0; j < provincia_iter->size; j++)
      {
          poligono_iter = provincia_iter->poligonos[j];
          for (size_t z = 0; z < poligono_iter->size; z++)
          {
            free(poligono_iter->vertices[z]);
          }
          free(poligono_iter->vertices);
          free(poligono_iter);
      }
      free(provincia_iter->color_mapa);
      textura_iter = provincia_iter->textura;

      for (size_t row = 0; row < textura_iter->height; row++)
      {
        free(textura_iter->pixeles[row]);
      }
      free(textura_iter);
      
      
      free(provincia_iter->poligonos);
      free(provincia_iter);
  }
}

void normal_keys(unsigned char key, int x, int y)
{
  switch (key)
  {

  case 8: // Borrar
    if(down_shift){
      reset_viewport();
    }
    else{
      reset_mapa();
    }
    break;
  
  case 27: // Esc
    free_mapa();
    exit(0);
    break;

  case 49: // 1
    DIBUJAR_RELLENO=false;
    DIBUJAR_TEXTURA=false;
    break;

  case 50: // 2
    DIBUJAR_RELLENO=true;
    DIBUJAR_TEXTURA=false;
    break;

  case 51: // 3
    DIBUJAR_RELLENO=false;
    DIBUJAR_TEXTURA=true;
    break;

  case 53: // 5
    print();
    break;

  case 101: // e
    down_escalar_abajo=true;
    break;

  case 69: // e
    down_escalar_arriba=true;
    break;

  case 114: // r
    rotacion_viewport=true;
    rv_clockwise=true;
    break;

  case 18: // r
    rotacion_viewport=true;
    rv_clockwise=true;
    break;

  case 102: // f
    rotacion_viewport=true;
    rv_clockwise=false;
    break;

  case 6: // f
    rotacion_viewport=true;
    rv_clockwise=false;
    break;

  case 116: // t
    rotacion_cero=true;
    rc_clockwise=true;
    break;

  case 20: // t
    rotacion_cero=true;
    rc_clockwise=true;
    break;

  case 103: // g
    rotacion_cero=true;
    rc_clockwise=false;
    break;

  case 7: // g
    rotacion_cero=true;
    rc_clockwise=false;
    break;

  case 43: // +
      zoom_in=true;
    break;

  case 45: // -
      zoom_out=true;
    break;

  default:
    break;
  }

  init_thread();
}

void normal_keys_up(unsigned char key,int x, int y){
  switch (key)
  {

  default:
    break;
  }
}

void special_keys(int key, int x, int y)
{
  switch (key)
  {
    case 100:
      left_key=true;
      break;
    case 101:
      up_key=true;
      break;
    case 102:
      right_key=true;
      break;
    case 103:
      down_key=true;
      break;
    case 112:
      down_shift=true;
      break;
    case 114:
      down_ctrl=true;
      break;
    case 116:
      down_alt=true;
      break;
    default:
      break;
  }
  init_thread();
}

void special_keys_up(int key,int x, int y){
  switch (key)
  {
    case 100:
      left_key=false;
      break;
    case 101:
      up_key=false;
      break;
    case 102:
      right_key=false;
      break;
    case 103:
      down_key=false;
      break;
    case 112:
      down_shift=false;
      break;
    case 114:
      down_ctrl=false;
      break;
    case 116:
      down_alt=false;
      break;
    default:
      break;
    }
}

void print()
{
  POLIGONO *poligono_iter;
  PROVINCIA *provincia_iter;

  for (size_t i = 0; i < provincias->size; i++)
  {
    provincia_iter = provincias->provincias[i];
    for (size_t j = 0; j < provincia_iter->size; j++)
    {
      poligono_iter = provincia_iter->poligonos[j];

      for (size_t k = 0; k < poligono_iter->size; k++)
      {
        system("clear");
        printf("\033[0;32m");
        printf("poligono >> %lf %lf\n", poligono_iter->vertices[k][0], poligono_iter->vertices[k][1]);
        printf("\033[0;36m");
        printf("clipping >> %lf %lf %lf %lf\n",viewport[LB_P].x,viewport[LB_P].y,viewport[RT_P].x,viewport[RT_P].y);
        printf("\033[0;37m");
        return;
      }
    }
  }
}