#include <check.h>
#include "errors.h"
#include "mtr_op.h"
#include "mtr_alloc.h"
#include "check_sum.h"
#include "compare.h"
#include "constants.h"


// Тест для матриц 1 на 1
START_TEST(test_sum_one)
{
    size_t n1 = 1, m1 = 1, n2 = 1, m2 = 1, n3, m3, n_ans = 1, m_ans = 1;
    double **mtr1 = matrix_alloc(n1, m1);
    double **mtr2 = matrix_alloc(n2, m2);
    double **mtr_ans = matrix_alloc(n_ans, m_ans);
    double **mtr3 = NULL;
    mtr1[0][0] = 10.1;
    mtr2[0][0] = -10.1;

    mtr_ans[0][0] = 0;

    int rc = sum_matrix((const double**) mtr1, n1, m1, (const double**) mtr2, n2, m2, &mtr3, &n3, &m3);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(compare_matrix((const double**) mtr3, n3, m3, (const double**) mtr_ans, n_ans, m_ans), MATRIX_EQUALS);

    matrix_free(mtr1, n1);
    matrix_free(mtr2, n2);
    matrix_free(mtr3, n3);
    matrix_free(mtr_ans, n_ans);
}
END_TEST

// Тест для прямоугольной матрицы
START_TEST(test_sum_not_one)
{
    size_t n1 = 1, m1 = 3, n2 = 1, m2 = 3, n3, m3, n_ans = 1, m_ans = 3;

    double **mtr1 = matrix_alloc(n1, m1);
    double **mtr2 = matrix_alloc(n2, m2);
    double **mtr_ans = matrix_alloc(n_ans, m_ans);
    double **mtr3 = NULL;
    mtr1[0][0] = 1;
    mtr1[0][1] = -1;
    mtr1[0][2] = 10;

    mtr2[0][0] = -1;
    mtr2[0][1] = 1;
    mtr2[0][2] = -10;

    mtr_ans[0][0] = 0;
    mtr_ans[0][1] = 0;
    mtr_ans[0][2] = 0;

    int rc = sum_matrix((const double**) mtr1, n1, m1, (const double**) mtr2, n2, m2, &mtr3, &n3, &m3);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(compare_matrix((const double**) mtr3, n3, m3, (const double**) mtr_ans, n_ans, m_ans), MATRIX_EQUALS);
    matrix_free(mtr1, n1);
    matrix_free(mtr2, n2);
    matrix_free(mtr3, n3);
    matrix_free(mtr_ans, n_ans);
}
END_TEST

// Неправильные размеры матриц
START_TEST(wrong_sizes)
{
    size_t n1 = 1, m1 = 3, n2 = 1, m2 = 4, n3, m3;

    double **mtr1 = matrix_alloc(n1, m1);
    double **mtr2 = matrix_alloc(n2, m2);
    double **mtr3 = NULL;
    mtr1[0][0] = 1;
    mtr1[0][1] = -1;
    mtr1[0][2] = 10;

    mtr2[0][0] = -1;
    mtr2[0][1] = 1;
    mtr2[0][2] = -10;
    mtr2[0][3] = -110;

    int rc = sum_matrix((const double**) mtr1, n1, m1, (const double**) mtr2, n2, m2, &mtr3, &n3, &m3);

    ck_assert_int_eq(rc, ERR_MTR_SIZE);

    matrix_free(mtr1, n1);
    matrix_free(mtr2, n2);
    matrix_free(mtr3, n3);
}

// Пустые матрицы
START_TEST(invalid_size_matrix)
{
    size_t n1 = 1, m1 = 3, n2 = 1, m2 = 3, n3, m3;

    double **mtr1 = NULL, **mtr2 = NULL, **mtr3 = NULL;

    int rc = sum_matrix((const double**) mtr1, n1, m1, (const double**) mtr2, n2, m2, &mtr3, &n3, &m3);

    ck_assert_int_eq(rc, ERR_EMPTY);

    matrix_free(mtr1, n1);
    matrix_free(mtr2, n2);
    matrix_free(mtr3, n3);
}

Suite* test_sum(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("test_sum");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, test_sum_one);
    tcase_add_test(tc_pos, test_sum_not_one);

    tcase_add_test(tc_neg, wrong_sizes);
    tcase_add_test(tc_neg, invalid_size_matrix);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
