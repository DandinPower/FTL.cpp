#include <stdio.h>
#include <data_type.h>

void Test_LPTable() {
    LPTable table = GetNewLPTable();
    // Test Case 1: Insert and Lookup
    insert(&table, 100, 500);
    int ppa = searchPpa(&table, 100);
    printf("PPA for LBA 100: %d\n", ppa);  // Expected output: 500

    // Test Case 2: Insert Duplicate LBA
    insert(&table, 100, 600);
    ppa = searchPpa(&table, 100);
    printf("PPA for LBA 100 (after duplicate insert): %d\n", ppa);  // Expected output: 600

    // Test Case 3: Lookup Non-existent LBA
    ppa = searchPpa(&table, 200);
    printf("PPA for LBA 200: %d\n", ppa);  // Expected output: -1

    // Test Case 4: Insert and Lookup Multiple LBAs
    insert(&table, 200, 700);
    insert(&table, 300, 800);
    insert(&table, 400, 900);
    ppa = searchPpa(&table, 200);
    printf("PPA for LBA 200: %d\n", ppa);  // Expected output: 700
    ppa = searchPpa(&table, 300);
    printf("PPA for LBA 300: %d\n", ppa);  // Expected output: 800
    ppa = searchPpa(&table, 400);
    printf("PPA for LBA 400: %d\n", ppa);  // Expected output: 900

    // Test Case 5: Remove LBA
    insert(&table, 500, 1000);
    ppa = searchPpa(&table, 500);
    printf("PPA for LBA 500 (before removal): %d\n", ppa);  // Expected output: 1000
    insert(&table, 500, -1);  // Remove LBA 500 by setting ppa to -1
    ppa = searchPpa(&table, 500);
    printf("PPA for LBA 500 (after removal): %d\n", ppa);  // Expected output: -1
    FreeTable(&table);
}