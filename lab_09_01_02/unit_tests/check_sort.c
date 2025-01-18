#include <check.h>
#include <stdbool.h>
#include "item_array.h"
#include "check_sort.h"

// Массив из одной вещи
START_TEST(test_sort_one)
{
    item_t arr[1] = {{ "item1", 0.0, 0.0, 0.0 }};
    item_t arr_correct[1] = {{ "item1", 0.0, 0.0, 0.0 }};

    sort_array(arr, sizeof(arr) / sizeof(arr[0]));

    ck_assert_mem_eq(arr, arr_correct, sizeof(arr_correct));
}

// Отсортированый массив из нескольких вещей
START_TEST(test_sort_sorted)
{
    item_t arr[3] = {{ "item1", 0.0, 0.0, 0.0}, { "item2", 1.0, 2.0, 0.5}, { "item3", 10.0, 2.0, 5.0 }};
    item_t arr_correct[3] = {{ "item1", 0.0, 0.0, 0.0}, { "item2", 1.0, 2.0, 0.5}, { "item3", 10.0, 2.0, 5.0 }};

    sort_array(arr, sizeof(arr) / sizeof(arr[0]));

    ck_assert_mem_eq(arr, arr_correct, sizeof(arr_correct));
}

// Неотсортированный массив из нескольких вещей
START_TEST(test_sort_unsorted)
{
    item_t arr[3] = {{ "item3", 10.0, 2.0, 5.0 }, { "item1", 0.0, 0.0, 0.0 }, { "item2", 1.0, 2.0, 0.5 }};
    item_t arr_correct[3] = {{ "item1", 0.0, 0.0, 0.0 }, { "item2", 1.0, 2.0, 0.5 }, { "item3", 10.0, 2.0, 5.0 }};

    sort_array(arr, sizeof(arr) / sizeof(arr[0]));

    ck_assert_mem_eq(arr, arr_correct, sizeof(arr_correct));
}

Suite* test_sort(void)
{
    Suite *s;
    TCase *tc_pos;
    s = suite_create("test_sort");
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_sort_one);
    tcase_add_test(tc_pos, test_sort_sorted);
    tcase_add_test(tc_pos, test_sort_unsorted);

    suite_add_tcase(s, tc_pos);

    return s;
}
