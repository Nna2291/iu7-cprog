#include "errors.h"
#include "array_io.h"
#include "array_loc.h"


/// @brief Функция получения длины массива, записанного в файл
/// 
/// @param f Файловая перменная
/// @param n Указатель на размер массива
/// @return Код ошибки
static int read_array_len(FILE *f, size_t *n)
{
    int temp;
    int rc;
    size_t n_temp = 0;

    while ((rc = fscanf(f, "%d", &temp)) == 1)
    {
        n_temp++;
    }

    if (rc == EOF)
    {
        *n = n_temp;
    }
    else
    {
        return ERR_IO;
    }
    return ERR_OK;
    
    // while (!feof(f))
    // {
    //     if (fscanf(f, "%d", &temp) != 1)
    //     {
    //         return ERR_IO;
    //     }
    //     n_temp++;
    // }

    // *n = n_temp;

    // return ERR_OK;
}

/// @brief Функция для чтения массива из файла
/// @param f файловая перменная
/// @param array массив
/// @param n длина массива
/// @return Код ошибки
static int read_array(FILE *f, int *pbeg, int *pend)
{
    for (int *pcur = pbeg; pcur < pend; pcur++)
    {
        if (fscanf(f, "%d", pcur) != 1)
        {
            return ERR_IO;
        }
    }

    return ERR_OK;
}


/// @brief Функция для создания массива
/// @param fname имя файла
/// @param array указатель на массив
/// @param n размер массива
/// @return Код ошибки
int create_array(FILE *f, int **pbeg, int **pend)
{
    int rc;
    size_t length = 0;

    rc = read_array_len(f, &length);
    
    if (rc != ERR_OK)
    {
        return rc;
    }

    
    int *tmp = array_calloc(length);

    if (tmp)
    {
        rewind(f);
        rc = read_array(f, tmp, tmp + length);
        if (rc == ERR_OK)
        {
            *pbeg = tmp;
            *pend = tmp + length;
        }
        else
        {
            array_free(tmp);
        }
    }
    else
    {
        rc = ERR_MEM;
    }

    return rc;
}


/// @brief Функция для записи массива в файл
/// @param fname Название файла
/// @param array_b Указатель на начало массива
/// @param array_end Указатель на конец массива
/// @return Код ошибки
int write_array(const char *fname, const int *array_b, const int *array_end)
{
    FILE *f = fopen(fname, "w");
    int rc = ERR_OK;

    if (!f)
    {
        rc = ERR_IO;
    }

    if (array_b == array_end)
    {
        rc = ERR_EMPTY; 
    }
    if (array_b > array_end)
    {
        rc = ERR_POINTER;
    }

    for (const int *pbeg = array_b; rc == ERR_OK && pbeg < array_end - 1; pbeg++)
    {
        if (rc == ERR_OK && fprintf(f, "%d ", *pbeg) < 0)
        {
            rc = ERR_IO;
        }
    }
    if (rc == ERR_OK && fprintf(f, "%d", *(array_end - 1)) < 0)
    {
        rc = ERR_IO;
    }
    fclose(f);
    return rc;
}

