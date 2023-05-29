#ifndef NAND_CONTROLLER_H
#define NAND_CONTROLLER_H
#include <block.h>

typedef struct {
    int currentHotBlockIndex;   // 紀錄目前的hot block index, -1代表需要時去找一個新的
    int currentColdBlockIndex;  // 紀錄目前的cold block index, -1代表需要時去找一個新的
    int blockStatus[BLOCK_NUM];    // 0代表free, 1代表被佔用了
    int blockGCLevelStatus[BLOCK_NUM];  // 0代表不用被GC, 1代表要被GC了, 每次block被update invalid時去更新該表
    Block* blocks;    // 存放block array pointer
} NandController;

NandController GetNewNandController();  // 回傳一個新的物件

int GetWriteBlockIndex(NandController* nandController, BlockType_t type); // 找出特定type的free block

int Program(NandController* nandController, long long lbas[], int lbaNums, BlockType_t type); // 寫入新的request, 回傳寫入的page address

void Erase(NandController* nandController, int blockIndex); // 當GC時需要Erase用

void ShowNandControllerContent(NandController nandController);  // 顯示該nandcontroller的資訊

void FreeNandController(NandController* nandController);    // 釋放掉Block空間

#endif