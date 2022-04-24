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
    down_ctrl=false;

double pan_x=0,
      pan_y=0,
      velocidad_pan;

void print();
void * teclaPresionada(void *vargp){

    POLIGONO *poligono_iter;
    PROVINCIA *provincia_iter;
    int escalar_int=0,r_l=0,u_d=0;
  
    while(left_key || right_key || up_key || down_key){
      usleep(15*1000);

      if(down_ctrl){
        velocidad_pan=0.01;
      }
      else if(down_shift){
        velocidad_pan=10;
      }
      else{
        velocidad_pan=5;
      }

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
      glutPostRedisplay();
  }
  thread_running=false;
  glutPostRedisplay();
}

void init_thread(){
  if(!thread_running){
    pthread_create(&thread_id,NULL,teclaPresionada,NULL);
    thread_running=true;
  }
}

void normal_keys(unsigned char key, int x, int y)
{
  printf("n> %i\n",key);
  switch (key)
  {

  case 8: // Borrar
    if(down_shift)
      reset_viewport();
    else
      reset_mapa();
    break;
  
  case 27: // Esc
    exit(0);
    break;

  case 53: // 5
    print();
    break;
  
  case 97: // a
    reset_mapa ();
    break;
  
  case 65: // a
    reset_viewport ();
    break;

  case 101: // e
    escalacion_mapa(0.9,0,0);
    break;

  case 69: // e
    escalacion_mapa(1.5,0,0);
    break;

  case 114: // r
    rotacion_mapa(-1,(double)(viewport[LB_P].x+viewport[RT_P].x)/2,(double)(viewport[LB_P].y+viewport[RT_P].y)/2);
    break;

  case 82: // R
    rotacion_mapa(1,(double)(viewport[LB_P].x+viewport[RT_P].x)/2,(double)(viewport[LB_P].y+viewport[RT_P].y)/2);
    break;

  case 116: // t
    rotacion_mapa(-1,0,0);
    break;

  case 84: // T
    rotacion_mapa(1,0,0);
    break;

  case 122: // z
    zoom_viewport((double)9/10);
    break;

  case 90: // z
    zoom_viewport((double)10/9);
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

  printf("s> %i\n",key);
  switch (key)
  {
    case 100:
      left_key=true;
      init_thread();
      break;
    case 101:
      up_key=true;
      init_thread();
      break;
    case 102:
      right_key=true;
      init_thread();
      break;
    case 103:
      down_key=true;
      init_thread();
      break;
    case 112:
      down_shift=true;
      break;
    case 114:
      down_ctrl=true;
      break;
    default:
      break;
  }
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
        printf("poligono >> %lf %lf\n", poligono_iter->vertices[k][0], poligono_iter->vertices[k][1]);
        
        printf("clipping >> %lf %lf %lf %lf\n",viewport[LB_P].x,viewport[LB_P].y,viewport[RT_P].x,viewport[RT_P].y);
        
        return;
      }
    }
  }
}