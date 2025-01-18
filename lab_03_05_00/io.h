#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "constants.h"

int matrix_input(int matrix[][M], size_t *n, size_t *m);

void print_matrix(const int matrix[][M], size_t n, size_t m);

#endif
