#include "mtr_op.h"
#include "mtr_alloc.h"
#include "errors.h"
#include <stdbool.h>

int sum_matrix(const double **mtr1, size_t rows1, size_t columns1, const double **mtr2, size_t rows2, size_t columns2, double ***mtr3, size_t *rows3, size_t *columns3)
{
    if (rows1 != rows2 || columns1 != columns2)
    {
        return ERR_MTR_SIZE;
    }

    if (!mtr1 || !mtr2)
    {
        return ERR_EMPTY;
    }

    double **tmp = matrix_alloc(rows1, columns1);

    if (!tmp)
    {
        return ERR_MEMORY;
    }

    for (size_t i = 0; i < rows1; i++)
    {
        for (size_t j = 0; j < columns1; j++)
        {
            tmp[i][j] = mtr1[i][j] + mtr2[i][j];
        }
    }

    *mtr3 = tmp;
    *rows3 = rows1;
    *columns3 = columns1;
    
    return ERR_OK;
}

int multiply_matrix(const double **mtr1, size_t rows1, size_t columns1, const double **mtr2, size_t rows2, size_t columns2, double ***mtr3, size_t *rows3, size_t *columns3)
{
    if (columns1 != rows2)
    {
        return ERR_MTR_SIZE;
    }

    if (!mtr1 || !mtr2)
    {
        return ERR_EMPTY;
    }

    double **tmp = matrix_alloc(rows1, columns2);

    if (!tmp)
    {
        return ERR_MEMORY;
    }
	
    for (int i = 0; i < rows1; i++) 
    {
        for (int j = 0; j < columns2; j++) 
        {
            tmp[i][j] = 0;
            for (int k = 0; k < columns1; k++)
            {
                tmp[i][j] += mtr1[i][k] * mtr2[k][j];
            }
        }
    }
    *rows3 = rows1;
    *columns3 = columns2;
    *mtr3 = tmp;

    return ERR_OK;
}
