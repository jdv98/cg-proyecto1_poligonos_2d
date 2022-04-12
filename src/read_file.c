#include "include/read_file.h"

char *read_file(char *filename,int * size)
{
    int file;
    double *data=0;
    struct stat buff_stat;
    size_t bytes_read;

    if ((file = open(filename, O_RDONLY)) < 0)
    {
        return NULL;
    }
    else if (fstat(file, &buff_stat) < 0)
    {
        return NULL;
    }
    else if ((data = malloc(buff_stat.st_size+sizeof(char *))) == NULL)
    {
        return NULL;
    }
    else if ((bytes_read = read(file, data, buff_stat.st_size)) < 0)
    {
        return NULL;
    }
    else
    {
        (*size)=buff_stat.st_size;
        char * text= (char *)data;
        text[(*size)]='\0';
        return text;
    }
}