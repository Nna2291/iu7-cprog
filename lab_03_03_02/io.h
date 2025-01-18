#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include "constants.h"
#include "errors.h"
#include <stdio.h>

int matrix_input(int matrix[][M], size_t *n, size_t *m);

void print_matrix(const int matrix[][M], size_t n, size_t m);

#endif
