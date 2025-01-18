#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "check_pop.h"
#include "dino.h"
#include "errors.h"
#include "list.h"
#include "node.h"
#include "utils.h"

#define EPSILON 1e-9
#define EQUAL   1

static int are_items_eq(dino_t *itm1, dino_t *itm2)
{
    if (strcmp(itm1->name, itm2->name) != 0)
    {
        return 0;
    }
    if (compare_double(itm1->weight, itm2->weight, EPSILON) != 0)
    {
        return 0;
    }
    if (compare_double(itm1->height, itm2->height, EPSILON) != 0)
    {
        return 0;
    }
    return 1;
}

// Получаем элемент из массива из одного динозавра
START_TEST(pop_from_one_item)
{
    char* filename = "unit_tests/data/unit_read_pos_01.txt";
    dino_t correct_item = { "trex", 10.0, 20.0 };

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_OK);
    dino_t *item = pop_front(&head);
    ck_assert_ptr_nonnull(item);
    ck_assert_int_eq(are_items_eq(item, &correct_item), EQUAL);
    list_free(head);

    dino_free_content(item);
    free(item);
}

// Получаем элемент из массива из нескольких динозавров
START_TEST(pop_from_multi_item)
{
    char* filename = "unit_tests/data/unit_read_pos_02.txt";
    dino_t correct_item = { "trex", 10.1, 20.0 };

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_OK);
    dino_t *item = pop_front(&head);
    ck_assert_ptr_nonnull(item);
    ck_assert_int_eq(are_items_eq(item, &correct_item), EQUAL);
    list_free(head);
    dino_free_content(item);
    free(item);
}

// Указатель на NULL
START_TEST(point_to_null)
{
    node_t *head = NULL;
    dino_t *item = pop_front(&head);
    ck_assert_ptr_null(item);
    list_free(head);
    dino_free_content(item);
    free(item);
}

// Указатель - NULL
START_TEST(point_null)
{
    dino_t *item = pop_front(NULL);
    ck_assert_ptr_null(item);
}

Suite* test_pop(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;
    s = suite_create("test_pop");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, pop_from_one_item);
    tcase_add_test(tc_pos, pop_from_multi_item);

    tcase_add_test(tc_neg, point_to_null);
    tcase_add_test(tc_neg, point_null);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
