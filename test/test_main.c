#include "check.h"
#include "stdlib.h"

#include "token_stack_test.c"

Suite * money_suite(void)
{
    Suite *s;
    TCase *tc_core;
     
    s = suite_create("Money");
     
    /* Core test case */
    tc_core = tcase_create("Core");
     
    tcase_add_test(tc_core, token_stack_test);
    tcase_add_test(tc_core, stack_overflow_test);
    tcase_add_test(tc_core, pop_empty_stack);

    suite_add_tcase(s, tc_core);
     
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;
     
    s = money_suite();
    sr = srunner_create(s);
     
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
