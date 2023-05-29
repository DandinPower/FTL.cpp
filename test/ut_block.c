#include <block.h>
#include <check.h>

// Initialize test suite and test case
START_TEST(test_GetNewBlock)
{
    // Use the function
    Block block = GetNewBlock(5);

    // Assert
    ck_assert_int_eq(block.index, 5);
    ck_assert_int_eq(block.invalidPage, 0);
    ck_assert_int_eq(block.currentPageIndex, 0);
    ck_assert_int_eq(block.type, NONE);
    ck_assert_ptr_nonnull(block.pages);
}
END_TEST

START_TEST(test_ProgramBlock)
{
    // Prepare data
    Block block = GetNewBlock(5);
    long long lbas[LBA_IN_PAGE_NUM] = {0, 1, 2, 3};
    int lbaNums = 4;
    BlockType_t type = HOT;

    // Use the function
    int programAddress = ProgramBlock(&block, lbas, lbaNums, type);
    // Assert
    ck_assert_int_eq(block.type, type);
    ck_assert_int_eq(block.currentPageIndex, 1);
    ck_assert_int_eq(block.pages[0].lbaNums, lbaNums);
}
END_TEST

START_TEST(test_new_block_not_full)
{
    Block block = GetNewBlock(0);
    ck_assert_int_eq(IsBlockFull(block), False);
    FreeBlock(&block);
}
END_TEST

START_TEST(test_program_block_exceed_capacity)
{
    Block block = GetNewBlock(0);
    long long lbas[LBA_IN_PAGE_NUM * PAGE_IN_BLOCK_NUM + 1];
    for (int i = 0; i < LBA_IN_PAGE_NUM * PAGE_IN_BLOCK_NUM + 1; i++) {
        lbas[i] = i;
    }
    int address = ProgramBlock(&block, lbas, LBA_IN_PAGE_NUM * PAGE_IN_BLOCK_NUM + 1, HOT);
    ck_assert_int_eq(address, -1);
    FreeBlock(&block);
}
END_TEST

START_TEST(test_program_block_does_not_change_type)
{
    Block block = GetNewBlock(0);
    block.type = COLD;
    long long lbas[LBA_IN_PAGE_NUM];
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
        lbas[i] = i;
    }
    ProgramBlock(&block, lbas, LBA_IN_PAGE_NUM, HOT);
    ck_assert_int_eq(block.type, COLD);
    FreeBlock(&block);
}
END_TEST

START_TEST(test_program_block_changes_none_type)
{
    Block block = GetNewBlock(0);
    long long lbas[LBA_IN_PAGE_NUM];
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
        lbas[i] = i;
    }
    ProgramBlock(&block, lbas, LBA_IN_PAGE_NUM, COLD);
    ck_assert_int_eq(block.type, COLD);
    FreeBlock(&block);
}
END_TEST

START_TEST(test_program_block_full)
{
    Block block = GetNewBlock(0);
    long long lbas[LBA_IN_PAGE_NUM];
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
        lbas[i] = i;
    }
    for (int i = 0; i < PAGE_IN_BLOCK_NUM; i++) {
        ProgramBlock(&block, lbas, LBA_IN_PAGE_NUM, HOT);
    }
    int address = ProgramBlock(&block, lbas, LBA_IN_PAGE_NUM, HOT);
    ck_assert_int_eq(address, -1);
    FreeBlock(&block);
}
END_TEST

START_TEST(test_erase_block_sets_none_type)
{
    Block block = GetNewBlock(0);
    block.type = HOT;
    EraseBlock(&block);
    ck_assert_int_eq(block.type, NONE);
    FreeBlock(&block);
}
END_TEST

START_TEST(test_erase_block_resets_currentPageIndex)
{
    Block block = GetNewBlock(0);
    long long lbas[LBA_IN_PAGE_NUM];
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
        lbas[i] = i;
    }
    ProgramBlock(&block, lbas, LBA_IN_PAGE_NUM, HOT);
    EraseBlock(&block);
    ck_assert_int_eq(block.currentPageIndex, 0);
    FreeBlock(&block);
}
END_TEST

START_TEST(test_erase_block_resets_pages)
{
    Block block = GetNewBlock(0);
    long long lbas[LBA_IN_PAGE_NUM];
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
        lbas[i] = i;
    }
    ProgramBlock(&block, lbas, LBA_IN_PAGE_NUM, HOT);
    EraseBlock(&block);
    for (int i = 0; i < PAGE_IN_BLOCK_NUM; i++) {
        ck_assert_int_eq(block.pages[i].status, FREE);
        ck_assert_int_eq(block.pages[i].lbaNums, 0);
    }
    FreeBlock(&block);
}
END_TEST

START_TEST(test_program_block_returns_correct_address)
{
    Block block = GetNewBlock(0);
    long long lbas[LBA_IN_PAGE_NUM];
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
        lbas[i] = i;
    }
    int address = ProgramBlock(&block, lbas, LBA_IN_PAGE_NUM, HOT);
    ck_assert_int_eq(address, block.index * PAGE_IN_BLOCK_NUM);
    FreeBlock(&block);
}
END_TEST

START_TEST(test_program_block_zero_lba)
{
    Block block = GetNewBlock(0);
    long long lbas[LBA_IN_PAGE_NUM];
    int address = ProgramBlock(&block, lbas, 0, HOT);
    ck_assert_int_eq(address, -1);
    FreeBlock(&block);
}
END_TEST

// Setting up test suite and adding test cases
Suite *block_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Block");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_GetNewBlock);
    tcase_add_test(tc_core, test_ProgramBlock);
    tcase_add_test(tc_core, test_new_block_not_full);
    tcase_add_test(tc_core, test_program_block_exceed_capacity);
    tcase_add_test(tc_core, test_program_block_does_not_change_type);
    tcase_add_test(tc_core, test_program_block_changes_none_type);
    tcase_add_test(tc_core, test_program_block_full);
    tcase_add_test(tc_core, test_erase_block_sets_none_type);
    tcase_add_test(tc_core, test_erase_block_resets_currentPageIndex);
    tcase_add_test(tc_core, test_erase_block_resets_pages);
    tcase_add_test(tc_core, test_program_block_returns_correct_address);
    tcase_add_test(tc_core, test_program_block_zero_lba);

    suite_add_tcase(s, tc_core);

    return s;
}