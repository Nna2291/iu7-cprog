#include <stdlib.h>
#include <check.h>
#include <stdbool.h>
#include "errors.h"
#include "constants.h"
#include "compare.h"
#include "check_mysort.h"


static int double_cmp(const void *l, const void *r)
{
    const double *pl = l;
    const double *pr = r;
    
    if (fabs(*pl - *pr) < EPSILON)
    {
        return 0;
    }

    if ((*pl - *pr) > 0)
    {
        return 1;
    }
    return -1;
}

static int char_cmp(const void *l, const void *r)
{
    const char *pl = l;
    const char *pr = r;
    
    return *pl - *pr;
}


// static int wrong_double_cmp(const void *l, const void *r)
// {
//     const double *pl = l;
//     const double *pr = r;
    
//     return *pl - *pr;
// }

// Тест для пустого массива
START_TEST(test_empty_array)
{
    int a[] = {1};
    int b[] = {1};

    size_t a_n = 0;
    
    ck_assert_int_eq(sizeof(a), sizeof(b));

    mysort(a, a_n, sizeof(int), int_cmp);

    ck_assert_int_eq(compare_int_arrays(a, b, a_n), ARRAY_EQUAL);
}
END_TEST

// Тест для массива из 1 элемента
START_TEST(test_array_length_one)
{
    int a[] = {1};
    int b[] = {1};
    size_t a_n = sizeof(a) / sizeof(a[0]);
    
    ck_assert_int_eq(sizeof(a), sizeof(b));

    mysort(a, a_n, sizeof(int), int_cmp);

    ck_assert_int_eq(compare_int_arrays(a, b, a_n), ARRAY_EQUAL);
}
END_TEST

// Тест для неупорядоченного массива из 2ух элементов
START_TEST(test_array_length_two_not_sorted)
{
    int a[] = {2, -2};
    int b[] = {-2, 2};
    size_t a_n = sizeof(a) / sizeof(a[0]);
    
    ck_assert_int_eq(sizeof(a), sizeof(b));

    mysort(a, a_n, sizeof(int), int_cmp);

    ck_assert_int_eq(compare_int_arrays(a, b, a_n), ARRAY_EQUAL);
}
END_TEST

// Тест для упорядоченного массива из 2ух элементов
START_TEST(test_array_length_two_sorted)
{
    int a[] = {-10, 10};
    int b[] = {-10, 10};
    size_t a_n = sizeof(a) / sizeof(a[0]);
    
    ck_assert_int_eq(sizeof(a), sizeof(b));

    mysort(a, a_n, sizeof(int), int_cmp);

    ck_assert_int_eq(compare_int_arrays(a, b, a_n), ARRAY_EQUAL);
}
END_TEST

// Тест для упорядоченного массива
START_TEST(test_array_sorted_asc)
{
    int a[] = {-4, -3, 0, 2, 5};
    int b[] = {-4, -3, 0, 2, 5};
    size_t a_n = sizeof(a) / sizeof(a[0]);
    
    ck_assert_int_eq(sizeof(a), sizeof(b));

    mysort(a, a_n, sizeof(int), int_cmp);

    ck_assert_int_eq(compare_int_arrays(a, b, a_n), ARRAY_EQUAL);
}
END_TEST

// Тест для массива, который отсортирован по убыванию
START_TEST(test_array_sorted_desc)
{
    int a[] = {100, 99, 98, 0, -100, -200, -10000, -98989892};
    int b[] = {-98989892, -10000, -200, -100, 0, 98, 99, 100};
    size_t a_n = sizeof(a) / sizeof(a[0]);
    
    ck_assert_int_eq(sizeof(a), sizeof(b));

    mysort(a, a_n, sizeof(int), int_cmp);

    ck_assert_int_eq(compare_int_arrays(a, b, a_n), ARRAY_EQUAL);
}
END_TEST

// Тест для массива, в котором элементы повторяются
START_TEST(test_array_double)
{
    int a[] = {100, -100, 55, 45, 0, 0};
    int b[] = {-100, 0, 0, 45, 55, 100};
    size_t a_n = sizeof(a) / sizeof(a[0]);
    
    ck_assert_int_eq(sizeof(a), sizeof(b));

    mysort(a, a_n, sizeof(int), int_cmp);

    ck_assert_int_eq(compare_int_arrays(a, b, a_n), ARRAY_EQUAL);
}
END_TEST

// Тест для массива, который состоит только из отрицательных элементов
START_TEST(test_array_negative)
{
    int a[] = {-1, -99, -2, -34};
    int b[] = {-99, -34, -2, -1};
    size_t a_n = sizeof(a) / sizeof(a[0]);
    
    ck_assert_int_eq(sizeof(a), sizeof(b));

    mysort(a, a_n, sizeof(int), int_cmp);

    ck_assert_int_eq(compare_int_arrays(a, b, a_n), ARRAY_EQUAL);
}
END_TEST

// Тест для массива, который состоит только из нулей
START_TEST(test_zero_array)
{
    int a[] = {0, 0, 0, 0};
    int b[] = {0, 0, 0, 0};
    size_t a_n = sizeof(a) / sizeof(a[0]);
    
    ck_assert_int_eq(sizeof(a), sizeof(b));

    mysort(a, a_n, sizeof(int), int_cmp);

    ck_assert_int_eq(compare_int_arrays(a, b, a_n), ARRAY_EQUAL);
}
END_TEST

// Тест для массива, который состоит из чпт
START_TEST(test_double_array)
{
    double a[] = {0.1, 0.3, 0.212, 0.2, -0.28};
    double b[] = {-0.28, 0.1, 0.2, 0.212, 0.3};
    size_t a_n = sizeof(a) / sizeof(a[0]);
    
    ck_assert_int_eq(sizeof(a), sizeof(b));

    mysort(a, a_n, sizeof(double), double_cmp);

    ck_assert_int_eq(compare_double_arrays(a, b, a_n), ARRAY_EQUAL);
}
END_TEST

START_TEST(test_char_array)
{
    char a[] = {'b', 'z', 'x', 'a'};
    char b[] = {'a', 'b', 'x', 'z'};
    size_t a_n = sizeof(a) / sizeof(a[0]);
    
    ck_assert_int_eq(sizeof(a), sizeof(b));

    mysort(a, a_n, sizeof(char), char_cmp);

    ck_assert_int_eq(compare_char_array(a, b, a_n), ARRAY_EQUAL);
}
END_TEST

Suite* test_sort(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("test_sort");
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_empty_array);
    tcase_add_test(tc_pos, test_array_length_one);
    tcase_add_test(tc_pos, test_array_length_two_not_sorted);
    tcase_add_test(tc_pos, test_array_length_two_sorted);
    tcase_add_test(tc_pos, test_array_sorted_asc);
    tcase_add_test(tc_pos, test_array_sorted_desc);
    tcase_add_test(tc_pos, test_array_double);
    tcase_add_test(tc_pos, test_array_negative);
    tcase_add_test(tc_pos, test_zero_array);
    tcase_add_test(tc_pos, test_char_array);
    tcase_add_test(tc_pos, test_double_array);

    suite_add_tcase(s, tc_pos);

    return s;
}
