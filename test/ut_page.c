#include <stdlib.h>
#include <check.h>
#include <page.h>
#include <block.h>
#include <string.h>

// Declare your test suite
START_TEST(test_new_page)
{
    int address = 5;
    void* parentBlock = malloc(sizeof(Block));
    Page page = GetNewPage(address, parentBlock);
    ck_assert_int_eq(page.address, address);
    ck_assert_ptr_eq(page.parentBlock, parentBlock);
    ck_assert_int_eq(page.status, FREE);
    ck_assert_int_eq(page.lbaNums, 0);
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
        ck_assert_int_eq(page.storeLbas[i], -1);
    }
    free(parentBlock);
}
END_TEST

START_TEST(test_program_page)
{
    int address = 5;
    void* parentBlock = malloc(sizeof(Block));
    Page page = GetNewPage(address, parentBlock);
    long long lbas[2] = {1, 2};
    int lbaNums = 2;
    ProgramPage(&page, lbas, lbaNums);
    ck_assert_int_eq(page.status, VALID);
    ck_assert_int_eq(page.lbaNums, lbaNums);
    for (int i = 0; i < lbaNums; i++) {
        ck_assert_int_eq(page.storeLbas[i], lbas[i]);
    }
    free(parentBlock);
}
END_TEST

START_TEST(test_reset_page)
{
    int address = 5;
    void* parentBlock = malloc(sizeof(Block));
    Page page = GetNewPage(address, parentBlock);
    long long lbas[2] = {1, 2};
    int lbaNums = 2;
    ProgramPage(&page, lbas, lbaNums);
    ResetPage(&page);
    ck_assert_int_eq(page.status, FREE);
    ck_assert_int_eq(page.lbaNums, 0);
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
        ck_assert_int_eq(page.storeLbas[i], -1);
    }
    free(parentBlock);
}
END_TEST

// Add more tests if needed

// More cases for program page
START_TEST(test_program_page_full)
{
    int address = 5;
    void* parentBlock = malloc(sizeof(Block));
    Page page = GetNewPage(address, parentBlock);
    long long lbas[LBA_IN_PAGE_NUM];
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
        lbas[i] = i;
    }
    int lbaNums = LBA_IN_PAGE_NUM;
    ProgramPage(&page, lbas, lbaNums);
    ck_assert_int_eq(page.status, VALID);
    ck_assert_int_eq(page.lbaNums, lbaNums);
    for (int i = 0; i < lbaNums; i++) {
        ck_assert_int_eq(page.storeLbas[i], lbas[i]);
    }
    free(parentBlock);
}
END_TEST

// 沒特別做檢查
// START_TEST(test_program_page_overflow)
// {
//     int address = 5;
//     void* parentBlock = malloc(sizeof(Block));
//     Page page = GetNewPage(address, parentBlock);
//     long long lbas[LBA_IN_PAGE_NUM + 1];
//     for (int i = 0; i < LBA_IN_PAGE_NUM + 1; i++) {
//         lbas[i] = i;
//     }
//     int lbaNums = LBA_IN_PAGE_NUM + 1;
//     ProgramPage(&page, lbas, lbaNums);
//     ck_assert_int_eq(page.status, VALID);
//     ck_assert_int_eq(page.lbaNums, LBA_IN_PAGE_NUM); // should not exceed the page capacity
//     for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
//         ck_assert_int_eq(page.storeLbas[i], lbas[i]);
//     }
//     free(parentBlock);
// }
// END_TEST

// More cases for reset page
START_TEST(test_reset_page_after_program)
{
    int address = 5;
    void* parentBlock = malloc(sizeof(Block));
    Page page = GetNewPage(address, parentBlock);
    long long lbas[2] = {1, 2};
    int lbaNums = 2;
    ProgramPage(&page, lbas, lbaNums);
    ResetPage(&page);
    ck_assert_int_eq(page.status, FREE);
    ck_assert_int_eq(page.lbaNums, 0);
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
        ck_assert_int_eq(page.storeLbas[i], -1);
    }
    free(parentBlock);
}
END_TEST

START_TEST(test_reset_page_full)
{
    int address = 5;
    void* parentBlock = malloc(sizeof(Block));
    Page page = GetNewPage(address, parentBlock);
    long long lbas[LBA_IN_PAGE_NUM];
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
        lbas[i] = i;
    }
    int lbaNums = LBA_IN_PAGE_NUM;
    ProgramPage(&page, lbas, lbaNums);
    ResetPage(&page);
    ck_assert_int_eq(page.status, FREE);
    ck_assert_int_eq(page.lbaNums, 0);
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++) {
        ck_assert_int_eq(page.storeLbas[i], -1);
    }
    free(parentBlock);
}
END_TEST

// More cases for new page
START_TEST(test_new_page_different_address)
{
    int address1 = 5;
    void* parentBlock1 = malloc(sizeof(Block));
    Page page1 = GetNewPage(address1, parentBlock1);
    int address2 = 10;
    void* parentBlock2 = malloc(sizeof(Block));
    Page page2 = GetNewPage(address2, parentBlock2);
    ck_assert_int_ne(page1.address, page2.address);
    ck_assert_ptr_ne(page1.parentBlock, page2.parentBlock);
    free(parentBlock1);
    free(parentBlock2);
}
END_TEST

// This is the test suite
Suite* page_suite(void)
{
    Suite* s = suite_create("Page");
    TCase* tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_new_page);
    tcase_add_test(tc_core, test_program_page);
    tcase_add_test(tc_core, test_reset_page);
    tcase_add_test(tc_core, test_program_page_full);
    // tcase_add_test(tc_core, test_program_page_overflow);
    tcase_add_test(tc_core, test_reset_page_after_program);
    tcase_add_test(tc_core, test_reset_page_full);
    tcase_add_test(tc_core, test_new_page_different_address);
    suite_add_tcase(s, tc_core);
    return s;
}
