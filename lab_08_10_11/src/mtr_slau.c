#include "mtr_slau.h"
#include "errors.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Универсальный обмен элементов по адресам
static void swap_elements(void *l, void *r, size_t elem_size)
{
    char tmp[elem_size];
    memcpy(tmp, l, elem_size);
    memcpy(l, r, elem_size);
    memcpy(r, tmp, elem_size);
}

// Обмен двух столбцов
static void swap_columns(double **matrix, size_t rows, size_t col1, size_t col2)
{
    for (size_t i = 0; i < rows; i++)
    {
        swap_elements(&matrix[i][col1], &matrix[i][col2], sizeof(double));
    }
}

// Поиск максимального элемента в строке
static double find_row_max(const double *array, size_t n, size_t *max_index)
{
    double max_element = array[0];
    size_t temp_ind = 0;

    for (size_t i = 1; i < n; i++)
    {
        if (fabs(array[i]) > fabs(max_element))
        {
            temp_ind = i;
            max_element = array[i];
        }
    }

    *max_index = temp_ind;
    return max_element;
}

// Деление строки на число
static int divide_row(double *row, size_t n, double delim)
{
    if (delim == 0)
    {
        return ERR_SOLUTION;
    }
    for (size_t i = 0; i < n; i++)
    {
        row[i] /= delim;
    }

    return ERR_OK;
}

// Вычитание из строки row_from строки row_which, которая умножена на multiplyer
static void minus_row_multiplyed_by(double *row_from, size_t n, double *row_which, double multiplyer)
{
    for (size_t i = 0; i < n; i++)
    {
        row_from[i] -= row_which[i] * multiplyer;
    }
}

// Сортировка по ключам
static void sort_by_keys(size_t *key_arr, double **arr, size_t rows, size_t size_of_elem, size_t size_of_key)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < rows - 1; j++)
        {
            if (key_arr[j] > key_arr[j + 1])
            {
                swap_elements(&arr[j][0], &arr[j + 1][0], size_of_elem);
                swap_elements(&key_arr[j], &key_arr[j + 1], size_of_elem);
            }
        }
    }
}

// Обратный ход для матрицы
static void back_substitution(double **matrix, double **solution, size_t rows, size_t columns, size_t *column_order)
{
    for (size_t i = rows; i > 0; i--) 
    {
        size_t row = i - 1;
        solution[row][0] = matrix[row][columns - 1];
        for (size_t j = row + 1; j < rows; j++)
        {
            solution[row][0] -= matrix[row][j] * solution[j][0];
        }
    }
    sort_by_keys(column_order, solution, rows, sizeof(solution[0][0]), sizeof(column_order[0]));
}

// Решение методом гаусса
int gauss_solve(double **mtr1, double **mtr2, size_t rows1, size_t columns1)
{
    if (!mtr1 || !mtr2)
    {
        return ERR_EMPTY;
    }

    if (rows1 <= 0 || columns1 <= 0)
    {
        return ERR_MTR_SIZE;
    }

    if (columns1 != rows1 + 1)
    {
        return ERR_SOLUTION;
    }

    int rc = ERR_OK;
    size_t columns_of_slau = columns1 - 1;

    // Создадим массив, который будет хранить порядок переменных в нашей СЛАУ
    size_t *column_order = calloc(columns_of_slau, sizeof(size_t));

    if (!column_order)
    {
        return ERR_MEMORY;
    }

    // Заполним этот массив исходными позициями
    for (size_t i = 0; i < columns_of_slau; i++)
    {
        column_order[i] = i;
    }

    for (size_t i = 0; i < rows1; i++)
    {
        size_t max_index;
        // Найдем максимум в столбце
        double max_element = find_row_max(mtr1[i], columns_of_slau, &max_index);

        // Установим столбец с максимальным элементом в позицию стобца, который необходимо обнулить
        swap_columns(mtr1, rows1, i, max_index);
        swap_elements(&column_order[i], &column_order[max_index], sizeof(column_order[i]));
        // Получим 1
        rc = divide_row(mtr1[i], columns1, max_element);
        if (rc != ERR_OK)
        {
            free(column_order);
            return rc;
        }
        
        // Занулим строки снизу
        for (size_t j = i + 1; j < rows1; j++)
        {
            minus_row_multiplyed_by(mtr1[j], columns1, mtr1[i], mtr1[j][i]);
        }
    }
    back_substitution(mtr1, mtr2, rows1, columns1, column_order);
    free(column_order);
    return rc;
}
