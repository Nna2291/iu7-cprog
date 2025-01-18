#ifndef SORTING_H__
#define SORTING_H__

#include <stdlib.h>

typedef int (*cmp_t)(const void *l, const void *r);

/// @brief Функция-компоратор для сравнения двух целых чисел
/// @param l Указатель на первый элемент
/// @param r Указатель на второй элемент
/// @return Целое число. Если вовзращается положительное число, то первый элемент больше второго.
/// @return Если вовзращается нуль, то первый элемент равен второму.
/// @return Если вовзращается отрицательное число, то первый элемент меньше второго.
int int_cmp(const void *l, const void *r);

/// @brief Функция сортировки вставками
/// @param arr Массив
/// @param arr_size Размер массива
/// @param elem_size Размер элемента массива
/// @param cmp Функция-компоратор
void mysort(void *arr, size_t arr_size, size_t elem_size, cmp_t cmp);

/// @brief Функция фильтр для массива
/// @param pb_src Указатель на начало исходного массива
/// @param pe_src Указатель на конец исходного массива
/// @param pb_dst Указатель на начало заполняемого массива
/// @param pe_dst Указатель на начало заполняемого массива
/// @return Код ошибки
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif
