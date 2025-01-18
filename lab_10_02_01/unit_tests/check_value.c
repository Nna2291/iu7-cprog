#include <check.h>
#include <math.h>

#include "check_value.h"
#include "errors.h"
#include "list.h"
#include "calculate.h"

// Неверный указатель на список
START_TEST(test_null_head)
{
    int val = 0;
    int result = calculate_val(NULL, 2, &val);
    ck_assert_int_eq(result, ERR_ARGS);
}
END_TEST

// Неверный указатель на значение
START_TEST(test_null_val_pointer)
{
    node_t *head = create_node(2, 3);
    int result = calculate_val(head, 2, NULL);
    ck_assert_int_eq(result, ERR_ARGS);
    list_free(head);
}
END_TEST

// Тест с одним членом полинома
START_TEST(test_single_node)
{
    node_t *head = create_node(3, 4);
    int val = 0;

    int result = calculate_val(head, 2, &val);
    ck_assert_int_eq(result, ERR_OK);
    ck_assert_int_eq(val, 4 * pow(2, 3));

    list_free(head);
}
END_TEST

// Тест с несколькими членами полинома (положительное значение)
START_TEST(test_multiple_nodes_pos)
{
    node_t *head = create_node(2, 3);
    list_add_to_end(&head, create_node(1, 2));
    list_add_to_end(&head, create_node(0, 1));

    int val = 0;
    int a = 2;

    int result = calculate_val(head, a, &val);
    ck_assert_int_eq(result, ERR_OK);
    ck_assert_int_eq(val, 3 * pow(a, 2) + 2 * pow(a, 1) + 1);

    list_free(head);
}
END_TEST

// Тест с несколькими членами полинома (отрицательное значение)
START_TEST(test_multiple_nodes_neg)
{
    node_t *head = create_node(2, 3);
    list_add_to_end(&head, create_node(1, 2));
    list_add_to_end(&head, create_node(0, 1));

    int val = 0;
    int a = -12743;

    int result = calculate_val(head, a, &val);
    ck_assert_int_eq(result, ERR_OK);
    ck_assert_int_eq(val, 3 * pow(a, 2) + 2 * pow(a, 1) + 1);

    list_free(head);
}
END_TEST

// Тест с несколькими членами полинома (отрицательное значение)
START_TEST(test_multiple_nodes_zero)
{
    node_t *head = create_node(2, 3);
    list_add_to_end(&head, create_node(1, 2));
    list_add_to_end(&head, create_node(0, 1));

    int val = 0;
    int a = 0;

    int result = calculate_val(head, a, &val);
    ck_assert_int_eq(result, ERR_OK);
    ck_assert_int_eq(val, 3 * pow(a, 2) + 2 * pow(a, 1) + 1);

    list_free(head);
}
END_TEST

Suite* test_value(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("test_val");

    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_null_head);
    tcase_add_test(tc_neg, test_null_val_pointer);

    tcase_add_test(tc_pos, test_single_node);
    tcase_add_test(tc_pos, test_multiple_nodes_zero);
    tcase_add_test(tc_pos, test_multiple_nodes_neg);
    tcase_add_test(tc_pos, test_multiple_nodes_pos);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
