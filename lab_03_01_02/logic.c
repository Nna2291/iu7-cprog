#include "logic.h"
#include <stdbool.h>

/*
 * @brief   Функция для определения чередования знаков чисел в столбце
 *
 * @param[in]   matrix[][M] указатель на матрицу
 * @param[in]   n   Количсество строк
 * @param[in]   k Индекс столбца
 *
 */
int analyse_columm(const int matrix[][M], size_t n, size_t k)
{
    if (matrix[0][k] == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 0;
    }
    bool status = (matrix[0][k] < 0);
    for (size_t i = 1; i < n; i++)
    {
        if (status == (matrix[i][k] < 0) || (matrix[i][k] == 0))
        {
            return 0;
        }
        status = (matrix[i][k] < 0);
    }
    return 1;
}

/*
 * @brief   Функция для заполнения массива
 *
 * @param[in]   matrix[][M] указатель на матрицу
 * @param[out]   arr[] указатель на заполняемый массив
 * @param[in]   n   Количсество строк
 * @param[in]   m Количество столбцов
 *
 */
void fill_array(const int matrix[][M], int arr[], size_t n, size_t m)
{
    for (size_t k = 0; k < m; k++)
    {
        arr[k] = analyse_columm(matrix, n, k);
    }
}
