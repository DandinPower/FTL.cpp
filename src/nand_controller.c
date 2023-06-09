#include <nand_controller.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

NandController GetNewNandController() {
    NandController newController;
    memset(newController.blockStatus, 0, sizeof(int) * BLOCK_NUM);
    memset(newController.blockGCLevelStatus, 0, sizeof(int) * BLOCK_NUM);
    newController.currentHotBlockIndex = -1;    // 代表目前沒紀錄
    newController.currentColdBlockIndex = -1;   // 代表目前沒紀錄
    newController.blocks = malloc(sizeof(Block) * BLOCK_NUM);
    for (int i = 0; i < BLOCK_NUM; i++) 
        newController.blocks[i] = GetNewBlock(i);
    return newController;
}

int GetWriteBlockIndex(NandController* nandController, BlockType_t type) {
    if (type == HOT) {
        if (nandController->currentHotBlockIndex == -1) {
            for (int i = 0; i < BLOCK_NUM; i++) {
                if (!nandController->blockStatus[i]) {
                    nandController->currentHotBlockIndex = i;
                    nandController->blockStatus[i] = 1;
                    break;
                }
            }
        }
        if (nandController->currentHotBlockIndex == -1) printf("Can't find free block\n");
        return nandController->currentHotBlockIndex;
    }
    else if (type == COLD) {
        if (nandController->currentColdBlockIndex == -1) {
            for (int i = 0; i < BLOCK_NUM; i++) {
                if (!nandController->blockStatus[i]) {
                    nandController->currentColdBlockIndex = i;
                    nandController->blockStatus[i] = 1;
                    break;
                }
            }
        }
        if (nandController->currentColdBlockIndex == -1) printf("Can't find free block\n");
        return nandController->currentColdBlockIndex;
    }
    else {
        printf("Unknown block type\n");
        return -1;
    }
}

int Program(NandController* nandController, long long lbas[], int lbaNums, BlockType_t type) {
    int programBlockIndex = GetWriteBlockIndex(nandController, type);
    if (programBlockIndex == -1) return -1;
    int programPageAddress = ProgramBlock(&nandController->blocks[programBlockIndex], lbas, lbaNums, type);
    if (IsBlockFull(nandController->blocks[programBlockIndex])) {
        if (type == HOT) nandController->currentHotBlockIndex = -1;
        else if (type == COLD) nandController->currentColdBlockIndex = -1;
        else printf("Unknown block type\n");
    }
    return programPageAddress;
}

void Erase(NandController* nandController, int blockIndex) {
    if (!nandController->blockStatus[blockIndex]) printf("Erase on free block\n");
    nandController->blockStatus[blockIndex] = 0;
    EraseBlock(&nandController->blocks[blockIndex]);
}

void ShowNandControllerContent(NandController nandController)
{
    for (int i = 0; i < BLOCK_NUM; i++) {
        ShowBlockContent(nandController.blocks[i]);
    }
    printf("\n");
}

void FreeNandController(NandController* nandController) {
    if (nandController->blocks != NULL) {
        for (int i = 0; i < BLOCK_NUM; i++) {
            FreeBlock(&nandController->blocks[i]);
        }
        free(nandController->blocks);
        nandController->blocks = NULL;
    }
}