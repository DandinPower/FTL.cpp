#ifndef NAND_CONTROLLER_H
#define NAND_CONTROLLER_H
#include <block.h>

typedef struct {
    int currentHotBlockIndex;   // 紀錄目前的hot block index, -1代表需要時去找一個新的
    int currentColdBlockIndex;  // 紀錄目前的cold block index, -1代表需要時去找一個新的
    int blockStatus[BLOCK_NUM];    // 0代表free, 1代表被佔用了
    Block* blocks;    // 存放block array pointer
} NandController;

NandController GetNewNandController();  // 回傳一個新的物件

int GetWriteBlockIndex(NandController* nandController, BlockType_t type); // 找出特定type的free block

int Program(NandController* nandController, int lbas[], int lbaNums, BlockType_t type); // 寫入新的request, 回傳寫入的page address

void ShowNandControllerContent(NandController nandController);  // 顯示該nandcontroller的資訊

void FreeNandController(NandController* nandController);    // 釋放掉Block空間

#endif