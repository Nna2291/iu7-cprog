#include "logic.h"

/*
 * @brief   Подсчет суммы цифр в числе
 *
 * @param[in]   int n анализируемое число
 *
 * @return  sum сумма цифр в числе
 */
int sum_of_digit(int n)
{
    int sum = 0;
    n = abs(n);

    while (n > 0)
    {
        sum += n % DIVIDER;
        n /= DIVIDER;
    }
    return sum;
}



/*
 * @brief   Функция для вставки строки в матрицу
 *
 * @param[in]   int matrix[][M] указатель на матрицу
 * @param[in]   n   Количсество строк
 * @param[in]   m Количество столбцов
 * @param[in]   index Индекс для новой строки
 *
 * @return  Код ошибки
 */
//void insert_row(int matrix[][M_INPUT], size_t n, size_t m, size_t index)
//{
//    for (size_t i = n + 1; i > index; i--)
//    {
//        for (size_t j = 0; j < m; j++)
//        {
//            matrix[i][j] = matrix[i - 1][j];
//        }
//    }
//    for (size_t i = 0; i < m; i++)
//    {
//        matrix[index][i] = -1;
//    }
//}

/*
 * @brief   Функция для присваивание одного массива другому
 *
 * @param[in]   int array1[] указатель на первый массив
 * @param[in]   int array2[]   указатель на второй массив
 * @param[in]   m Количество элементов в массиве
 *
 * @return  Код ошибки
 */
void assigne_array(int *array1, const int *array2, size_t m)
{
    for (size_t i = 0; i < m; i++)
    {
        array1[i] = array2[i];
    }
}

/*
 * @brief   Функция для заполнения массива числом
 *
 * @param[in]   int row[] указатель на массив
 * @param[in]   m Количество столбцов
 * @param[in]   digit Число
 *
 */
void fill_array(int row[], size_t m, int digit)
{
    for (size_t i = 0; i < m; i++)
    {
        row[i] = digit;
    }
}

/*
 * @brief   Функция для вставки строки в матрицу
 *
 * @param[in]   int matrix[][M] указатель на матрицу
 * @param[in]   n   Количсество строк
 * @param[in]   m Количество столбцов
 * @param[in]   index Индекс для новой строки
 *
 * @return  Код ошибки
 */
void insert_row(int matrix[][M_INPUT], size_t n, size_t m, size_t index, int row[])
{
    for (size_t i = n + 1; i > index; i--)
    {
        assigne_array(matrix[i], matrix[i - 1], m);
    }
    assigne_array(matrix[index], row, m);
}


/*
 * @brief   Функция для нахождения колчиества элементов в строке где, сумма цифр каждого из которых нечётна
 *
 * @param[in]   row[] указатель на строку
 * @param[in]   m Количество элементов
 *
 * @return  Количество
 */
int count_not_prime_sum(const int row[], size_t m)
{
    int counter = 0;
    for (size_t j = 0; j < m; j++)
    {
        if (sum_of_digit(row[j]) % 2 != 0)
        {
            counter += 1;
        }
    }
    return counter;
}

/*
 * @brief   Функция для заполнения матрица
 *
 * @param[in]   matrix[][M] указатель на матрицу
 * @param[in]   *n   Указатель на количсество строк
 * @param[in]   m   Количество столбцов
 *
 * @return  Истина/ложь
 */
void analyse_rows(int matrix[][M_INPUT], size_t *n, size_t m)
{
    size_t i = 0;
    int row[N];
    fill_array(row, m, DIGIT);
    while (i < (*n))
    {
        if (count_not_prime_sum(matrix[i], m) >= COUNT)
        {
            insert_row(matrix, *n, m, i, row);
            (*n)++;
            i++;
        }
        i++;
    }
}
