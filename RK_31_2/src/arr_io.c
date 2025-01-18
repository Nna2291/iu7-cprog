#include "arr_io.h"
#include "arr_loc.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

int input_array(int **array, size_t *n)
{
    size_t temp_n;
    int *temp_arr = NULL;

    if (scanf("%zu", &temp_n) != 1)
    {
        return ERR_IO;
    }

    if (n == 0)
    {
        return ERR_OK;
    }

    temp_arr = arr_loc(temp_n);

    if (!temp_arr)
    {
        return ERR_MEMORY;
    }

    for (size_t i = 0; i < temp_n; i++)
    {
        if (scanf("%d", &temp_arr[i]) != 1)
        {
            free(temp_arr);
            return ERR_IO;
        }
    }

    *array = temp_arr;
    *n = temp_n;
    
    return ERR_OK;
}

void print_array(const int *array, size_t n)
{
    if (n == 0)
    {
        printf("\n");
        return;
    }
    for (size_t i = 0; i < n - 1; i++)
    {
        printf("%d ", array[i]);
    }
    printf("%d\n", array[n - 1]);
}
