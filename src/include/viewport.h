#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <stdlib.h>
#include <stdbool.h>

/***************************/
#include "vertices.h"
/***************************/

/**
 * @brief L->left   R->Right    B->Bottom   T->Top 
 * 
 */
#define LB_P 0
#define LT_P 1
#define RT_P 2
#define RB_P 3

extern Vertices * viewport;

void init_viewport(double left, double bottom, double right, double top);
void reset_viewport();

#endif