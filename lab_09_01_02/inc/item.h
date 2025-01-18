#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdbool.h>

#define EPSILON 1e-8 // Точность для сравнения чпт
#define TITLE_LEN_FOR_READ (TITLE_LEN + 2) // Буфер для считывания названия

typedef struct
{
    char *title;
    double weight;
    double volume;
    double density;
} item_t;

/*
 * @brief   Функция для рассчета плотности вещи
 *
 * @param[in]   item  Указатель на структуру вещи
 *
 * @return  Плотность вещи
 */
double calculate_density(double weight, double volume);

int item_read(FILE *f, item_t *item);

/*
 * @brief   Функция для вывода информации о вещи
 *
 * @param[in]   item1  Указатель на структуру вещи
 *
 */
void item_print(const item_t *item);

/*
 * @brief   Функция для сравнения двух вещей по плотности
 *
 * @param[in]   item1  Указатель на структуру первой вещи
 * @param[in]   item1  Указатель на структуру второй вещи
 *
 * @return  Больше ли плотность первой вещи или нет
 */
bool compare_item_by_density(const item_t *item1, const item_t *item2);

/*
 * @brief   Функция для проверки наличия подстроки в названии вещи
 *
 * @param[in]   item1  Указатель на структуру первой вещи
 * @param[in]   substr  Искомая подстрока
 *
 * @return  Есть ли подстрока в названии или нет
 */
bool item_substr(const item_t *item1, const char *substr);

void item_free_content(item_t *pitem);

int item_copy(item_t *pdst, const item_t *psrc);

int item_cmp(const item_t *item1, const item_t *item2);

#endif
