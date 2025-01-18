#include "logic.h"

/*
 * @brief   Функция для проверки является ли данная цифра последней в числе
 *
 * @param[in]   number число для проверки
 * @param[in]   int digit цифра для проверки
 *
 * @return  Истина/Ложь
 */
bool is_last_digit(int number, int digit)
{
    number = abs(number);
    return number % DIVIDER == digit;
}

/*
 * @brief   Функция для нахождения максимального числа оканчивающегося на данную цифру под побочной диагональю матрицы
 *
 * @param[in]   matrix[][M] указатель на матрицу
 * @param[in]   n цифра для проверки
 *
 * @return  Код ошибки
 */
int find_maximum_value(const int matrix[][M], size_t n, int *answer)
{
    for (size_t i = n; i > 0; i--)
    {
        for (size_t j = n - i + 1; j < n; j++)
        {
            int element = matrix[j][i - 1];
            if (is_last_digit(element, LAST_DIGIT))
            {
                *answer = element;
                break;
            }
        }
    }
    if (*answer == 0)
    {
        return ERR_EMPTY;
    }
    for (size_t i = n; i > 0; i--)
    {
        for (size_t j = n - i + 1; j < n; j++)
        {
            int element = matrix[j][i - 1];
            if (element > *answer && is_last_digit(element, LAST_DIGIT))
            {
                *answer = element;
            }
        }
    }
    return ERR_OK;
}
