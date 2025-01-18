#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "check_append.h"
#include "dino.h"
#include "errors.h"
#include "list.h"
#include "node.h"
#include "utils.h"

#define EPSILON 1e-9

// Соединение двух пустых списков
START_TEST(append_two_empty_lists)
{
    char *file_a = "unit_tests/data/append_empty_list_a.txt";
    char *file_b = "unit_tests/data/append_empty_list_b.txt";

    node_t *head_a = NULL, *head_b = NULL;
    int rc_a = list_read(file_a, &head_a);
    int rc_b = list_read(file_b, &head_b);
    ck_assert_int_eq(rc_a, ERR_DATA);
    ck_assert_int_eq(rc_b, ERR_DATA);

    append(&head_a, &head_b);

    ck_assert_ptr_null(head_a);
    ck_assert_ptr_null(head_b);

    list_free(head_a);
    list_free(head_b);
}

// Соединение пустого списка с непустым
START_TEST(append_empty_with_non_empty)
{
    char *file_a = "unit_tests/data/append_empty_list_a.txt";
    char *file_b = "unit_tests/data/append_non_empty_list_b.txt";

    node_t *head_a = NULL, *head_b = NULL;
    int rc_a = list_read(file_a, &head_a);
    int rc_b = list_read(file_b, &head_b);
    ck_assert_int_eq(rc_a, ERR_DATA);
    ck_assert_int_eq(rc_b, ERR_OK);

    append(&head_a, &head_b);

    ck_assert_ptr_nonnull(head_a);
    ck_assert_ptr_null(head_b);

    dino_t *dino = (dino_t *)head_a->data;
    ck_assert_str_eq(dino->name, "raptor");
    ck_assert_double_eq(dino->weight, 5.0);
    ck_assert_double_eq(dino->height, 15.0);

    list_free(head_a);
    list_free(head_b);
}

// Соединение двух непустых списков
START_TEST(append_two_non_empty_lists)
{
    char *file_a = "unit_tests/data/append_non_empty_list_a.txt";
    char *file_b = "unit_tests/data/append_non_empty_list_b.txt";

    node_t *head_a = NULL, *head_b = NULL;
    int rc_a = list_read(file_a, &head_a);
    int rc_b = list_read(file_b, &head_b);
    ck_assert_int_eq(rc_a, ERR_OK);
    ck_assert_int_eq(rc_b, ERR_OK);

    append(&head_a, &head_b);

    ck_assert_ptr_nonnull(head_a);
    ck_assert_ptr_null(head_b);

    dino_t *dino = (dino_t *)head_a->data;
    ck_assert_str_eq(dino->name, "trex");
    dino = (dino_t *)head_a->next->data;
    ck_assert_str_eq(dino->name, "stego");
    dino = (dino_t *)head_a->next->next->data;
    ck_assert_str_eq(dino->name, "raptor");

    list_free(head_a);
    list_free(head_b);
}

Suite* test_append(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("test_append");

    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, append_two_empty_lists);

    tcase_add_test(tc_pos, append_empty_with_non_empty);
    tcase_add_test(tc_pos, append_two_non_empty_lists);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}