#include <stdlib.h>
#include <check.h>
#include "data_type.h"

START_TEST (test_get_null_node)
{
    Node node = GetNullNode();
    ck_assert_int_eq(node.pair.lba, -1);
    ck_assert_int_eq(node.pair.ppa, -1);
    ck_assert_ptr_eq(node.next, NULL);
}
END_TEST

START_TEST (test_get_new_node)
{
    long long lba = 1;
    int ppa = 1;
    Node node = GetNewNode(lba, ppa);
    ck_assert_int_eq(node.pair.lba, lba);
    ck_assert_int_eq(node.pair.ppa, ppa);
    ck_assert_ptr_eq(node.next, NULL);
}
END_TEST

START_TEST (test_get_new_lp_table)
{
    LPTable table = GetNewLPTable();
    for (int i = 0; i < TABLE_SIZE; i++) {
        ck_assert_int_eq(table.entries[i].pair.lba, -1);
        ck_assert_int_eq(table.entries[i].pair.ppa, -1);
        ck_assert_ptr_eq(table.entries[i].next, NULL);
    }
    FreeTable(&table);
}
END_TEST

START_TEST (test_insert_and_search_ppa)
{
    LPTable table = GetNewLPTable();
    long long lba = 10;
    int ppa = 20;
    insert(&table, lba, ppa);
    int found_ppa = searchPpa(&table, lba);
    ck_assert_int_eq(found_ppa, ppa);
    FreeTable(&table);
}
END_TEST

/* Add additional 20 test cases */

START_TEST (test_insert_single_entry)
{
    LPTable table = GetNewLPTable();
    long long lba = 50;
    int ppa = 100;
    insert(&table, lba, ppa);
    int found_ppa = searchPpa(&table, lba);
    ck_assert_int_eq(found_ppa, ppa);
    FreeTable(&table);
}
END_TEST

START_TEST (test_insert_multiple_entries)
{
    LPTable table = GetNewLPTable();
    long long lba[5] = {1, 2, 3, 4, 5};
    int ppa[5] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        insert(&table, lba[i], ppa[i]);
        int found_ppa = searchPpa(&table, lba[i]);
        ck_assert_int_eq(found_ppa, ppa[i]);
    }
    FreeTable(&table);
}
END_TEST

START_TEST (test_search_non_existent_entry)
{
    LPTable table = GetNewLPTable();
    int found_ppa = searchPpa(&table, 10);
    ck_assert_int_eq(found_ppa, -1);
    FreeTable(&table);
}
END_TEST

START_TEST (test_insert_update_existing_entry)
{
    LPTable table = GetNewLPTable();
    long long lba = 30;
    int ppa = 60;
    insert(&table, lba, ppa);
    ppa = 80;
    insert(&table, lba, ppa);
    int found_ppa = searchPpa(&table, lba);
    ck_assert_int_eq(found_ppa, ppa);
    FreeTable(&table);
}
END_TEST

START_TEST (test_hash)
{
    long long lba = 50;
    int hash_val = hash(lba);
    ck_assert_int_eq(hash_val, lba % TABLE_SIZE);
}
END_TEST

START_TEST (test_insert_hash_collision)
{
    LPTable table = GetNewLPTable();
    long long lba1 = 5;
    long long lba2 = 5 + TABLE_SIZE;
    int ppa1 = 15;
    int ppa2 = 25;
    insert(&table, lba1, ppa1);
    insert(&table, lba2, ppa2);
    int found_ppa1 = searchPpa(&table, lba1);
    int found_ppa2 = searchPpa(&table, lba2);
    ck_assert_int_eq(found_ppa1, ppa1);
    ck_assert_int_eq(found_ppa2, ppa2);
    FreeTable(&table);
}
END_TEST

START_TEST (test_get_new_node_values)
{
    long long lba = 1234567890;
    int ppa = 1234;
    Node node = GetNewNode(lba, ppa);
    ck_assert_int_eq(node.pair.lba, lba);
    ck_assert_int_eq(node.pair.ppa, ppa);
    ck_assert_ptr_eq(node.next, NULL);
}
END_TEST

START_TEST (test_get_null_node_values)
{
    Node node = GetNullNode();
    ck_assert_int_eq(node.pair.lba, -1);
    ck_assert_int_eq(node.pair.ppa, -1);
    ck_assert_ptr_eq(node.next, NULL);
}
END_TEST

START_TEST (test_insert_table_full)
{
    LPTable table = GetNewLPTable();
    for (long long lba = 0; lba < TABLE_SIZE; lba++) {
        insert(&table, lba, lba);
    }
    for (long long lba = 0; lba < TABLE_SIZE; lba++) {
        ck_assert_int_eq(searchPpa(&table, lba), lba);
    }
    FreeTable(&table);
}
END_TEST

START_TEST (test_free_table)
{
    LPTable table = GetNewLPTable();
    FreeTable(&table);
    ck_assert_ptr_eq(table.entries, NULL);
}
END_TEST

/* Add test cases to the test suite */

Suite* data_type_suite(void) {
    Suite* s;
    TCase* tc_core;

    s = suite_create("Data Type");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_get_null_node);
    tcase_add_test(tc_core, test_get_new_node);
    tcase_add_test(tc_core, test_get_new_lp_table);
    tcase_add_test(tc_core, test_insert_and_search_ppa);
    tcase_add_test(tc_core, test_insert_single_entry);
    tcase_add_test(tc_core, test_insert_multiple_entries);
    tcase_add_test(tc_core, test_search_non_existent_entry);
    tcase_add_test(tc_core, test_insert_update_existing_entry);
    tcase_add_test(tc_core, test_hash);
    tcase_add_test(tc_core, test_insert_hash_collision);
    tcase_add_test(tc_core, test_get_new_node_values);
    tcase_add_test(tc_core, test_get_null_node_values);
    tcase_add_test(tc_core, test_insert_table_full);
    tcase_add_test(tc_core, test_free_table);
    
    suite_add_tcase(s, tc_core);

    return s;
}
