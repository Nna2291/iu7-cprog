#include "associative_array.h"
#include "check_min.h"
#include <check.h>

// Поиск минимального элемента
START_TEST(test_assoc_array_min)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key3", 3);
    assoc_array_insert(arr, "key1", 15);
    assoc_array_insert(arr, "key2", 2);

    int *value;
    assoc_array_error_t err = assoc_array_min(arr, &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(value);
    ck_assert_int_eq(*value, 15);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

// Поиск в пустом массиве
START_TEST(test_assoc_array_min_empty)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    int *value;
    assoc_array_error_t err = assoc_array_min(arr, &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

// Неверные аргументы
START_TEST(test_assoc_array_min_params)
{
    assoc_array_error_t err = assoc_array_min(NULL, NULL);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    err = assoc_array_min(arr, NULL);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

Suite *test_min(void)
{
    Suite *s = suite_create("test_min");
    TCase *tc_pos = tcase_create("positives");
    TCase *tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, test_assoc_array_min);
    tcase_add_test(tc_neg, test_assoc_array_min_empty);
    tcase_add_test(tc_neg, test_assoc_array_min_params);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
