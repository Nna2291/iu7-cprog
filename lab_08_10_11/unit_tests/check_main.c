#include <stdlib.h>
#include <check.h>
#include "check_solve.h"
#include "check_sum.h"
#include "check_multi.h"

int main(void)
{
    int no_failed = 0;
    Suite *s_solve, *s_sum, *s_multi;
    SRunner *runner;

    // s_sort = test_sort();
    s_solve = test_solve();
    s_sum = test_sum();
    s_multi = test_multi();

    runner = srunner_create(s_solve);
    srunner_add_suite(runner, s_sum);
    srunner_add_suite(runner, s_multi);
    
    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
