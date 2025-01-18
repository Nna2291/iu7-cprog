#include "associative_array.h"
#include "check_remove.h"
#include <check.h>

// Удаление элемента из массива
START_TEST(test_assoc_array_remove)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key1", 42);

    assoc_array_error_t err = assoc_array_remove(arr, "key1");
    ck_assert_int_eq(err, ASSOC_ARRAY_OK);

    int *value;
    err = assoc_array_find(arr, "key1", &value);
    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

// Удаление элемента, которого не существует
START_TEST(test_assoc_array_remove_not_found)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key7", 42);
    assoc_array_insert(arr, "key8", 42);
    assoc_array_insert(arr, "key9", 42);
    assoc_array_insert(arr, "key8", 42);
    assoc_array_insert(arr, "key5", 42);
    assoc_array_insert(arr, "key4", 42);
    assoc_array_insert(arr, "key3", 42);
    assoc_array_insert(arr, "key2", 42);

    assoc_array_error_t err = assoc_array_remove(arr, "key12");
    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

// Поиск в пустом массиве
START_TEST(test_assoc_array_clear_and_find)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);

    assoc_array_insert(arr, "key1", 42);
    assoc_array_clear(arr);

    assoc_array_error_t err = assoc_array_remove(arr, "key1");
    ck_assert_int_eq(err, ASSOC_ARRAY_NOT_FOUND);
    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
// Неверные аргументы
START_TEST(test_assoc_array_remove_params)
{
    assoc_array_error_t err = assoc_array_remove(NULL, "");
    ck_assert_int_eq(err, ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

Suite *test_remove(void)
{
    Suite *s = suite_create("test_remove");
    TCase *tc_pos = tcase_create("positives");
    TCase *tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, test_assoc_array_remove);
    tcase_add_test(tc_neg, test_assoc_array_remove_not_found);
    tcase_add_test(tc_neg, test_assoc_array_remove_params);
    tcase_add_test(tc_neg, test_assoc_array_clear_and_find);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
