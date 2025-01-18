#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "check_derivative.h"
#include "errors.h"
#include "calculate.h"
#include "list.h"
#include "node.h"

// Неверный указатель исходного списка
START_TEST(test_null_head)
{
    node_t *new_head = NULL;
    int result = calculate_derivative(NULL, &new_head);
    ck_assert_int_eq(result, ERR_ARGS);
}
END_TEST

// Неверный указатель нового списка
START_TEST(test_null_new_head)
{
    node_t *head = create_node(2, 3);
    int result = calculate_derivative(head, NULL);
    ck_assert_int_eq(result, ERR_ARGS);
    list_free(head);
}
END_TEST

// Тест с несколькими членами полинома
START_TEST(test_multiple_nodes)
{
    node_t *head = create_node(3, 4);
    list_add_to_end(&head, create_node(2, 3));
    list_add_to_end(&head, create_node(1, 2));
    list_add_to_end(&head, create_node(0, 2));

    node_t *new_head = NULL;

    int result = calculate_derivative(head, &new_head);
    ck_assert_int_eq(result, ERR_OK);
    ck_assert_ptr_nonnull(new_head);

    ck_assert_int_eq(new_head->power, 2);
    ck_assert_int_eq(new_head->coefficient, 12);

    ck_assert_ptr_nonnull(new_head->next);
    ck_assert_int_eq(new_head->next->power, 1);
    ck_assert_int_eq(new_head->next->coefficient, 6);
    
    ck_assert_ptr_nonnull(new_head->next->next);
    ck_assert_int_eq(new_head->next->next->power, 0);
    ck_assert_int_eq(new_head->next->next->coefficient, 2);

    ck_assert_ptr_null(new_head->next->next->next);

    list_free(head);
    list_free(new_head);
}
END_TEST

// Тест с одним членом полинома
START_TEST(test_single_node)
{
    node_t *head = create_node(0, 4);
    node_t *new_head = NULL;

    int result = calculate_derivative(head, &new_head);
    ck_assert_int_eq(result, ERR_OK);

    ck_assert_ptr_null(new_head);
    list_free(head);
}
END_TEST

Suite* test_derivative(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("test_derivative");

    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_null_head);
    tcase_add_test(tc_neg, test_null_new_head);
    tcase_add_test(tc_pos, test_single_node);
    tcase_add_test(tc_pos, test_multiple_nodes);
    
    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
