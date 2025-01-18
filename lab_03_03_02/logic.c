#include "logic.h"

/*
 * @brief   Функция для нахождения произведения строки
 *
 * @param[in]   array[] указатель на строку
 * @param[in]   m Количество элементов
 *
 * @return Произведение чисел строки
 */
int product_of_row(const int array[], size_t m)
{
    int answer = 1;
    for (size_t i = 0; i < m; i++)
    {
        answer *= array[i];
    }
    return answer;
}


void change_lines(int matrix[][M], size_t m, size_t a, size_t b)
{
    for (size_t j = 0; j < m; j++)
    {
        int temp = matrix[a][j];
        matrix[a][j] = matrix[b][j];
        matrix[b][j] = temp;
    }
}

void sort_matrix(int matrix[][M], size_t n, size_t m)
{
    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 0; j < n - i - 1; j++)
        {
            if (product_of_row(matrix[j], m) > product_of_row(matrix[j + 1], m))
            {
                change_lines(matrix, m, j, j + 1);
            }
        }
    }
}
