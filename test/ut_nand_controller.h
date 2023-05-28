#include <nand_controller.h>
#include <stdio.h>

void testNandController() {
    NandController nandController = GetNewNandController();
    
    // Test GetWriteBlockIndex
    int hotBlockIndex = GetWriteBlockIndex(&nandController, HOT);
    int coldBlockIndex = GetWriteBlockIndex(&nandController, COLD);
    printf("Hot block index: %d\n", hotBlockIndex);
    printf("Cold block index: %d\n", coldBlockIndex);
    
    // Test Program
    int lbas[] = {1, 2, 3};
    int lbaNums = sizeof(lbas) / sizeof(lbas[0]);
    int pageAddress = Program(&nandController, lbas, lbaNums, HOT);
    printf("Programmed page address: %d\n", pageAddress);
    
    // Test ShowNandControllerContent
    printf("NAND Controller Content:\n");
    ShowNandControllerContent(nandController);
    
    // Test filling up a block with pages
    printf("Filling up a block with pages:\n");
    for (int i = 0; i < 10; i++) {
        int lbas2[] = {i + 1};
        int lbaNums2 = sizeof(lbas2) / sizeof(lbas2[0]);
        int pageAddress = Program(&nandController, lbas2, lbaNums2, HOT);
        printf("Programmed page address: %d\n", pageAddress);
    }
    ShowNandControllerContent(nandController);
    
    // Test block overflow
    printf("Block overflow:\n");
    int lbas3[] = {11};
    int lbaNums3 = sizeof(lbas3) / sizeof(lbas3[0]);
    int pageAddress3 = Program(&nandController, lbas3, lbaNums3, HOT);
    printf("Programmed page address: %d\n", pageAddress3);
    ShowNandControllerContent(nandController);
    
    // Test Erase
    printf("Erase a block:\n");
    Erase(&nandController, 2);
    ShowNandControllerContent(nandController);
    
    // Test FreeNandController
    FreeNandController(&nandController);
}