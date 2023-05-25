#include <page.h>
#include <block.h>
#include <stdio.h>

// Function to test ProgramBlock
void testProgramBlock() {
    Block block = GetNewBlock(0);
    
    // Test case 1: Program lbas into the block
    int lbas[] = {1, 2, 3};
    int lbaNums = sizeof(lbas) / sizeof(lbas[0]);
    printf("ProgramBlock Test 1:\n");
    ProgramBlock(&block, lbas, lbaNums, HOT);
    ShowBlockContent(block);
    
    // Test case 2: Insufficient space in block
    int lbas2[] = {4, 5, 6, 7};
    int lbaNums2 = sizeof(lbas2) / sizeof(lbas2[0]);
    printf("ProgramBlock Test 2:\n");
    ProgramBlock(&block, lbas2, lbaNums2, HOT);
    ShowBlockContent(block);
}

int main() {
    // Test ProgramBlock function
    printf("ProgramBlock Test:\n");
    testProgramBlock();

    return 0;
}
