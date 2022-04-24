#ifndef TRANSFORMACIONES_H
#define TRANSFORMACIONES_H

void rotacion_mapa(double angulo,double x, double y);
void escalacion_mapa(double escalar, double x, double y);
void traslacion_mapa(double x, double y);
void rotar_triangulos(double grados, double x, double y);
void pan_viewport(double x, double y);
void zoom_viewport(double zoom);
void reset_viewport();
void print_viewport_log();

#endif