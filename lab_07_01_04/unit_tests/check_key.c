#include <stdlib.h>
#include <stdbool.h>
#include <check.h>
#include "errors.h"
#include "compare.h"
#include "constants.h"
#include "check_key.h"


// Тест для одного подходящего числа
START_TEST(test_key_base)
{
    int a[] = {1, 10, 54, 3};
    int a_true[] = {54};
    int *b_pb = NULL, *b_pe = NULL;
    size_t size_a = sizeof(a) / sizeof(a[0]);

    int rc = key(a, a + size_a, &b_pb, &b_pe);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(sizeof(a_true) / sizeof(a_true[0]), b_pe - b_pb);

    ck_assert_int_eq(compare_int_arrays(a_true, b_pb, b_pe - b_pb), ARRAY_EQUAL);
    free(b_pb);
}
END_TEST

// Тест для массива отрицательных чисел
START_TEST(test_key_negative)
{
    int a[] = {-100, -20, -30, -10};
    int a_true[] = {-20, -30, -10};
    int *b_pb = NULL, *b_pe = NULL;
    size_t size_a = sizeof(a) / sizeof(a[0]);

    int rc = key(a, a + size_a, &b_pb, &b_pe);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(sizeof(a_true) / sizeof(a_true[0]), b_pe - b_pb);

    ck_assert_int_eq(compare_int_arrays(a_true, b_pb, b_pe - b_pb), ARRAY_EQUAL);
    free(b_pb);
}
END_TEST

// Тест для массива, в котором нетп подходящих значений
START_TEST(test_key_no_numbers)
{
    int a[] = {-15, -15};
    int *b_pb = NULL, *b_pe = NULL;
    size_t size_a = sizeof(a) / sizeof(a[0]);

    int rc = key(a, a + size_a, &b_pb, &b_pe);
    free(b_pb);

    ck_assert_int_eq(rc, ERR_EMPTY);
}
END_TEST

// Тест для неправильных указателей 
START_TEST(test_key_no_begin_pointer)
{
    int a[] = {-15, -15};
    int *b_pb = NULL, *b_pe = NULL;
    size_t size_a = sizeof(a) / sizeof(a[0]);

    int rc = key(NULL, a + size_a, &b_pb, &b_pe);
    free(b_pb);

    ck_assert_int_eq(rc, ERR_POINTER);
}
END_TEST

// Тест для неправильных указателей 
START_TEST(test_key_no_end_pointer)
{
    int a[] = {-15, -15};
    int *b_pb = NULL, *b_pe = NULL;

    int rc = key(a, NULL, &b_pb, &b_pe);
    free(b_pb);

    ck_assert_int_eq(rc, ERR_POINTER);
}
END_TEST

// Тест для неправильных указателей 
START_TEST(test_key_greater_pointer)
{
    int a[] = {-15, -15};
    int *b_pb = NULL, *b_pe = NULL;
    size_t size_a = sizeof(a) / sizeof(a[0]);

    int rc = key(a + size_a, a, &b_pb, &b_pe);
    free(b_pb);

    ck_assert_int_eq(rc, ERR_POINTER);
}
END_TEST

Suite* test_key(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;
    s = suite_create("test_key");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatibes");

    tcase_add_test(tc_pos, test_key_base);
    tcase_add_test(tc_pos, test_key_negative);

    tcase_add_test(tc_neg, test_key_no_numbers);
    tcase_add_test(tc_neg, test_key_no_begin_pointer);
    tcase_add_test(tc_neg, test_key_no_end_pointer);
    tcase_add_test(tc_neg, test_key_greater_pointer);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
