#include <stdbool.h>
#include <stdlib.h>
#include "errors.h"
#include "arr_loc.h"
#include "arr_op.h"

static bool is_elem_in_array(const int *arr, size_t n, int elem)
{
    for (size_t i = 0; i < n; i++)
    {
        if (arr[i] == elem)
        {
            return true;
        }
    }
    return false;
}

int array_to_set(const int *arr1, size_t n1, int **set, size_t *n_set)
{
    int *temp_array = NULL, *fin_array = NULL;
    size_t size_temp = n1;
    size_t current_length = 0;
    int rc = ERR_OK;

    if (n1 == 0)
    {
        return rc;
    }

    temp_array = arr_loc(size_temp);

    if (!temp_array)
    {
        return ERR_MEMORY;
    }

    for (size_t i = 0; i < n1; i++)
    {
        if (!is_elem_in_array(temp_array, current_length, arr1[i]))
        {
            temp_array[current_length] = arr1[i];
            current_length++;
        }
    }

    fin_array = realloc(temp_array, current_length * sizeof(int));
    if (fin_array)
    {
        *set = fin_array;
        *n_set = current_length;
    }
    else
    {
        rc = ERR_MEMORY;
    }
    return rc;
}

int array_unioin(const int *arr1, size_t n1, const int *arr2, size_t n2, int **arr3, size_t *n3)
{
    int *temp_array = NULL, *fin_array = NULL;
    size_t size_temp = n1 + n2;
    size_t current_length = 0;
    temp_array = arr_loc(size_temp);

    if (!temp_array)
    {
        return ERR_MEMORY;
    }

    for (size_t i = 0; i < n1; i++)
    {
        if (!is_elem_in_array(temp_array, current_length, arr1[i]))
        {
            temp_array[current_length] = arr1[i];
            current_length++;
        }
    }

    for (size_t i = 0; i < n2; i++)
    {
        if (!is_elem_in_array(temp_array, current_length, arr2[i]))
        {
            temp_array[current_length] = arr2[i];
            current_length++;
        }
    }

    if (current_length != 0)
    {
        fin_array = realloc(temp_array, current_length * sizeof(int));
    }
    else
    {
        free(temp_array);
        return ERR_OK;
    }

    if (fin_array)
    {
        *arr3 = fin_array;
        *n3 = current_length;
    }
    else
    {
        return ERR_MEMORY;
    }
    return ERR_OK;
}
