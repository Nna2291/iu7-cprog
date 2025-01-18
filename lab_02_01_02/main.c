#include "stdio.h"

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_EMPTY 3
#define N 10


/*
 * @brief   Функция для ввода массива
 *
 * @param[in]   array[]   Указатель на массив
 * @param[in]   *n   Указатель на размер массива
 *
 * @return  Код ошибки
 */
int input(int array[], size_t *n)
{
    printf("Input n: ");
    if (scanf("%zu", n) != 1)
        return ERR_IO;

    if (*n > N || *n == 0)
        return ERR_RANGE;

    printf("Input integers of array: \n");
    for (size_t i = 0; i < *n; i++)
    {
        if (scanf("%d", &array[i]) != 1)
            return ERR_IO;
    }

    return ERR_OK;
}

/*
 * @brief   Функция для нахождения среднего арифмитического отрицательных значений
 *
 * @param[in]   array[]   Указатель на массив
 * @param[in]   n   Размер массива
 * @param[out]   *answer   Указатель на количество элементов
 *
 * @return  Код ошибки
 */
int find_negative_middle_value(const int array[], size_t n, double *answer)
{
    double negative_sum = 0;
    int quantity = 0;

    for (size_t i = 0; i < n; i++)
    {
        if (array[i] < 0)
        {
            quantity += 1;
            negative_sum += array[i];
        }
    }

    if (quantity == 0)
    {
        return ERR_EMPTY;
    }
    *answer = negative_sum / quantity;
    return ERR_OK;
}


int main(void)
{
    int array[N];

    double answer;
    size_t n;

    int rc = input(array, &n);
    if (rc != ERR_OK)
    {
        return rc;
    }

    rc = find_negative_middle_value(array, n, &answer);

    if (rc != ERR_OK)
    {
        printf("No negative numbers!\n");
        return rc;
    }
    printf("Middle value of negatives number: %lf\n", answer);
    return ERR_OK;
}
