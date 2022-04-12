#include "include/char_iterator.h"

char * iter;
char * iter_end;

void asignar_iter(char * origen,int size){
    iter=&origen[0];
    iter_end=&origen[size];
}

bool seguir_iter(){
    return iter!=iter_end;
}

void inc_iter(){
    if(seguir_iter())
        iter++;
}

char get_char_iter(){
    return (*iter);
}

bool cmp_iter_char(char c){
    return (*iter)==c;
}