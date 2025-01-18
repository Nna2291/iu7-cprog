#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "check_read.h"
#include "dino.h"
#include "errors.h"
#include "list.h"
#include "node.h"
#include "utils.h"

#define EPSILON 1e-9
#define EQUAL   1

static size_t count_list_len(node_t *head)
{
    size_t len = 0;

    while (head)
    {
        len++;
        head = head->next;
    }
    return len;
}

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


static int are_list_and_array_eq(dino_t *dnio_array, node_t *head)
{
    size_t i = 0;

    while (head)
    {
        if (!are_items_eq(head->data, &dnio_array[i]))
        {
            return 0;
        }
        head = head->next;
        i++;
    }
    return 1;
}

// Массив из одного динозавра
START_TEST(read_one_item)
{
    int size = 1;
    char* filename = "unit_tests/data/unit_read_pos_01.txt";
    dino_t arr_correct[] = {{ "trex", 10.0, 20.0 }};

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(size, count_list_len(head));
    ck_assert_int_eq(are_list_and_array_eq(arr_correct, head), EQUAL);
    list_free(head);
}

// Массив из одного динозавра
START_TEST(read_multi_items)
{
    int size = 5;
    char* filename = "unit_tests/data/unit_read_pos_02.txt";
    dino_t arr_correct[] = {{ "trex", 10.1, 20.0 }, { "trex1", 5.2, 30.0 }, 
    { "trex2", 10.0, 20.2 }, { "trex3", 10.0, 20.4 },
    { "trex4", 10.6, 20.0 }};

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_OK);
    ck_assert_int_eq(size, count_list_len(head));
    ck_assert_int_eq(are_list_and_array_eq(arr_correct, head), EQUAL);
    list_free(head);
}

// Массив со строками вместо массы (ошибка в начале файла)
START_TEST(read_neg_items_begin)
{
    char* filename = "unit_tests/data/unit_read_neg_01.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_DATA);
    list_free(head);
}

// Массив со строками вместо массы (ошибка в середине файла)
START_TEST(read_neg_items_mid)
{
    char* filename = "unit_tests/data/unit_read_neg_02.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_DATA);
    list_free(head);
}

// Массив со строками вместо массы (ошибка в конце файла)
START_TEST(read_neg_items_end)
{
    char* filename = "unit_tests/data/unit_read_neg_03.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_DATA);
    list_free(head);
}

// Массив с неверными числами вместо массы (ошибка в начале файла)
START_TEST(read_neg_items_begin_weight)
{
    char* filename = "unit_tests/data/unit_read_neg_04.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_DATA);
    list_free(head);
}

// Массив с неверными числами вместо массы (ошибка в середине файла)
START_TEST(read_neg_items_mid_weight)
{
    char* filename = "unit_tests/data/unit_read_neg_05.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_DATA);
    list_free(head);
}

// Массив с неверными числами вместо массы (ошибка в конце файла)
START_TEST(read_neg_items_end_weight)
{
    char* filename = "unit_tests/data/unit_read_neg_06.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_DATA);
    list_free(head);
}

// Массив с неверными числами вместо массы (ошибка в начале файла)
START_TEST(read_neg_items_begin_height)
{
    char* filename = "unit_tests/data/unit_read_neg_07.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_DATA);
    list_free(head);
}

// Массив с неверными числами вместо массы (ошибка в середине файла)
START_TEST(read_neg_items_mid_height)
{
    char* filename = "unit_tests/data/unit_read_neg_08.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_DATA);
    list_free(head);
}

// Массив с неверными числами вместо массы (ошибка в конце файла)
START_TEST(read_neg_items_end_height)
{
    char* filename = "unit_tests/data/unit_read_neg_09.txt";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_DATA);
    list_free(head);
}

// Несуществующий файл
START_TEST(no_file)
{
    char* filename = "unit_tests/data/hfruo";

    node_t *head = NULL;
    int rc = list_read(filename, &head);
    ck_assert_int_eq(rc, ERR_IO);
    list_free(head);
}

Suite* test_read(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;
    s = suite_create("test_read");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_pos, read_one_item);
    tcase_add_test(tc_pos, read_multi_items);

    tcase_add_test(tc_neg, read_neg_items_begin);
    tcase_add_test(tc_neg, read_neg_items_mid);
    tcase_add_test(tc_neg, read_neg_items_end);

    tcase_add_test(tc_neg, read_neg_items_begin_weight);
    tcase_add_test(tc_neg, read_neg_items_mid_weight);
    tcase_add_test(tc_neg, read_neg_items_end_weight);

    tcase_add_test(tc_neg, read_neg_items_begin_height);
    tcase_add_test(tc_neg, read_neg_items_mid_height);
    tcase_add_test(tc_neg, read_neg_items_end_height);

    tcase_add_test(tc_neg, no_file);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
