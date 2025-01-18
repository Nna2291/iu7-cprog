#include <stdlib.h>
#include <check.h>

#include "check_snprintf.h"

int main(void)
{
    int no_failed = 0;
    Suite *s_snprintf;
    SRunner *runner;

    s_snprintf= test_snprintf();

    runner = srunner_create(s_snprintf);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
