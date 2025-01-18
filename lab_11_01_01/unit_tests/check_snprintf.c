#include <stdio.h>
#include <stdlib.h>
#include "check_snprintf.h"
#include "my_realization.h"

// Тест с обоими спецификаторами
START_TEST(test_snprintf_normal)
{
    int size = 33;
    char *buffer = malloc(size);
    char *buffer1 = malloc(size);

    int buf = snprintf(buffer, size, "%s %o", "string", 123);
    int buf1 = my_snprintf(buffer1, size, "%s %o", "string", 123);

    ck_assert_str_eq(buffer, buffer1);
    ck_assert_int_eq(buf, buf1);

    free(buffer);
    free(buffer1);
}
END_TEST

// Тест с маленьким буффером
START_TEST(test_snprintf_short_buf)
{
    int size = 1;
    char *buffer = malloc(size);
    char *buffer1 = malloc(size);

    int buf = snprintf(buffer, size, "%s %o", "string", 123);
    int buf1 = my_snprintf(buffer1, size, "%s %o", "string", 123);

    ck_assert_str_eq(buffer, buffer1);
    ck_assert_int_eq(buf, buf1);

    free(buffer);
    free(buffer1);
}
END_TEST

// Тест с большим буффером
START_TEST(test_snprintf_long_buf)
{
    int size = 1000;
    char *buffer = malloc(size);
    char *buffer1 = malloc(size);

    int buf = snprintf(buffer, size, "%s %o", "string", 123);
    int buf1 = my_snprintf(buffer1, size, "%s %o", "string", 123);

    ck_assert_str_eq(buffer, buffer1);
    ck_assert_int_eq(buf, buf1);

    free(buffer);
    free(buffer1);
}
END_TEST

// Тест с пустым буффером
START_TEST(test_snprintf_zero_buf)
{
    size_t size = 0;
    char *buffer = "";
    char *buffer1 = "";

    // int buf = snprintf(buffer, size, "%s %o", "string", 123);
    int buf = snprintf(buffer, size, "%s %o", "string", 123);
    int buf1 = my_snprintf(buffer1, size, "%s %o", "string", 123);

    ck_assert_str_eq(buffer, buffer1);
    ck_assert_int_eq(buf, buf1);
}
END_TEST

// Тест с числом = 0
START_TEST(test_snprintf_zero_num)
{
    int size = 33;
    char *buffer = malloc(size);
    char *buffer1 = malloc(size);

    int buf = snprintf(buffer, size, "%s %o", "string", 0);
    int buf1 = my_snprintf(buffer1, size, "%s %o", "string", 0);

    ck_assert_str_eq(buffer, buffer1);
    ck_assert_int_eq(buf, buf1);

    free(buffer);
    free(buffer1);
}
END_TEST

// Тест с пустой строкой
// START_TEST(test_snprintf_null_string)
// {
//     int size = 33;
//     char *buffer = malloc(size);
//     char *buffer1 = malloc(size);

//     char *str = NULL;

//     int buf = snprintf(buffer, size, "%s", str);
//     int buf1 = my_snprintf(buffer1, size, "%s", str);

//     ck_assert_str_eq(buffer, buffer1);
//     ck_assert_int_eq(buf, buf1);

//     free(buffer);
//     free(buffer1);
// }
// END_TEST

Suite *test_snprintf(void)
{
    Suite *s = suite_create("test_snprintf");
    TCase *tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_snprintf_normal);
    tcase_add_test(tc_pos, test_snprintf_short_buf);
    tcase_add_test(tc_pos, test_snprintf_long_buf);
    tcase_add_test(tc_pos, test_snprintf_zero_buf);
    tcase_add_test(tc_pos, test_snprintf_zero_num);
    // tcase_add_test(tc_pos, test_snprintf_null_string);

    suite_add_tcase(s, tc_pos);

    return s;
}