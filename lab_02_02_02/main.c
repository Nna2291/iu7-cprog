#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_EMPTY 3
#define DIVIDER 10
#define N 10

/*
 * @brief   Функция для ввода массива
 *
 * @param[in]   array[]   Указатель на массив
 * @param[in]   *n   Указатель на размер массива
 *
 * @return  Код ошибки
 */
int input(int *a, size_t *n)
{
    printf("Input n: ");
    if (scanf("%zu", n) != 1)
        return ERR_IO;

    if (*n > N || *n == 0)
        return ERR_RANGE;

    printf("Input integers of array: \n");
    for (size_t i = 0; i < *n; i++)
    {
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;
    }

    return ERR_OK;
}

/*
 * @brief Функция для проверки начинается ли число на одну и ту же цифру
 *
 * @param[in] n Число для проверки
 *
 * @return Является или нет
 */
bool is_first_and_last_digit_same(int n)
{
    n = abs(n);
    int first_digit;
    int last_digit = n % DIVIDER;
    n /= DIVIDER;
    if (n == 0)
    {
        return true;
    }

    while (n > 0)
    {
        first_digit = n % DIVIDER;
        n /= DIVIDER;
    }

    return last_digit == first_digit;
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
        printf(" %d", array[i]);
    }
}

/*
 * @brief Функция для заполнения нового массива
 *
 * @param[in] array1[] Указатель на исходный массив
 * @param[in]   n1   Размер исходного массива
 * @param[in] array2[] Указатель на заполняемый массив
 * @param[in]   n2   Размер заполняемого массива
 *
 */
void fill_new_array(const int array1[], size_t n1, int array2[], size_t *n2)
{
    size_t index = 0;
    for (size_t i = 0; i < n1; i++)
    {
        if (is_first_and_last_digit_same(array1[i]))
        {
            array2[index] = array1[i];
            index++;
        }
    }
    *n2 = index;
}


int main(void)
{
    int array1[N];
    int array2[N];
    int rc;

    size_t n1;
    size_t n2;

    rc = input(array1, &n1);
    if (rc != ERR_OK)
    {
        return rc;
    }

    fill_new_array(array1, n1, array2, &n2);

    if (n2 == 0)
    {
        printf("Empty array!\n");
        return ERR_EMPTY;
    }

    printf("New array:");
    print_array(array2, n2);
    printf("\n");
    return ERR_OK;
}
