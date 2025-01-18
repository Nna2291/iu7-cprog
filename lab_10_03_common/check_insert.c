#include "associative_array.h"
#include "check_insert.h"
#include <check.h>

// Вставка элемента и вставка элемента с существующим ключем
START_TEST(test_assoc_array_insert)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_error_t err;
    err = assoc_array_insert(arr, "key1", 42);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    err = assoc_array_insert(arr, "key2", 2);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);
    err = assoc_array_insert(arr, "key3", 3);
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    err = assoc_array_insert(arr, "key1", 42);
    ck_assert_int_eq(err, ASSOC_ARRAY_KEY_EXISTS);
    err = assoc_array_insert(arr, "key2", 2);
    ck_assert_int_eq(err, ASSOC_ARRAY_KEY_EXISTS);
    err = assoc_array_insert(arr, "key3", 3);
    ck_assert_int_eq(err, ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

// Неверные аргументы
START_TEST(test_assoc_array_insert_params)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_error_t err;
    err = assoc_array_insert(NULL, "key1", 42);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    err = assoc_array_insert(arr, NULL, 99);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    err = assoc_array_insert(arr, "", 99);
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

Suite *test_insert(void)
{
    Suite *s = suite_create("test_insert");
    TCase *tc_pos = tcase_create("positives");
    TCase *tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, test_assoc_array_insert);
    tcase_add_test(tc_neg, test_assoc_array_insert_params);
    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
