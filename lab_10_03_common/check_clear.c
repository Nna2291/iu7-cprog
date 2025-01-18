#include "associative_array.h"
#include "check_clear.h"
#include <check.h>

// Очистка массива
START_TEST(test_assoc_array_clear)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key1", 42);

    assoc_array_error_t err = assoc_array_clear(arr);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    int *value;
    err = assoc_array_find(arr, "key1", &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

// Неверные аргументы
START_TEST(test_assoc_array_clear_params)
{
    assoc_array_error_t err = assoc_array_clear(NULL);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

Suite *test_clear(void)
{
    Suite *s = suite_create("test_clear");
    TCase *tc_pos = tcase_create("positives");
    TCase *tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, test_assoc_array_clear);
    tcase_add_test(tc_neg, test_assoc_array_clear_params);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
