#include "io.h"
#include <stdio.h>
/*
 * @brief   Функция для ввода матрицы
 *
 * @param[in]   matrix[][M] указатель на матрицу
 * @param[out]   *n   Количсество строк
 * @param[out]   *m Количество столбцов
 *
 * @return  Код ошибки
 */
int matrix_input(int matrix[][M], size_t *n, size_t *m)
{
    printf("Input number of rows: ");
    if (scanf("%zu", n) != 1)
    {
        return ERR_IO;
    }

    printf("Input number of columns: ");
    if (scanf("%zu", m) != 1)
    {
        return ERR_IO;
    }

    if (*n > N || *m > M || *n == 0 || *m == 0)
    {
        return ERR_RANGE;
    }

    printf("Input elements: ");
    for (size_t i = 0; i < *n; i++)
    {
        for (size_t j = 0; j < *m; j++)
        {
            if (scanf("%d", &matrix[i][j]) != 1)
            {
                return ERR_IO;
            }
        }
    }

    return ERR_OK;
}

/*
 * @brief   Функция для вывода массива
 *
 * @param[in]   array[] указатель на массив
 * @param[in]   n   Количсество элементов
 *
 */
void print_array(const int array[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
