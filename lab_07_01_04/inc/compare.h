#ifndef COMPARE_H__
#define COMPARE_H__
#include <stddef.h>

int compare_int_arrays(const int *arr1, const int *arr2, size_t n);

int compare_double_arrays(const double *arr1, const double *arr2, size_t n);

int compare_char_array(const char *arr1, const char *arr2, size_t n);

#endif
