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

void ShowNandControllerContent(NandController nandController);  // 顯示該nandcontroller的資訊

void FreeNandController(NandController* nandController);    // 釋放掉Block空間

#endif