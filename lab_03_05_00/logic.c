#include "logic.h"

/*
 * @brief   Функция для определения является ли число простым
 *
 * @param[in]   x   Число для проверки
 *
 * @return Истина/ложь
 */
bool is_prime(int x)
{
    if (x < 2)
        return false;

    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            return false;
        }
    }

    return true;
}

/*
 * @brief   Функция для заполнения массива простыми числами
 *
 * @param[in]   array[] указатель на заполняемый массив
 * @param[in]   matrix[][M] указатель на матрицу
 * @param[in]   n   Количсество строк
 * @param[in]   m Количество столбцов
 *
 * @return Размер массива
 */
int put_primes(int array[], const int matrix[][M], size_t n, size_t m)
{
    int index = 0;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (is_prime(matrix[i][j]))
            {
                array[index] = matrix[i][j];
                index++;
            }
        }
    }
    return index;
}

/*
 * @brief   Функция для разворота массива
 *
 * @param[in]   array[] указатель на массив
 * @param[in]   n   Количсество элементов
 *
 */
void reverse_array(int array[], int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        int temp = array[i];
        array[i] = array[n - 1 - i];
        array[n - 1 - i] = temp;
    }
}

/*
 * @brief   Функция для заполнения матрицы обратно
 *
 * @param[in]   array[] указатель на массив
 * @param[in]   matrix[][M] указатель на матрицу
 * @param[in]   n   Количсество строк
 * @param[in]   m Количество столбцов
 *
 */
void put_back_in_matrix(const int array[], int matrix[][M], size_t n, size_t m)
{
    int count = 0;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (is_prime(matrix[i][j]))
            {
                matrix[i][j] = array[count++];
            }
        }
    }
}
