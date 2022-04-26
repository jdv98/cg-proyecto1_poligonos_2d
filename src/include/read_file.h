#ifndef READ_FILE_H
#define READ_FILE_H


#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

char *read_file(const char *filename,int * size);
#endif