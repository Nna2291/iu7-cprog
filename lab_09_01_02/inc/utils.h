#ifndef UTILS_H__
#define UTILS_H__

#include <stdbool.h>

/*
 * @brief   Функция для сравнения двух вещественных чисел
 *
 * @param[in]   a   Первое сравнимое число
 * @param[in]   b   Второе сравнимое число
 * @param[in]   eps Точность сравнения
 *
 * @return  Результат сравнения
 */
int compare_double(double a, double b, double eps);

#endif
