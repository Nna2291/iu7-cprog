#ifndef ARR_OP_H__
#define ARR_OP_H__

#include <stddef.h>

int array_unioin(const int *arr1, size_t n1, const int *arr2, size_t n2, int **arr3, size_t *n3);

int array_to_set(const int *arr1, size_t n1, int **array2, size_t *n2);

#endif
