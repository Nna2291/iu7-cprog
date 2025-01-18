#include <stdio.h>
#include <string.h>
#include "errors.h"
#include "sorting.h"
#include "array_loc.h"


/// @brief Функция свопа переменных
/// @param l Первый элемент
/// @param r Второй элемент
/// @param elem_size Размер элемента
static void swap(void *l, void *r, size_t elem_size)
{
    char tmp[elem_size];
    memcpy(tmp, l, elem_size);
    memcpy(l, r, elem_size);
    memcpy(r, tmp, elem_size);
}


/// @brief Функция-компоратор для сравнения двух целых чисел
/// @param l Указатель на первый элемент
/// @param r Указатель на второй элемент
/// @return Целое число. Если вовзращается положительное число, то первый элемент больше второго.
/// @return Если вовзращается нуль, то первый элемент равен второму.
/// @return Если вовзращается отрицательное число, то первый элемент меньше второго.
int int_cmp(const void *l, const void *r)
{
    const int *pl = l;
    const int *pr = r;
    return *pl - *pr;
}

/// @brief Функция сортировки вставками
/// @param arr Массив
/// @param arr_size Размер массива
/// @param elem_size Размер элемента массива
/// @param cmp Функция-компоратор
// void mysort(void *arr, size_t arr_size, size_t elem_size, cmp_t cmp)
// {
//     char *pbeg = (char *) arr;
//     char *pend = pbeg + (arr_size * elem_size);

//     for (char *pcur = pbeg + elem_size; pcur < pend; pcur += elem_size)
//     {
//         for (char *pcur_internal = pcur; pcur_internal > pbeg && cmp(pcur_internal - elem_size, pcur_internal) > 0; pcur_internal -= elem_size)
//         {
//             swap(pcur_internal - elem_size, pcur_internal, elem_size);
//         }
//     }
// }

/// @brief Функция сортировки вставками
/// @param arr Массив
/// @param arr_size Размер массива
/// @param elem_size Размер элемента массива
/// @param cmp Функция-компоратор
void mysort(void *arr, size_t arr_size, size_t elem_size, cmp_t cmp)
{
    char *pbeg = (char*) arr;
    char *pend = pbeg + (arr_size * elem_size);

    for (char *pcur = pbeg; pcur < pend - elem_size; pcur += elem_size) 
    {
        char *min_idx = pcur;
        for (char *pcur_internal = pcur + elem_size; pcur_internal < pend; pcur_internal += elem_size) 
        {
            if (cmp(pcur_internal, min_idx) < 0)
            {
                min_idx = pcur_internal;
            }
        }

        swap(min_idx, pcur, elem_size);
    }
}

static double get_array_sum(const int *pbeg, const int *pend)
{
    double n = 0.0;
    for (const int *pcur = pbeg; pcur < pend; pcur++)
    {
        n += *pcur;
    }
    return n;
}

static size_t get_new_array_len(const int *pbeg, const int *pend, double avg)
{
    size_t n = 0;
    for (const int *pcur = pbeg; pcur < pend; pcur++)
    {
        if (*pcur > avg)
        {
            // printf("%d\n", *pcur);
            n++;
        }
    }

    return n;
}

int fill_array(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst, double avg, size_t n)
{
    int *p_dst = *pb_dst;

    for (const int *pcur = pb_src; pcur < pe_src; pcur++)
    {
        if (*pcur > avg)
        {
            *p_dst = *pcur;
            p_dst++;
        }
    }

    *pe_dst = p_dst;
    return ERR_OK;
}


/// @brief Функция фильтр для массива
/// @param pb_src Указатель на начало исходного массива
/// @param pe_src Указатель на конец исходного массива
/// @param pb_dst Указатель на начало заполняемого массива
/// @param pe_dst Указатель на начало заполняемого массива
/// @return Код ошибки
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (!pb_src || !pe_src)
    {
        return ERR_POINTER;
    }

    if (pe_src <= pb_src)
    {
        return ERR_POINTER;
    }


    double sum = get_array_sum(pb_src, pe_src);
    double avg = sum / (pe_src - pb_src);;
    // printf("%lf\n", avg);
    size_t n = get_new_array_len(pb_src, pe_src, avg);
    // printf("%zu", n);

    if (n == 0)
    {
        return ERR_EMPTY;
    }


    *pb_dst = array_calloc(n);
    if (!pb_dst)
    {
        return ERR_MEM;
    }

    int rc = fill_array(pb_src, pe_src, pb_dst, pe_dst, avg, n);

    return rc;
}
