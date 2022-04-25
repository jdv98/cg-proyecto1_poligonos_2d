#include "include/textura.h"

void iniciar_matriz(int h,int w, COLOR *** matriz_textura);
void lecturaAVS(COLOR *** matriz_textura,MagickWand *magick_wand, int height);

void iniciar_matriz(int h,int w, COLOR *** matriz_textura)
{
    (*matriz_textura) = (COLOR **)calloc(h, sizeof(COLOR *));
    for (int i = 0; i < h; i++)
    {
        (*matriz_textura)[i] = (COLOR *)calloc(w, sizeof(COLOR));
    }
}

void cargar_textura(char * archivo, COLOR *** matriz_textura,int * height, int * width) //archivo.avs
{   
    MagickWand *magick_wand;

    // Inicializaciones
    MagickWandGenesis();
    magick_wand = NewMagickWand();

    // Lee la imagen
    MagickBooleanType status = MagickReadImage(magick_wand, archivo);
    if (status == MagickFalse)
        ThrowWandException(magick_wand);
    MagickResetIterator(magick_wand);
    MagickNextImage(magick_wand);

    // Define la altura y anchura de la matriz
    (* height)=MagickGetImageHeight(magick_wand);
    (* width)=MagickGetImageWidth(magick_wand);
    iniciar_matriz((* height), (* width) , matriz_textura);

    // 
    lecturaAVS(matriz_textura,magick_wand,(* height));

    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
}

void lecturaAVS(COLOR *** matriz_textura,MagickWand *magick_wand,int height)
{
    PixelIterator *pixel_iterator;

    size_t number_wands=0;
    PixelWand **pixel_wand_row = NULL;
    pixel_iterator = NewPixelIterator(magick_wand);
    
    PixelResetIterator(pixel_iterator);
    pixel_wand_row = PixelGetCurrentIteratorRow(pixel_iterator, &number_wands);
    int row = height-1;

    do
    {
        for (size_t i = 0; i < number_wands; i++)
        {
            (*matriz_textura)[row][i].r=(double)PixelGetRed(pixel_wand_row[i]);
            (*matriz_textura)[row][i].g=(double)PixelGetGreen(pixel_wand_row[i]);
            (*matriz_textura)[row][i].b=(double)PixelGetBlue(pixel_wand_row[i]);
        }
        pixel_wand_row = PixelGetNextIteratorRow(pixel_iterator, &number_wands);
        row--;
    } while (number_wands > 0);
    DestroyPixelIterator(pixel_iterator);
}