#include <check.h>

#include "check_sum.h"
#include "errors.h"
#include "list.h"
#include "calculate.h"

// Неверный указатель исходного списка 1
START_TEST(test_null_head1)
{
    node_t *head2 = create_node(2, 3);
    node_t *head3 = NULL;
    int result = calculate_sum(NULL, head2, &head3);
    ck_assert_int_eq(result, ERR_ARGS);
    list_free(head2);
}
END_TEST

// Неверный указатель исходного списка 2
START_TEST(test_null_head2)
{
    node_t *head1 = create_node(2, 3);
    node_t *head3 = NULL;
    int result = calculate_sum(head1, NULL, &head3);
    ck_assert_int_eq(result, ERR_ARGS);
    list_free(head1);
}
END_TEST

// Неверный указатель выходного списка
START_TEST(test_null_head3)
{
    node_t *head1 = create_node(2, 3);
    node_t *head2 = create_node(1, 4);
    int result = calculate_sum(head1, head2, NULL);
    ck_assert_int_eq(result, ERR_ARGS);
    list_free(head1);
    list_free(head2);
}
END_TEST

// Тест с одинаковыми степенями
START_TEST(test_single_nodes)
{
    node_t *head1 = create_node(2, 3);
    node_t *head2 = create_node(2, 4);
    node_t *head3 = NULL;

    int result = calculate_sum(head1, head2, &head3);
    ck_assert_int_eq(result, ERR_OK);

    ck_assert_ptr_nonnull(head3);
    ck_assert_int_eq(head3->power, 2);
    ck_assert_int_eq(head3->coefficient, 7);
    ck_assert_ptr_null(head3->next);

    list_free(head1);
    list_free(head2);
    list_free(head3);
}
END_TEST

// Тест с разными степенями
START_TEST(test_different_powers)
{
    node_t *head1 = create_node(3, 5);
    list_add_to_end(&head1, create_node(1, 2));

    node_t *head2 = create_node(2, 3);
    list_add_to_end(&head2, create_node(0, 1));

    node_t *head3 = NULL;

    int result = calculate_sum(head1, head2, &head3);
    ck_assert_int_eq(result, ERR_OK);

    ck_assert_ptr_nonnull(head3);
    ck_assert_int_eq(head3->power, 3);
    ck_assert_int_eq(head3->coefficient, 5);
    ck_assert_int_eq(head3->next->power, 2);
    ck_assert_int_eq(head3->next->coefficient, 3);
    ck_assert_int_eq(head3->next->next->power, 1);
    ck_assert_int_eq(head3->next->next->coefficient, 2);
    ck_assert_int_eq(head3->next->next->next->power, 0);
    ck_assert_int_eq(head3->next->next->next->coefficient, 1);
    ck_assert_ptr_null(head3->next->next->next->next);

    list_free(head1);
    list_free(head2);
    list_free(head3);
}
END_TEST

// Объединенный случай
START_TEST(test_overlapping_powers)
{
    node_t *head1 = create_node(2, 3);
    list_add_to_end(&head1, create_node(1, 2));

    node_t *head2 = create_node(2, 4);
    list_add_to_end(&head2, create_node(0, 1));

    node_t *head3 = NULL;

    int result = calculate_sum(head1, head2, &head3);
    ck_assert_int_eq(result, ERR_OK);

    ck_assert_ptr_nonnull(head3);
    ck_assert_int_eq(head3->power, 2);
    ck_assert_int_eq(head3->coefficient, 7);
    ck_assert_int_eq(head3->next->power, 1);
    ck_assert_int_eq(head3->next->coefficient, 2);
    ck_assert_int_eq(head3->next->next->power, 0);
    ck_assert_int_eq(head3->next->next->coefficient, 1);
    ck_assert_ptr_null(head3->next->next->next);

    list_free(head1);
    list_free(head2);
    list_free(head3);
}
END_TEST

Suite* test_sum(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("test_sum");

    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_null_head1);
    tcase_add_test(tc_neg, test_null_head2);
    tcase_add_test(tc_neg, test_null_head3);
    tcase_add_test(tc_pos, test_single_nodes);
    tcase_add_test(tc_pos, test_different_powers);
    tcase_add_test(tc_pos, test_overlapping_powers);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
