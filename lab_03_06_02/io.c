#include "io.h"
#include "errors.h"

/*
 * @brief   Функция для ввода размеров матрицы
 *
 * @param[out]   *n   Количсество строк
 * @param[out]   *m Количество столбцов
 *
 * @return  Код ошибки
 */
int matrix_input(size_t *n, size_t *m)
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
        return ERR_IO;
    }

    return ERR_OK;
}

/*
 * @brief   Функция для вывода матрицы
 *
 * @param[in]   matrix[][M] указатель на матрицу
 * @param[in]   n   Количсество строк
 * @param[in]   m Количество столбцов
 *
 */
void print_matrix(const int array[][M], size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}
