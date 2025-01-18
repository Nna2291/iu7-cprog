#include "associative_array.h"
#include "check_each.h"
#include <check.h>

void increment_values(const char *key, int *num, void *param)
{
    (void) param;
    (void) key;
    if (num)
    {
        (*num)++;
    }
}

// Применение функции к каждому элементу в массиве
START_TEST(test_assoc_array_each)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key1", 1);
    assoc_array_insert(arr, "key2", 2);
    assoc_array_insert(arr, "key3", 3);

    assoc_array_error_t err = assoc_array_each(arr, increment_values, NULL);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    int *value;
    assoc_array_find(arr, "key1", &value);
    ck_assert_int_eq(*value, 2);

    assoc_array_find(arr, "key2", &value);
    ck_assert_int_eq(*value, 3);

    assoc_array_find(arr, "key3", &value);
    ck_assert_int_eq(*value, 4);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

// Неверные аргументы
START_TEST(test_assoc_array_each_params)
{
    assoc_array_error_t err = assoc_array_each(NULL, increment_values, NULL);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    err = assoc_array_each(arr, NULL, NULL);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

Suite *test_each(void)
{
    Suite *s = suite_create("test_each");
    TCase *tc_pos = tcase_create("positives");
    TCase *tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, test_assoc_array_each);
    tcase_add_test(tc_neg, test_assoc_array_each_params);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
