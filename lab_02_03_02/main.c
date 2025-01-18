#include "stdio.h"
#include "stdbool.h"

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_EMPTY 3
#define N 10

/*
 * @brief Функция для проверки является ли число полным квадратом
 *
 * @param[in] n Число для проверки
 *
 * @return Является или нет
 */
bool is_square(int n)
{
    int root = 0;
    while (root * root < n)
    {
        root += 1;
    }
    if (root * root == n)
    {
        return true;
    }
    return false;
}

/*
 * @brief   Функция для ввода массива
 *
 * @param[in]   array[]   Указатель на массив
 * @param[in]   *n   Указатель на размер массива
 *
 * @return  Код ошибки
 */
int input(int a[], size_t *n)
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
 * @brief Функция для вывода массива
 *
 * @param[in] array[] Указатель на массив
 * @param[in]   n   Размер массива
 *
 */
void print_array(const int a[], size_t n)
{
    printf("New array: \n");
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/*
 * @brief Функция для удаления элемента из массива
 *
 * @param[in] array[] Указатель на массив
 * @param[in]   index   Индекс удаления
 * @param[in]   *n   Указатель на размер массива
 *
 */
int remove_element_from_array(int array[], size_t *n, size_t index)
{
    if (index > *n - 1)
    {
        return ERR_RANGE;
    }
    while (index < *n - 1)
    {
        array[index] = array[index + 1];
        index++;
    }
    (*n)--;
    return ERR_OK;
}

/*
 * @brief Функция для удаления числа, которое является полным квадратом из массива
 *
 * @param[in] array[] Указатель на массив
 * @param[in] *n Указатель на размер массива
 *
 */
int edit_array(int *array, size_t *n)
{
    int rc;
    size_t i = 0;
    while (i < *n)
    {
        if (is_square(array[i]))
        {
            rc = remove_element_from_array(array, n, i);
            if (rc != ERR_OK)
            {
                return rc;
            }
        }
        else
        {
            i++;
        }
    }
    return ERR_OK;
}

int main(void)
{
    int array[N];
    size_t n = 0;

    int rc = input(array, &n);
    if (rc != ERR_OK)
    {
        return rc;
    }
    edit_array(array, &n);
    if (n == 0)
    {
        printf("Empty array!\n");
        return ERR_EMPTY;
    }
    print_array(array, n);
}
