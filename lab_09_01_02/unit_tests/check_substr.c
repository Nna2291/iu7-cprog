#include <check.h>
#include <stdbool.h>
#include "item.h"
#include "check_substr.h"

// Поиск подстроки в строке
START_TEST(test_substr_not_full)
{
    const item_t item = { "item1", 0.0, 0.0, 0.0 };

    bool ans = item_substr(&item, "it");

    ck_assert_int_eq(ans, true);
}

// Поиск подстроки, которая полностью равна строке
START_TEST(test_substr_full)
{
    const item_t item = { "item1", 0.0, 0.0, 0.0 };

    bool ans = item_substr(&item, "item1");

    ck_assert_int_eq(ans, true);
}

// Поиск подстроки, которая больше чем строка
START_TEST(test_substr_no)
{
    const item_t item = { "item1", 0.0, 0.0, 0.0 };

    bool ans = item_substr(&item, "item12");

    ck_assert_int_eq(ans, false);
}

// Поиск пустой строки
START_TEST(test_substr_empty)
{
    const item_t item = { "item1", 0.0, 0.0, 0.0 };

    bool ans = item_substr(&item, "");

    ck_assert_int_eq(ans, true);
}

Suite* test_substr(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("test_substr");
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_substr_not_full);
    tcase_add_test(tc_pos, test_substr_full);
    tcase_add_test(tc_pos, test_substr_no);
    tcase_add_test(tc_pos, test_substr_empty);

    suite_add_tcase(s, tc_pos);

    return s;
}
