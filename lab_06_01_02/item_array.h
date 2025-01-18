#ifndef ITEM_ARRAY_H
#define ITEM_ARRAY_H

#include "item.h"
#include <stdio.h>

#define N_MAX 15 // Максимальный размер массива

/*
 * @brief   Функция для сортировки массива с вещами
 *
 * @param[in]   array  Указатель на массив с вещами
 * @param[in]   n Размер массива
 *
 */
void sort_array(item_t *array, size_t n);

/*
 * @brief   Функция для вывода массива с вещами
 *
 * @param[in]   array  Указатель на массив с вещами
 * @param[in]   n Размер массива
 *
 */
void print_items(const item_t *array, size_t n);

/*
 * @brief   Функция для вывода массива с вещами, название которых содержит заданную подстроку
 *
 * @param[in]   array  Указатель на массив с вещами
 * @param[in]   n Размер массива
 * @param[in]   substring  Подстрока
 *
 */
void print_items_with_substr(const item_t *array, size_t n, const char *substring);

/*
 * @brief   Функция для чтения массива с вещами из файла
 *
 * @param[in]   f  Указатель на файл
 * @param[in]   array  Указатель на массив с вещами
 * @param[in]   n Указатель на размер массива
 * @param[in]   n_max  Максимальная длинна массива
 *
 */
int read_array(FILE *f, item_t *array, size_t *n, size_t n_max);

#endif
