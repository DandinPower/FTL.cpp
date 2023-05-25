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