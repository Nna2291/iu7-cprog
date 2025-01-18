#include <stdlib.h>
#include <check.h>
#include "check_sort.h"
#include "check_read.h"
#include "check_substr.h"
int main(void)
{
    int no_failed = 0;
    Suite *s_sort, *s_sub, *s_read;
    SRunner *runner;

    s_sort = test_sort();
    s_sub = test_substr();
    s_read = test_read();
    runner = srunner_create(s_sort);
    srunner_add_suite(runner, s_sub);
    srunner_add_suite(runner, s_read);
    
    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
