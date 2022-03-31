#include "include/cargar_provincias.h"

PROVINCIAS *provincias;

void crear_provincia(PROVINCIA ** provincia,json_object *nombre,json_object *length_geometries);
void crear_poligono(POLIGONO ** poligono,json_object *length_vertices);
void agregar_vertices(double ** vertice,json_object *json_vertice);

void cargarProvincias(const char *filename)
{
    POLIGONO *poligono;
    PROVINCIA *provincia;
    struct json_object  *obj,
                        *geometries,
                        *polygon,
                        *nombre,
                        *features;


    obj = json_object_from_file(filename);
    features = json_object_object_get(obj, "features");

    provincias = malloc(json_object_array_length(features) * sizeof(PROVINCIAS));
    provincias->size = json_object_array_length(features);
    provincias->provincias = (PROVINCIA **)malloc(provincias->size * sizeof(PROVINCIA*));

    for (size_t i = 0; i < provincias->size; i++)
    {
        obj = json_object_array_get_idx(features, i);
        nombre = json_object_object_get(obj, "properties");
        nombre = json_object_object_get(nombre, "provincia");
        obj = json_object_object_get(obj, "geometry");
        geometries = json_object_object_get(obj, "coordinates");

        crear_provincia(&provincia,nombre,geometries);
        for (size_t j = 0; j < provincia->size; j++)
        {
            polygon = json_object_array_get_idx(geometries, j);
            crear_poligono(&poligono,polygon);

            for (size_t k = 0; k < poligono->size; k++)
            {
                obj = json_object_array_get_idx(polygon, k);
                agregar_vertices(&poligono->vertices[k],obj);
            }
            provincia->poligonos[j] = poligono;
        }
        
        provincias->provincias[i] = provincia;
    }
}

void crear_provincia(PROVINCIA ** provincia,json_object *nombre,json_object *length_geometries){
    (*provincia) = malloc(sizeof(PROVINCIA));
    (*provincia)->nombre = (char *)json_object_get_string(nombre);
    (*provincia)->size = json_object_array_length(length_geometries);
    (*provincia)->poligonos = (POLIGONO **)malloc((*provincia)->size * sizeof(POLIGONO*));
}

void crear_poligono(POLIGONO ** poligono,json_object *length_vertices){
    (*poligono) = malloc(sizeof(POLIGONO));
    (*poligono)->size = json_object_array_length(length_vertices);
    (*poligono)->vertices = (double **)malloc((*poligono)->size * sizeof(double *));
}

void agregar_vertices(double ** vertice,json_object *json_vertice){
    (*vertice) = (double *)malloc(2 * sizeof(double));
    (*vertice)[0] = json_object_get_double(json_object_array_get_idx(json_vertice, 0));
    (*vertice)[1] = json_object_get_double(json_object_array_get_idx(json_vertice, 1));
}