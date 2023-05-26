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

void testNandController() {
    NandController nandController = GetNewNandController();
    
    // Test filling up a block with pages
    printf("Filling up a block with pages:\n");
    for (int i = 0; i < 10; i++) {
        int lbas[] = {i + 1};
        int lbaNums = sizeof(lbas) / sizeof(lbas[0]);
        int pageAddress = Program(&nandController, lbas, lbaNums, HOT);
        printf("Programmed page address: %d\n", pageAddress);
    }
    ShowNandControllerContent(nandController);
    
    // Test block overflow
    printf("Block overflow:\n");
    int lbas[] = {11};
    int lbaNums = sizeof(lbas) / sizeof(lbas[0]);
    int pageAddress = Program(&nandController, lbas, lbaNums, HOT);
    printf("Programmed page address: %d\n", pageAddress);
    ShowNandControllerContent(nandController);
    
    // Test FreeNandController
    FreeNandController(&nandController);
}

int main() {
    // Test ProgramBlock function
    printf("ProgramBlock Test:\n");
    testProgramBlock();

    return 0;
}
