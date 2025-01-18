#include "associative_array.h"
#include "check_find.h"
#include <check.h>

// Поиск элемента в массиве
START_TEST(test_assoc_array_find)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key1", 42);

    int *value;
    assoc_array_error_t err = assoc_array_find(arr, "key1", &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(value);
    ck_assert_int_eq(*value, 42);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

// Поиск несуществующего элемента в массиве
START_TEST(test_assoc_array_find_not_found)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    int *value;
    assoc_array_error_t err = assoc_array_find(arr, "key2", &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

// Неверные аргументы
START_TEST(test_assoc_array_find_params)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    int *value;
    assoc_array_error_t err = assoc_array_find(NULL, "key1", &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    err = assoc_array_find(arr, NULL, &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    err = assoc_array_find(arr, "key1", NULL);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

Suite *test_find(void)
{
    Suite *s = suite_create("test_find");
    TCase *tc_pos = tcase_create("positives");
    TCase *tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, test_assoc_array_find);
    tcase_add_test(tc_neg, test_assoc_array_find_not_found);
    tcase_add_test(tc_neg, test_assoc_array_find_params);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
