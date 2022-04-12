#include "include/cargar_provincias.h"

PROVINCIAS *provincias;

double ** realloc_vertices(POLIGONO ** poligono){
    (*poligono)->size++;
    (*poligono)->vertices=realloc((*poligono)->vertices,(*poligono)->size*sizeof(double*));
    (*poligono)->vertices[(*poligono)->size-1]=malloc(2*sizeof(double));
    return &(*poligono)->vertices[(*poligono)->size-1];
}

POLIGONO ** realloc_poligonos(PROVINCIA ** provincia){
    (*provincia)->size++;
    (*provincia)->poligonos=realloc((*provincia)->poligonos,(*provincia)->size*sizeof(POLIGONO*));
    (*provincia)->poligonos[(*provincia)->size-1]=malloc(sizeof(POLIGONO));
    return &(*provincia)->poligonos[(*provincia)->size-1];
}

PROVINCIA ** realloc_provincias(){
    provincias->size++;
    provincias->provincias=realloc(provincias->provincias,provincias->size * sizeof(PROVINCIA*));
    provincias->provincias[provincias->size-1]=malloc(sizeof(PROVINCIA));
    return &provincias->provincias[provincias->size-1];
}

double leer_numero(){
    bool init=true;
    double num=0;

    while(get_char_iter()>47 && get_char_iter()<58){
        if(init){
            num+=get_char_iter()-48;
            init=false;
        }
        else{
            num*=10;
            num+=get_char_iter()-48;
        }
        inc_iter();
    }
    if(cmp_iter_char('.')){
        inc_iter();
        int decimales=10;
        
        while(get_char_iter()>47 && get_char_iter()<58){
            num+=(double)(get_char_iter()-48)/decimales;
            decimales*=10;
            inc_iter();
        }
    }
    return num;
}

void leer_punto(double ** vertice){
    
    if(cmp_iter_char('['))
        inc_iter();

    (*vertice)[0]=leer_numero();// x

    if(cmp_iter_char(','))
        inc_iter();

    (*vertice)[1]=leer_numero();// y

    if(cmp_iter_char(']'))
        inc_iter();
}

void leer_poligonos_triangulares(POLIGONO ** poligono){
    (*poligono)->size=0;
    (*poligono)->vertices=(double**)malloc((*poligono)->size*sizeof(double*));
    
    inc_iter();
    do
    {
        leer_punto(realloc_vertices(poligono));
        if(cmp_iter_char(','))
            inc_iter();
    } while (!cmp_iter_char(']'));
    inc_iter();//    ]
}

void leer_provincia(){
    if(cmp_iter_char('{')){

        
        PROVINCIA ** provincia=realloc_provincias();
        
        inc_iter();

        (*provincia)->numero=(int)leer_numero();
        (*provincia)->size=0;
        (*provincia)->poligonos=malloc(0);
        
        inc_iter();

        if(cmp_iter_char('[')){//geometria
            inc_iter();
            do
            {
                leer_poligonos_triangulares(realloc_poligonos(provincia));
                if(cmp_iter_char(',')){
                    inc_iter();
                }
            } while (!cmp_iter_char(']'));
            inc_iter();//    ]
        }
    }
    //if(cmp_iter_char('}'))
    inc_iter();
}

void cargarProvincias(const char *filename){
    int size=0;
    char* original=read_file(filename,&size);
    asignar_iter(original,size);

    //INIT
    provincias=malloc(sizeof(PROVINCIAS));
    provincias->size=0;
    provincias->provincias=malloc(0);
    
    //LECTURA
    while(seguir_iter()){      
        leer_provincia();
    }

    free(original);
}