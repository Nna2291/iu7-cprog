#include <check.h>
#include "errors.h"
#include "mtr_op.h"
#include "mtr_alloc.h"
#include "check_multi.h"
#include "compare.h"
#include "constants.h"


// Тест для матрицы
START_TEST(test_multi_one)
{
    size_t n1 = 1, m1 = 1, n2 = 1, m2 = 1, n3, m3, n_ans = 1, m_ans = 1;
    double** mtr1 = matrix_alloc(n1, m1);
    double **mtr2 = matrix_alloc(n2, m2);
    double **mtr_ans = matrix_alloc(n_ans, m_ans);
    double **mtr3 = NULL;
    mtr1[0][0] = 2;
    mtr2[0][0] = 22;

    mtr_ans[0][0] = 44;

    int rc = multiply_matrix((const double**) mtr1, n1, m1, (const double**) mtr2, n2, m2, &mtr3, &n3, &m3);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(compare_matrix((const double**) mtr3, n3, m3, (const double**) mtr_ans, n_ans, m_ans), MATRIX_EQUALS);

    matrix_free(mtr1, n1);
    matrix_free(mtr2, n2);
    matrix_free(mtr3, n3);
    matrix_free(mtr_ans, n_ans);
}
END_TEST

// Тест для матрицы
START_TEST(test_multi_n_1_1_m)
{
    size_t n1 = 5, m1 = 1, n2 = 1, m2 = 6, n3, m3, n_ans = 5, m_ans = 6;
    double** mtr1 = matrix_alloc(n1, m1);
    double **mtr2 = matrix_alloc(n2, m2);
    double **mtr_ans = matrix_alloc(n_ans, m_ans);
    double **mtr3 = NULL;
    mtr1[0][0] = 1;
    mtr1[1][0] = 2;
    mtr1[2][0] = 3;
    mtr1[3][0] = 4;
    mtr1[4][0] = 5;

    mtr2[0][0] = 1;
    mtr2[0][1] = 2;
    mtr2[0][2] = 3;
    mtr2[0][3] = 4;
    mtr2[0][4] = 5;
    mtr2[0][5] = 6;

    mtr_ans[0][0] = 1;
    mtr_ans[0][1] = 2;
    mtr_ans[0][2] = 3;
    mtr_ans[0][3] = 4;
    mtr_ans[0][4] = 5;
    mtr_ans[0][5] = 6;

    mtr_ans[1][0] = 2;
    mtr_ans[1][1] = 4;
    mtr_ans[1][2] = 6;
    mtr_ans[1][3] = 8;
    mtr_ans[1][4] = 10;
    mtr_ans[1][5] = 12;

    mtr_ans[2][0] = 3;
    mtr_ans[2][1] = 6;
    mtr_ans[2][2] = 9;
    mtr_ans[2][3] = 12;
    mtr_ans[2][4] = 15;
    mtr_ans[2][5] = 18;

    mtr_ans[3][0] = 4;
    mtr_ans[3][1] = 8;
    mtr_ans[3][2] = 12;
    mtr_ans[3][3] = 16;
    mtr_ans[3][4] = 20;
    mtr_ans[3][5] = 24;

    mtr_ans[4][0] = 5;
    mtr_ans[4][1] = 10;
    mtr_ans[4][2] = 15;
    mtr_ans[4][3] = 20;
    mtr_ans[4][4] = 25;
    mtr_ans[4][5] = 30;

    int rc = multiply_matrix((const double**) mtr1, n1, m1, (const double**) mtr2, n2, m2, &mtr3, &n3, &m3);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(compare_matrix((const double**) mtr3, n3, m3, (const double**) mtr_ans, n_ans, m_ans), MATRIX_EQUALS);

    matrix_free(mtr1, n1);
    matrix_free(mtr2, n2);
    matrix_free(mtr3, n3);
    matrix_free(mtr_ans, n_ans);
}
END_TEST

START_TEST(test_multi_1_n_n_1)
{
    size_t n1 = 1, m1 = 4, n2 = 4, m2 = 1, n3, m3, n_ans = 1, m_ans = 1;
    double** mtr1 = matrix_alloc(n1, m1);
    double **mtr2 = matrix_alloc(n2, m2);
    double **mtr_ans = matrix_alloc(n_ans, m_ans);
    double **mtr3 = NULL;
    mtr1[0][0] = 1;
    mtr1[0][1] = 2;
    mtr1[0][2] = 3;
    mtr1[0][3] = 4;

    mtr2[0][0] = 1;
    mtr2[1][0] = 2;
    mtr2[2][0] = 3;
    mtr2[3][0] = 4;

    mtr_ans[0][0] = 30;

    int rc = multiply_matrix((const double**) mtr1, n1, m1, (const double**) mtr2, n2, m2, &mtr3, &n3, &m3);

    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(compare_matrix((const double**) mtr3, n3, m3, (const double**) mtr_ans, n_ans, m_ans), MATRIX_EQUALS);

    matrix_free(mtr1, n1);
    matrix_free(mtr2, n2);
    matrix_free(mtr3, n3);
    matrix_free(mtr_ans, n_ans);
}
END_TEST

// Тест для прямоугольной матрицы
START_TEST(test_multi_not_one)
{
    size_t n1 = 2, m1 = 3, n2 = 3, m2 = 2, n3, m3, n_ans = 2, m_ans = 2;

    double **mtr1 = matrix_alloc(n1, m1);
    double **mtr2 = matrix_alloc(n2, m2);
    double **mtr_ans = matrix_alloc(n_ans, m_ans);
    double **mtr3 = NULL;
    mtr1[0][0] = 1;
    mtr1[0][1] = 2;
    mtr1[0][2] = 3;
    mtr1[1][0] = 4;
    mtr1[1][1] = 5;
    mtr1[1][2] = 6;

    mtr2[0][0] = -1;
    mtr2[0][1] = -2;
    mtr2[1][0] = -3;
    mtr2[1][1] = -4;
    mtr2[2][0] = -5;
    mtr2[2][1] = -6;

    mtr_ans[0][0] = -22;
    mtr_ans[0][1] = -28;
    mtr_ans[1][0] = -49;
    mtr_ans[1][1] = -64;

    int rc = multiply_matrix((const double**) mtr1, n1, m1, (const double**) mtr2, n2, m2, &mtr3, &n3, &m3);

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

    int rc = multiply_matrix((const double**) mtr1, n1, m1, (const double**) mtr2, n2, m2, &mtr3, &n3, &m3);

    ck_assert_int_eq(rc, ERR_MTR_SIZE);

    matrix_free(mtr1, n1);
    matrix_free(mtr2, n2);
    matrix_free(mtr3, n3);
}

// Пустые матрицы
START_TEST(invalid_size_matrix)
{
    size_t n1 = 1, m1 = 3, n2 = 3, m2 = 1, n3, m3;

    double **mtr1 = NULL, **mtr2 = NULL, **mtr3 = NULL;

    int rc = multiply_matrix((const double**) mtr1, n1, m1, (const double**) mtr2, n2, m2, &mtr3, &n3, &m3);

    ck_assert_int_eq(rc, ERR_EMPTY);

    matrix_free(mtr1, n1);
    matrix_free(mtr2, n2);
    matrix_free(mtr3, n3);
}

Suite* test_multi(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;
    s = suite_create("test_multi");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, test_multi_one);
    tcase_add_test(tc_pos, test_multi_not_one);
    tcase_add_test(tc_pos, test_multi_n_1_1_m);
    tcase_add_test(tc_pos, test_multi_1_n_n_1);

    tcase_add_test(tc_neg, wrong_sizes);
    tcase_add_test(tc_neg, invalid_size_matrix);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
