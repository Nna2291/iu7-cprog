#ifndef ARR_IO_H__
#define ARR_IO_H__

#include <stdio.h>

int create_array(FILE *f, int **pbeg, int **pend);


int write_array(const char *fname, const int *array_b, const int *array_end);

#endif

