#ifndef IO_H
#define IO_H
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"

int matrix_input(size_t *n, size_t *m);

void print_matrix(const int matrix[][M], size_t n, size_t m);

#endif
