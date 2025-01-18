#ifndef __MTR_IO_H__
#define __MTR_IO_H__

#include <stdio.h>
#include <stddef.h>

/// @brief Функция для считывания матрицы из файла
/// @param f Файловая перменная
/// @param data Матрицы
/// @param n Количество строк
/// @param m Количество столбцов
/// @return Код ошибки
int matrix_create(const char *fname, double ***data, size_t *n, size_t *m);


/// @brief Функция для вывода матрицы в файл
/// @param filename  Название файла
/// @param mtr Матрица
/// @param rows Количество строк
/// @param columns Количество столбцо
/// @return 
int matrix_fprint(const char *filename, const double **mtr, size_t rows, size_t columns);


#endif
