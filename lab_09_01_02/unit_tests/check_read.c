#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "item.h"
#include "utils.h"
#include "errors.h"
#include "item_array.h"
#include "check_read.h"

static int are_items_eq(item_t *itm1, item_t *itm2)
{
    if (strcmp(itm1->title, itm2->title) != 0)
    {
        return 0;
    }
    if (compare_double(itm1->weight, itm2->weight, EPSILON) != 0)
    {
        return 0;
    }
    if (compare_double(itm1->volume, itm2->volume, EPSILON) != 0)
    {
        return 0;
    }
     if (compare_double(itm1->density, itm2->density, EPSILON) != 0)
    {
        return 0;
    }
    return 1;
}

static void are_array_eq(item_t *array, item_t *arr_correct, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        ck_assert_int_eq(1, are_items_eq(&array[i], &arr_correct[i]));
    }
}

// Массив из одной вещи
START_TEST(read_one_item)
{
    char* filename = "func_tests/data/unit_pos_01.txt";
    size_t n;
    FILE *f = fopen(filename, "r");

    ck_assert_ptr_nonnull(f);

    int rc = items_count(f, &n);
    ck_assert_int_eq(rc, ERR_OK);
    rewind(f);
    ck_assert_int_eq(n, 1);

    item_t *array = calloc(n, sizeof(item_t));
    item_t arr_correct[1] = {{ "item1", 10.0, 20.0, 0.5 }};

    rc = item_array_read(f, array, n);
    ck_assert_int_eq(rc, ERR_OK);

    are_array_eq(array, arr_correct, n);

    fclose(f);
    item_array_free(array, n);
}

// Массив из нескольких вещи
START_TEST(read_several_items)
{
    char* filename = "func_tests/data/unit_pos_02.txt";
    size_t n;
    FILE *f = fopen(filename, "r");

    ck_assert_ptr_nonnull(f);
    
    int rc = items_count(f, &n);
    ck_assert_int_eq(rc, ERR_OK);
    rewind(f);
    ck_assert_int_eq(n, 2);

    item_t *array = calloc(n, sizeof(item_t));
    item_t arr_correct[2] = {{ "item1", 10.0, 20.0, 0.5 }, { "item2", 20.0, 20.0, 1.0 }};

    rc = item_array_read(f, array, n);
    ck_assert_int_eq(rc, ERR_OK);
    
    are_array_eq(array, arr_correct, n);
    
    fclose(f);
    item_array_free(array, n);
}

// Файл с нулевыми массами
START_TEST(read_zero_items)
{
    char* filename = "func_tests/data/unit_neg_01.txt";
    size_t n = 1;
    FILE *f = fopen(filename, "r");

    ck_assert_ptr_nonnull(f);
    
    item_t *array = calloc(n, sizeof(item_t));

    int rc = item_array_read(f, array, n);
    ck_assert_int_eq(rc, ERR_DATA);
    
    fclose(f);
}

// Файл с отрицательными массами
START_TEST(read_negative_items)
{
    char* filename = "func_tests/data/unit_neg_02.txt";
    size_t n = 1;
    FILE *f = fopen(filename, "r");

    ck_assert_ptr_nonnull(f);
    
    item_t *array = calloc(n, sizeof(item_t));

    int rc = item_array_read(f, array, n);
    ck_assert_int_eq(rc, ERR_DATA);
    
    fclose(f);
}

// Пустой файл
START_TEST(read_no_items)
{
    char* filename = "func_tests/data/unit_neg_03.txt";
    size_t n = 1;
    FILE *f = fopen(filename, "r");

    ck_assert_ptr_nonnull(f);
    
    item_t *array = calloc(n, sizeof(item_t));

    int rc = item_array_read(f, array, n);
    ck_assert_int_eq(rc, ERR_DATA);
    
    fclose(f);
}

Suite* test_read(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;
    s = suite_create("test_read");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, read_one_item);
    tcase_add_test(tc_pos, read_several_items);
    tcase_add_test(tc_neg, read_zero_items);
    tcase_add_test(tc_neg, read_negative_items);
    tcase_add_test(tc_neg, read_no_items);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
