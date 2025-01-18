#include <stdio.h>
#include <stdbool.h>

#define N 10

#define ERR_OK 0
#define ERR_IO 1
#define ERR_RANGE 2

/*
 * @brief   Функция для ввода массива
 *
 * @param[in]   array[]   Указатель на массив
 * @param[in]   *n   Указатель на размер массива
 *
 * @return  Код ошибки
 */
int input_array(int *pa, int *pb)
{
    for (int *p_current = pa; p_current < pb; p_current++)
    {
        if (scanf("%d", p_current) != 1)
        {
            return ERR_IO;
        }
    }
    return ERR_OK;
}

/*
 * @brief   Функция для сравнения элемента массива с предыдущими
 *
 * @param[in]   *p_current   Указатель на массив
 * @param[in]   *pa   Указатель на массив
 *
 * @return  0 или 1 в зависимости от наличия такого элемента в массиве равнее
 */
int compare_with_prev_value(const int *p_current, const int *pa)
{
    for (const int *p_current2 = p_current - 1; p_current2 >= pa; p_current2--)
    {
        if (*p_current == *p_current2)
        {
            return 0;
        }
    }
    return 1;
}

/*
 * @brief   Функция для поиска уникальных значений в массиве
 *
 * @param[in]   *pa   Указатель на массив
 * @param[in]   *pb   Указатель на массив
 *
 * @return  Количество уникальных элементов
 */
int find_unique_values(const int *pa, const int *pb)
{
    int answer = 0;

    for (const int *p_current = pa; p_current < pb; p_current++)
    {
        int value = compare_with_prev_value(p_current, pa);

        answer += value;
    }
    return answer;
}

int main(void)
{
    int array[N];
    size_t n;

    printf("Input n: ");
    if (scanf("%zu", &n) != 1)
        return ERR_IO;

    if (n > N || n == 0)
        return ERR_RANGE;

    int *pa = array;
    int *pb = array + n;

    printf("Input integers of array: \n");
    int rc = input_array(pa, pb);

    if (rc != ERR_OK)
    {
        return rc;
    }

    int answer = find_unique_values(pa, pb);
    printf("Unique elements: %d", answer);

    return ERR_OK;
}
