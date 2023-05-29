#include <stdlib.h>
#include <check.h>
#include "ut_data_type.h"
#include "ut_page.h"
#include "ut_block.h"

int main(void) {
    int number_failed;
    Suite* s_data_type = data_type_suite();
    Suite* s_page = page_suite();
    Suite* s_block = block_suite();
    // create the test runner
    SRunner *sr = srunner_create(s_data_type);
    srunner_add_suite(sr, s_page); // add the page test suite to the runner
    srunner_add_suite(sr, s_block); // add the page test suite to the runner
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    // free the runner
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}