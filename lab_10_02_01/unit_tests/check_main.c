#include <stdlib.h>
#include <check.h>

#include "check_derivative.h"
#include "check_div.h"
#include "check_sum.h"
#include "check_value.h"

int main(void)
{
    int no_failed = 0;
    Suite *s_derivative, *s_val, *s_div, *s_sum;
    SRunner *runner;

    s_derivative = test_derivative();
    s_val = test_value();
    s_div = test_div();
    s_sum = test_sum();

    runner = srunner_create(s_derivative);
    srunner_add_suite(runner, s_val);
    srunner_add_suite(runner, s_div);
    srunner_add_suite(runner, s_sum);
    
    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
