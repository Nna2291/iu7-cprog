#ifndef MTR_ALLOC__
#define MTR_ALLOC__

#include <stdlib.h>

/// @brief Функция для выделения памяти матрицы
/// @param n Количество строк
/// @param m Количество столбцов
/// @return Матрицы
double **matrix_alloc(size_t n, size_t m);

/// @brief Функция для освобождения матрицы
/// @param mtr Матрица
/// @param n Количество строк матрицы
void matrix_free(double **mtr, size_t n);

#endif
