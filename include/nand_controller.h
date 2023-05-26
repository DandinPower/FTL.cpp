#ifndef NAND_CONTROLLER_H
#define NAND_CONTROLLER_H
#include <block.h>

typedef struct {
    int currentHotBlockIndex;   // 紀錄目前的hot block index
    int currentColdBlockIndex;  // 紀錄目前的cold block index
    int freeBlockIndexesNums;   // 紀錄數量
    int freeBlockIndexes[BLOCK_NUM];    // 存放freeblock的index
    Block* blocks;    // 存放block array pointer
} NandController;

NandController GetNewNandController();  // 回傳一個新的物件

int GetFreeBlockIndex(NandController* nandController, BlockType_t type); // 找出特定type的free block

int Program(NandController* nandController, int lbas[], int lbaNums, BlockType_t type); // 寫入新的request, 回傳寫入的page address

void ShowNandControllerContent(NandController nandController);  // 顯示該nandcontroller的資訊

void FreeNandController(NandController* nandController);    // 釋放掉Block空間

#endif