#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "check_find.h"
#include "dino.h"
#include "errors.h"
#include "list.h"
#include "node.h"
#include "utils.h"

#define EPSILON 1e-9

static int compare_dino_by_name(const void *a, const void *b)
{
    const dino_t *d1 = (const dino_t *)a;
    const dino_t *d2 = (const dino_t *)b;
    return strcmp(d1->name, d2->name);
}

// Поиск в пустом списке
START_TEST(find_in_empty_list)
{
    char *filename = "unit_tests/data/find_in_empty_list.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_DATA);

    dino_t target = { "trex", 0, 0 };
    node_t *found = find(head, &target, compare_dino_by_name);

    ck_assert_ptr_null(found);

    list_free(head);
}

// Поиск элемента, который есть в списке
START_TEST(find_existing_element)
{
    char *filename = "unit_tests/data/find_existing_element.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_OK);

    dino_t target = { "raptor", 0, 0 };
    node_t *found = find(head, &target, compare_dino_by_name);

    ck_assert_ptr_nonnull(found);
    ck_assert_str_eq(((dino_t *)(found->data))->name, "raptor");

    list_free(head);
}

// Поиск элемента, которого нет в списке
START_TEST(find_non_existing_element)
{
    char *filename = "unit_tests/data/find_non_existing_element.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_OK);

    dino_t target = { "unknown", 0, 0 };
    node_t *found = find(head, &target, compare_dino_by_name);

    ck_assert_ptr_null(found);

    list_free(head);
}

// Поиск в списке с одним элементом
START_TEST(find_in_single_element_list)
{
    char *filename = "unit_tests/data/find_in_single_element_list.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_OK);

    dino_t target = { "trex", 0, 0 };
    node_t *found = find(head, &target, compare_dino_by_name);

    ck_assert_ptr_nonnull(found);
    ck_assert_str_eq(((dino_t *)(found->data))->name, "trex");

    list_free(head);
}

// Поиск элемента в начале списка
START_TEST(find_at_start)
{
    char *filename = "unit_tests/data/find_at_start.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_OK);

    dino_t target = { "raptor", 0, 0 };
    node_t *found = find(head, &target, compare_dino_by_name);

    ck_assert_ptr_nonnull(found);
    ck_assert_str_eq(((dino_t *)(found->data))->name, "raptor");

    list_free(head);
}

// Поиск элемента в конце списка
START_TEST(find_at_end)
{
    char *filename = "unit_tests/data/find_at_end.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_OK);

    dino_t target = { "trex", 0, 0 };
    node_t *found = find(head, &target, compare_dino_by_name);

    ck_assert_ptr_nonnull(found);
    ck_assert_str_eq(((dino_t *)(found->data))->name, "trex");

    list_free(head);
}

Suite* test_find(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("test_find");

    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, find_in_empty_list);
    tcase_add_test(tc_neg, find_non_existing_element);

    tcase_add_test(tc_pos, find_existing_element);
    tcase_add_test(tc_pos, find_in_single_element_list);
    tcase_add_test(tc_pos, find_at_start);
    tcase_add_test(tc_pos, find_at_end);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}