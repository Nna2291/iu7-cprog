#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "check_sort.h"
#include "dino.h"
#include "errors.h"
#include "list.h"
#include "node.h"
#include "utils.h"

#define EPSILON 1e-9
#define EQUAL   1

// Здесь сортировка проверяется по именам динозавров

static int compare_by_weight(const void *a, const void *b)
{
    const dino_t *d1 = (const dino_t *)a;
    const dino_t *d2 = (const dino_t *)b;
    return compare_double(d1->weight, d2->weight, EPSILON);
}

// Пустой список
START_TEST(sort_empty_list)
{
    char *filename = "unit_tests/data/unit_sort_empty_list.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_DATA);
    ck_assert_ptr_null(head);

    node_t *sorted = sort(head, compare_by_weight);
    ck_assert_ptr_null(sorted);
}

// Сортировка списка из одного элемента
START_TEST(sort_single_element)
{
    char *filename = "unit_tests/data/unit_sort_single_element.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_OK);

    node_t *sorted = sort(head, compare_by_weight);

    ck_assert_ptr_nonnull(sorted);
    ck_assert_str_eq(((dino_t *)(sorted->data))->name, "trex");
    ck_assert_ptr_null(sorted->next);

    list_free(sorted);
}

// Сортировка уже упорядоченного списка
START_TEST(sort_sorted_list)
{
    char *filename = "unit_tests/data/unit_sort_sorted_list.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_OK);

    node_t *sorted = sort(head, compare_by_weight);

    ck_assert_ptr_nonnull(sorted);
    ck_assert_str_eq(((dino_t *)(sorted->data))->name, "raptor");
    ck_assert_str_eq(((dino_t *)(sorted->next->data))->name, "trex");
    ck_assert_ptr_null(sorted->next->next);

    list_free(sorted);
}

// Сортировка неупорядоченного списка
START_TEST(sort_unsorted_list)
{
    char *filename = "unit_tests/data/unit_sort_unsorted_list.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_OK);

    node_t *sorted = sort(head, compare_by_weight);

    ck_assert_ptr_nonnull(sorted);
    ck_assert_str_eq(((dino_t *)(sorted->data))->name, "raptor");
    ck_assert_str_eq(((dino_t *)(sorted->next->data))->name, "trex");
    ck_assert_ptr_null(sorted->next->next);

    list_free(sorted);
}

Suite* test_sort(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("test_sort");

    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");
    
    tcase_add_test(tc_neg, sort_empty_list);
    tcase_add_test(tc_pos, sort_single_element);
    tcase_add_test(tc_pos, sort_sorted_list);
    tcase_add_test(tc_pos, sort_unsorted_list);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}