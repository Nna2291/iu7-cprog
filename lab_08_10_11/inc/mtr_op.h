#ifndef MTR_OP_H__
#define MTR_OP_H__

#include <stddef.h>

/// @brief Функция для сложения матрицы
/// @param mtr1 Матрица слогаемое
/// @param mtr2 Матрица слогаемое
/// @param mtr3 Матрица сумма
/// @param rows1 Количество строк в первой матрице
/// @param columns1 Количетсво столбцов в первой матрице
/// @param rows2 Количество строк во второй матрице
/// @param columns2 Количетсво столбцов во второй матрице
/// @param rows3 Количество строк в третьей
/// @param columns3 Количетсво столбцов в третьей матрице
/// @return Код ошибки
int sum_matrix(const double **mtr1, size_t rows1, size_t columns1, 
const double **mtr2, size_t rows2, size_t columns2,
double ***mtr3, size_t *rows3, size_t *columns3);

/// @brief Функция для умножения матриц
/// @param mtr1 Матрица слогаемое
/// @param mtr2 Матрица слогаемое
/// @param mtr3 Матрица сумма
/// @param rows1 Количество строк в первой матрице
/// @param columns1 Количетсво столбцов в первой матрице
/// @param rows2 Количество строк во второй матрице
/// @param columns2 Количетсво столбцов во второй матрице
/// @param rows3 Количество строк в третьей
/// @param columns3 Количетсво столбцов в третьей матрице
/// @return Код ошибки
int multiply_matrix(const double **mtr1, size_t rows1, size_t columns1, 
const double **mtr2, size_t rows2, size_t columns2,
double ***mtr3, size_t *rows3, size_t *columns3);

/// @brief Функция для решения СЛАУ методом Гаусса
/// @param mtr1 СЛАУ со свободными членами
/// @param mtr2 Столбец решений
/// @param rows1 Количество строк
/// @param columns1 Количетсво столбцов
/// @return Код ошибки
int gauss_solve(double **mtr1, double **mtr2, size_t rows1, size_t columns1);

#endif
