#include <stdlib.h>
#include <check.h>
#include "ut_data_type.h"
#include "ut_page.h"
#include "ut_block.h"
#include "ut_nand_controller.h"

int main(void) {
    int number_failed;
    Suite* s_data_type = data_type_suite();
    Suite* s_page = page_suite();
    Suite* s_block = block_suite();
    Suite* s_nand_controller = nand_controller_suite();
    SRunner *sr = srunner_create(s_data_type);
    srunner_add_suite(sr, s_page);
    srunner_add_suite(sr, s_block);
    srunner_add_suite(sr, s_nand_controller);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    // free the runner
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}