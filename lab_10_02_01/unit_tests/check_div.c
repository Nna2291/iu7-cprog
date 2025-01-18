#include <check.h>

#include "errors.h"
#include "list.h"
#include "calculate.h"
#include "check_div.h"

// Неверный указатель исходного списка
START_TEST(test_null_head)
{
    node_t *head_odd = NULL, *head_even = NULL;
    int result = divide_poly(NULL, &head_odd, &head_even);
    ck_assert_int_eq(result, ERR_ARGS);
}
END_TEST

// Неверный указатель списка c нечетными
START_TEST(test_null_head_odd)
{
    node_t *head = create_node(2, 3);
    node_t *head_even = NULL;
    int result = divide_poly(head, NULL, &head_even);
    ck_assert_int_eq(result, ERR_ARGS);
    list_free(head);
}
END_TEST

// Неверный указатель списка c четными
START_TEST(test_null_head_even)
{
    node_t *head = create_node(2, 3);
    node_t *head_odd = NULL;
    int result = divide_poly(head, &head_odd, NULL);
    ck_assert_int_eq(result, ERR_ARGS);
    list_free(head);
}
END_TEST

// Тест с одним членом полинома
START_TEST(test_single_even_power)
{
    node_t *head = create_node(2, 3);
    node_t *head_odd = NULL, *head_even = NULL;

    int result = divide_poly(head, &head_odd, &head_even);
    ck_assert_int_eq(result, ERR_OK);

    ck_assert_ptr_null(head_odd);
    ck_assert_ptr_nonnull(head_even);
    ck_assert_int_eq(head_even->power, 2);
    ck_assert_int_eq(head_even->coefficient, 3);
    ck_assert_ptr_null(head_even->next);

    list_free(head);
    list_free(head_even);
}
END_TEST

// Тест с несколькими членами полинома
START_TEST(test_single_odd_power)
{
    node_t *head = create_node(3, 4);
    node_t *head_odd = NULL, *head_even = NULL;

    int result = divide_poly(head, &head_odd, &head_even);
    ck_assert_int_eq(result, ERR_OK);

    ck_assert_ptr_null(head_even);
    ck_assert_ptr_nonnull(head_odd);
    ck_assert_int_eq(head_odd->power, 3);
    ck_assert_int_eq(head_odd->coefficient, 4);
    ck_assert_ptr_null(head_odd->next);

    list_free(head);
    list_free(head_odd);
}
END_TEST

START_TEST(test_multiple_nodes)
{
    node_t *head = create_node(3, 4);
    list_add_to_end(&head, create_node(2, 3));
    list_add_to_end(&head, create_node(1, 2));
    list_add_to_end(&head, create_node(0, 1));

    node_t *head_odd = NULL, *head_even = NULL;

    int result = divide_poly(head, &head_odd, &head_even);
    ck_assert_int_eq(result, ERR_OK);

    ck_assert_ptr_nonnull(head_odd);
    ck_assert_int_eq(head_odd->power, 3);
    ck_assert_int_eq(head_odd->coefficient, 4);

    ck_assert_ptr_nonnull(head_odd->next);
    ck_assert_int_eq(head_odd->next->power, 1);
    ck_assert_int_eq(head_odd->next->coefficient, 2);

    ck_assert_ptr_null(head_odd->next->next);

    ck_assert_ptr_nonnull(head_even);
    ck_assert_int_eq(head_even->power, 2);
    ck_assert_int_eq(head_even->coefficient, 3);

    ck_assert_ptr_nonnull(head_even->next);
    ck_assert_int_eq(head_even->next->power, 0);
    ck_assert_int_eq(head_even->next->coefficient, 1);

    ck_assert_ptr_null(head_even->next->next);

    list_free(head);
    list_free(head_odd);
    list_free(head_even);
}
END_TEST

Suite* test_div(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("test_div");

    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_null_head);
    tcase_add_test(tc_neg, test_null_head_odd);
    tcase_add_test(tc_neg, test_null_head_even);

    tcase_add_test(tc_pos, test_single_even_power);
    tcase_add_test(tc_pos, test_single_odd_power);
    tcase_add_test(tc_pos, test_multiple_nodes);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
