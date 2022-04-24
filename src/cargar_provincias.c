#include "include/cargar_provincias.h"

double lineas[][3]={
    {239, 83, 80},
    {171, 71, 188},
    {66, 165, 245},
    {38, 198, 218},
    {102, 187, 106},
    {255, 238, 88},
    {255, 167, 38}
};

double rellenado[][3]={
    {255, 235, 238},
    {243, 229, 245},
    {227, 242, 253},
    {224, 247, 250},
    {232, 245, 233},
    {255, 253, 231},
    {236, 239, 241}
};

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

void cargar_color(PROVINCIA ** provincia){
    (*provincia)->color_mapa=malloc(sizeof(COLOR));
    (*provincia)->color_mapa->r=lineas[(*provincia)->numero-1][0]/255;
    (*provincia)->color_mapa->g=lineas[(*provincia)->numero-1][1]/255;
    (*provincia)->color_mapa->b=lineas[(*provincia)->numero-1][2]/255;

    //////

    (*provincia)->relleno_mapa=malloc(sizeof(COLOR));
    (*provincia)->relleno_mapa->r=rellenado[(*provincia)->numero-1][0]/255;
    (*provincia)->relleno_mapa->g=rellenado[(*provincia)->numero-1][1]/255;
    (*provincia)->relleno_mapa->b=rellenado[(*provincia)->numero-1][2]/255;

    //////

    char * nombre=malloc(sizeof(char)*(25));
    sprintf(nombre, "texturas/%i.avs", (*provincia)->numero);

    (*provincia)->textura=malloc(sizeof(TEXTURA));
    cargar_textura(nombre,&(*provincia)->textura->pixeles,&(*provincia)->textura->height,&(*provincia)->textura->width);

    free(nombre);
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
        cargar_color(provincia);
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
    provincias->log_cambios_matriz=matriz_init(3,3,true);
    
    //LECTURA
    while(seguir_iter()){      
        leer_provincia();
    }

    free(original);
}