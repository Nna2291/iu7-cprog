#include <math.h>
#include "constants.h"
#include "compare.h"

int compare_int_arrays(const int *arr1, const int *arr2, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        if (arr1[i] != arr2[i])
        {
            return ARRAY_NOT_EQUAL;
        }
    }
    return ARRAY_EQUAL;
}

int compare_double_arrays(const double *arr1, const double *arr2, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        if (fabs(arr1[i] - arr2[i]) > EPSILON)
        {
            return ARRAY_NOT_EQUAL;
        }
    }
    return ARRAY_EQUAL;
}

int compare_char_array(const char *arr1, const char *arr2, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        if (arr1[i] != arr2[i])
        {
            return ARRAY_NOT_EQUAL;
        }
    }
    return ARRAY_EQUAL;
}
