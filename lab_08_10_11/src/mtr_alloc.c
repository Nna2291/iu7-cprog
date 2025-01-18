#include "mtr_alloc.h"
#include <stdlib.h>


// double **matrix_alloc(size_t n, size_t m)
// {
//     double **ptrs, *data;

//     ptrs = malloc(n * sizeof(double*));
//     if (!ptrs)
//     {
//         return NULL;
//     }

//     data = malloc(n * m * sizeof(double));
//     if (!data)
//     {
//         free(ptrs);
//         return NULL;
//     }

//     for (size_t i = 0; i < n; i++)
//     {
//         ptrs[i] = data + i * m;
//     }

//     return ptrs;
// }

double **matrix_alloc(size_t n, size_t m)
{
    double **data = calloc(n, sizeof(double*));

    if (!data)
    {
        return NULL;
    }

    for (size_t i = 0; i < n; i++)
    {
        data[i] = malloc(m * sizeof(double));

        if (!data[i])
        {
            matrix_free(data, n);
            return NULL;
        }
    }

    return data;
}

void matrix_free(double **mtr, size_t n)
{
    if (!mtr)
    {
        return;
    }
    for (size_t i = 0; i < n; i++)
    {
        free(mtr[i]);
    }
    free(mtr);
}

// void matrix_free(double **mtr, size_t n)
// {
//     (void) n;

//     /*
//         Такая проверка сделана, что бы при подаче mtr = NULL valgrind не ругался

//         ==93621== Invalid read of size 8
//         ==93621==    at 0x109585: matrix_free (mtr_alloc.c:39)
//         ==93621==    by 0x10949D: main (main.c:55)
//         ==93621==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
//     */
//     if (mtr)
//     {
//         free(mtr[0]);

//         free(mtr);
//     }
// }
