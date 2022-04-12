#ifndef CHAR_ITERATOR_H
#define CHAR_ITERATOR_H

#include <stdbool.h>

void asignar_iter(char * origen,int size);
bool seguir_iter();
void inc_iter();
char get_char_iter();
bool cmp_iter_char(char c);

#endif