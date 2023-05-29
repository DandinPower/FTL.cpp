#include <nand_controller.h>
#include <check.h>

START_TEST(test_new_nandcontroller_initialization)
{
    NandController controller = GetNewNandController();
    ck_assert_int_eq(controller.currentHotBlockIndex, -1);
    ck_assert_int_eq(controller.currentColdBlockIndex, -1);
    for (int i = 0; i < BLOCK_NUM; i++) {
        ck_assert_int_eq(controller.blockStatus[i], 0);
        ck_assert_int_eq(controller.blockGCLevelStatus[i], 0);
    }
    FreeNandController(&controller);
}
END_TEST

START_TEST(test_get_write_block_index_hot)
{
    NandController controller = GetNewNandController();
    int index = GetWriteBlockIndex(&controller, HOT);
    ck_assert_int_eq(controller.blockStatus[index], 1);
    ck_assert_int_eq(controller.currentHotBlockIndex, index);
    FreeNandController(&controller);
}
END_TEST

START_TEST(test_get_write_block_index_cold)
{
    NandController controller = GetNewNandController();
    int index = GetWriteBlockIndex(&controller, COLD);
    ck_assert_int_eq(controller.blockStatus[index], 1);
    ck_assert_int_eq(controller.currentColdBlockIndex, index);
    FreeNandController(&controller);
}
END_TEST

START_TEST(test_get_write_block_index_unknown)
{
    NandController controller = GetNewNandController();
    int index = GetWriteBlockIndex(&controller, (BlockType_t)999);
    ck_assert_int_eq(index, -1);
    FreeNandController(&controller);
}
END_TEST

START_TEST(test_program_unknown)
{
    NandController controller = GetNewNandController();
    long long lbas[LBA_IN_PAGE_NUM];
    int address = Program(&controller, lbas, LBA_IN_PAGE_NUM, (BlockType_t)999);
    ck_assert_int_eq(address, -1);
    FreeNandController(&controller);
}
END_TEST

START_TEST(test_erase_free)
{
    NandController controller = GetNewNandController();
    int index = GetWriteBlockIndex(&controller, HOT);
    controller.blockStatus[index] = 0;
    // Here you should somehow check if "Erase on free block" is printed.
    // This depends on your test environment and might not be feasible.
    Erase(&controller, index);
    FreeNandController(&controller);
}
END_TEST

START_TEST(test_erase_block)
{
    NandController controller = GetNewNandController();
    int index = GetWriteBlockIndex(&controller, HOT);
    Erase(&controller, index);
    ck_assert_int_eq(controller.blockStatus[index], 0);
    FreeNandController(&controller);
}
END_TEST

START_TEST(test_free_nandcontroller)
{
    NandController controller = GetNewNandController();
    FreeNandController(&controller);
    ck_assert_ptr_eq(controller.blocks, NULL);
}
END_TEST

// Setting up test suite and adding test cases
Suite *nand_controller_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("Nand_Controller");
    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_new_nandcontroller_initialization);
    tcase_add_test(tc_core, test_get_write_block_index_hot);
    tcase_add_test(tc_core, test_get_write_block_index_cold);
    tcase_add_test(tc_core, test_get_write_block_index_unknown);
    tcase_add_test(tc_core, test_program_unknown);
    tcase_add_test(tc_core, test_erase_free);
    tcase_add_test(tc_core, test_erase_block);
    tcase_add_test(tc_core, test_free_nandcontroller);
    suite_add_tcase(s, tc_core);
    return s;
}