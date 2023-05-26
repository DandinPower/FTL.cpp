#include <nand_controller.h>
#include <stdio.h>
#include <stdlib.h>

NandController GetNewNandController() {
    NandController newController;
    newController.freeBlockIndexesNums = 0;
    for (int i = 0; i < BLOCK_NUM; i++) 
        newController.freeBlockIndexes[i] = i;
    newController.currentHotBlockIndex = -1;    // 代表目前沒紀錄
    newController.currentColdBlockIndex = -1;   // 代表目前沒紀錄
    newController.blocks = malloc(sizeof(Block) * BLOCK_NUM);
    for (int i = 0; i < BLOCK_NUM; i++) 
        newController.blocks[i] = GetNewBlock(i);
    return newController;
}

int GetFreeBlockIndex(NandController* nandController, BlockType_t type) {
    if (type == HOT) {
        if (nandController->currentHotBlockIndex != -1)
            return nandController->currentHotBlockIndex;
        if (nandController->currentColdBlockIndex == nandController->freeBlockIndexes[0]) {
            if (nandController->freeBlockIndexesNums == 1) {
                printf("No free hot block\n");
            }
            else {
                nandController->currentHotBlockIndex = nandController->freeBlockIndexes[1];
                return nandController->currentHotBlockIndex;
            }
        }
        nandController->currentHotBlockIndex = nandController->freeBlockIndexes[0];
        return nandController->currentHotBlockIndex;
    }
    else if (type == COLD) {
        if (nandController->currentColdBlockIndex != -1)
            return nandController->currentColdBlockIndex;
        if (nandController->currentHotBlockIndex == nandController->freeBlockIndexes[0]) {
            if (nandController->freeBlockIndexesNums == 1) {
                printf("No free cold block\n");
            }
            else {
                nandController->currentColdBlockIndex = nandController->freeBlockIndexes[1];
                return nandController->currentColdBlockIndex;
            }
        }
        nandController->currentColdBlockIndex = nandController->freeBlockIndexes[0];
        return nandController->currentColdBlockIndex;
    }
    else {
        printf("Unknown block type\n");
    }
}

int Program(NandController* nandController, int lbas[], int lbaNums, BlockType_t type) {
    int programBlockIndex = GetFreeBlockIndex(nandController, type);
    int programPageAddress = ProgramBlock(&nandController->blocks[programBlockIndex], lbas, lbaNums, type);
    
    
    
    
    return -1;
}

void ShowNandControllerContent(NandController nandController)
{
    for (int i = 0; i < BLOCK_NUM; i++) {
        ShowBlockContent(nandController.blocks[i]);
    }
    printf("\n");
}

void FreeNandController(NandController* nandController) {
    for (int i = 0; i < BLOCK_NUM; i++) {
        FreeBlock(&nandController->blocks[i]);
    }
    free(nandController->blocks);
}