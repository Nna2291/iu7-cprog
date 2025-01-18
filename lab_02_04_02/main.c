#include "stdio.h"

#define ERR_OK 0
#define ERR_EMPTY 1
#define ERR_EXIT_OVERFLOW 100
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
    printf("Input integers of array: \n");
    size_t index = 0;

    while (index <= N)
    {
        int value;
        if (scanf("%d", &value) != 1)
        {
            break;
        }
        if (index <= N - 1)
        {
            array[index] = value;
        }
        index++;
    }
    if (index > N)
    {
        *n = N;
        return ERR_EXIT_OVERFLOW;
    }
    *n = index;
    if (index == 0)
    {
        return ERR_EMPTY;
    }
    return ERR_OK;
}

/*
 * @brief Функция для вывода массива
 *
 * @param[in] array[] Указатель на массив
 * @param[in]   n   Размер массива
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

/*
 * @brief Функция для свопа двух переменных
 *
 * @param[in] *xp Указатель на первую переменную
 * @param[in]   *yp   Указатель на вторую переменную
 *
 */
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/*
 * @brief Функция для сортировки выбором
 *
 * @param[in] array[] Указатель на массив
 * @param[in]   n   Размер массива
 *
 */
void selection_sort(int array[], size_t n)
{
    size_t min_idx;

    for (size_t i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (size_t j = i + 1; j < n; j++)
        {
            if (array[j] < array[min_idx])
            {
                min_idx = j;
            }
        }
        swap(&array[min_idx], &array[i]);
    }
}

int main(void)
{
    int array[N];
    size_t n = 0;

    int rc = input(array, &n);

    if (rc != ERR_OK && rc != ERR_EXIT_OVERFLOW)
    {
        return rc;
    }

    printf("Sorted array: ");
    selection_sort(array, n);
    print_array(array, n);
    return rc;
}
