#ifndef ARR_LOC__
#define ARR_LOC__

#include <stdlib.h>

/// @brief Функция для освобождение массива
/// @param pb Указатель на начало массива
void array_free(int *pb);

/// @brief Функция для выделения памяти под массив
/// @param n Размер массива
/// @return Код ошибки
int *array_calloc(size_t n);

#endif