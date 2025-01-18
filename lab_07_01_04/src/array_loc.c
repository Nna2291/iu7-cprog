#include "array_loc.h"

/// @brief Функция для освобождение массива
/// @param pb Указатель на начало массива
void array_free(int *pb)
{
    free(pb);
}

/// @brief Функция для выделения памяти под массив
/// @param n Размер массива
/// @return Код ошибки
int *array_calloc(size_t n)
{
    int *array;

    array = calloc(n, sizeof(int));

    if (!array)
    {
        return NULL;
    }

    return array;
}
