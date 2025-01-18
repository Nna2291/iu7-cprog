#include <stdlib.h>
#include <check.h>
#include "check_read.h"
#include "check_pop.h"
#include "check_append.h"
#include "check_find.h"
#include "check_sort.h"

int main(void)
{
    int no_failed = 0;
    Suite *s_read, *s_pop, *s_sort, *s_find, *s_append;
    SRunner *runner;

    s_read = test_read();
    s_pop = test_pop();
    s_sort = test_sort();
    s_find = test_find();
    s_append = test_append();

    runner = srunner_create(s_read);
    srunner_add_suite(runner, s_pop);
    srunner_add_suite(runner, s_sort);
    srunner_add_suite(runner, s_find);
    srunner_add_suite(runner, s_append);
    
    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
