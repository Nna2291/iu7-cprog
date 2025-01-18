#include <check.h>
#include "errors.h"
#include "mtr_slau.h"
#include "mtr_alloc.h"
#include "compare.h"
#include "constants.h"
#include "check_solve.h"


// Тест для слау с 1 неизвестно
START_TEST(test_solve_one)
{
    size_t n1 = 1, m1 = 2, n2 = 1, m2 = 1, n_ans = 1, m_ans = 1;
    double** mtr1 = matrix_alloc(n1, m1);
    double** mtr_ans = matrix_alloc(n_ans, m_ans);
    mtr1[0][0] = 10;
    mtr1[0][1] = 50;

    mtr_ans[0][0] = 5;

    double **mtr2 = matrix_alloc(n2, m2);

    int rc = gauss_solve(mtr1, mtr2, n1, m1);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(compare_matrix((const double**) mtr2, n2, m2, (const double**) mtr_ans, n_ans, m_ans), MATRIX_EQUALS);

    matrix_free(mtr1, n1);
    matrix_free(mtr2, n2);
    matrix_free(mtr_ans, n_ans);
}
END_TEST

// Тест для слау с несколькими неизвестными
START_TEST(test_solve_multi)
{
    size_t n1 = 2, m1 = 3, n2 = 2, m2 = 1, n_ans = 2, m_ans = 1;
    double** mtr1 = matrix_alloc(n1, m1);
    double** mtr_ans = matrix_alloc(n_ans, m_ans);

    mtr1[0][0] = 2;
    mtr1[0][1] = 5;
    mtr1[0][2] = 4;
    mtr1[1][0] = 1;
    mtr1[1][1] = 2;
    mtr1[1][2] = 3;

    mtr_ans[0][0] = 7;
    mtr_ans[1][0] = -2;

    double **mtr2 = matrix_alloc(n2, m2);

    int rc = gauss_solve(mtr1, mtr2, n1, m1);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(compare_matrix((const double**) mtr2, n2, m2, (const double**) mtr_ans, n_ans, m_ans), MATRIX_EQUALS);

    matrix_free(mtr1, n1);
    matrix_free(mtr2, n2);
    matrix_free(mtr_ans, n_ans);
}
END_TEST

START_TEST(null_matrix)
{
    int rc = gauss_solve(NULL, NULL, 10, 20);
    ck_assert_int_eq(rc, ERR_EMPTY);
}

START_TEST(invalid_size_matrix)
{
    size_t n1 = 2, m1 = 4, n2 = 2, m2 = 1;
    double** mtr1 = matrix_alloc(n1, m1);

    mtr1[0][0] = 2;
    mtr1[0][1] = 5;
    mtr1[0][2] = 4;
    mtr1[0][3] = 4;
    mtr1[1][0] = 1;
    mtr1[1][1] = 2;
    mtr1[1][2] = 3;
    mtr1[1][3] = 3;

    double **mtr2 = matrix_alloc(n2, m2);
    int rc = gauss_solve(mtr1, mtr2, n1, m1);
    ck_assert_int_eq(rc, ERR_SOLUTION);
    matrix_free(mtr1, n1);
    matrix_free(mtr2, n2);
}

Suite* test_solve(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;
    s = suite_create("test_solve");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, test_solve_one);
    tcase_add_test(tc_pos, test_solve_multi);

    tcase_add_test(tc_neg, null_matrix);
    tcase_add_test(tc_neg, invalid_size_matrix);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
