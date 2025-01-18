#include <stdlib.h>
#include <check.h>

#include "check_insert.h"
#include "check_remove.h"
#include "check_find.h"
#include "check_min.h"
#include "check_max.h"
#include "check_each.h"
#include "check_clear.h"

int main(void)
{
    int no_failed = 0;
    Suite *s_insert, *s_remove, *s_find, *s_min, *s_max, *s_each, *s_clear;
    SRunner *runner;

    s_insert = test_insert();
    s_remove = test_remove();
    s_find = test_find();
    s_min = test_min();
    s_max = test_max();
    s_each = test_each();
    s_clear = test_clear();

    runner = srunner_create(s_insert);
    srunner_add_suite(runner, s_remove);
    srunner_add_suite(runner, s_find);
    srunner_add_suite(runner, s_min);
    srunner_add_suite(runner, s_max);
    srunner_add_suite(runner, s_each);
    srunner_add_suite(runner, s_clear);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
