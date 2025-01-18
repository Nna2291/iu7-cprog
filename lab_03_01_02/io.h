#ifndef IO_H
#define IO_H
#include <stddef.h>
#include "constants.h"
#include "errors.h"

int matrix_input(int matrix[][M], size_t *n, size_t *m);

void print_array(const int array[], size_t n);

#endif
