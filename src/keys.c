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
    shitf=false,
    left_key=false,
    right_key=false,
    up_key=false,
    down_key=false,
    subir_escala_bool=false,
    bajar_escala_bool=false,
    entrar=false;

double escalar = 1.5;
int num = 2;

void print();
void aum_velocidad();
void dis_velocidad();

void * teclaPresionada(void *vargp){

    POLIGONO *poligono_iter;
    PROVINCIA *provincia_iter;
    int escalar_int=0,r_l=0,u_d=0;
    int x=0,y=0;
  
  while(left_key || right_key || up_key || down_key || bajar_escala_bool || subir_escala_bool){
    usleep(15*1000);

    if(subir_escala_bool) escalar_int=1;
    else if(bajar_escala_bool) escalar_int=2;
    else escalar_int=0;

    if(right_key){
      x=5;
    }
    else if(left_key){
      x=-5;
    }
    else{
      x=0;
    }

    if(up_key){
      y=5;
    }
    else if(down_key){
      y=-5;
    }
    else{
      y=0;
    }
    pan_viewport(x,y);
    glutPostRedisplay();
  }
  thread_running=false;
}

void init_thread(){
  if(!thread_running){
    pthread_create(&thread_id,NULL,teclaPresionada,NULL);
    thread_running=true;
  }
}

void normal_keys(unsigned char key, int x, int y)
{
  printf("%i\n",key);
  switch (key)
  {
  case 27: // Esc
    exit(0);
    break;
  
  case 49: // 1
    entrar=true;
    init_thread();
    //rotacion();
    //escalacion();
    //traslacion();
    break;
  
  case 50: // 2
    bajar_escala_bool=true;
    init_thread();
    break;

  case 51: // 3
    subir_escala_bool=true;
    init_thread();
    break;

  case 52: // 4
    aum_velocidad();
    break;

  case 53: // 5
    print();
    break;

  case 54: // 6
    traslacion();
    break;
  
  case 97: // a
    receteando ();
    break;

  case 101: // e
    escalacion(0.9);
    break;

  case 69: // e
    escalacion(1.5);
    break;

  case 114: // r
    rotacion();
    break;

  case 122: // z
    zoom_viewport(0.5);
    break;

  case 90: // z
    zoom_viewport(2);
    break;

  default:
    break;
  }
}

void normal_keys_up(unsigned char key,int x, int y){
  switch (key)
  {

  case 50: // 2
    bajar_escala_bool=false;
    break;

  case 51: // 3
    subir_escala_bool=false;
    break;

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

void aum_velocidad()
{
  system("clear");
  num += num;
  printf("num>> %i\n", num);
}

void dis_velocidad()
{
  if (num > 2)
    num -= (int)num / 2;
  system("clear");
  printf("num>> %i\n", num);
}