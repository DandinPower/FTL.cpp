#ifndef BLOCK_H
#define BLOCK_H
#include <config.h>
#include <page.h>

typedef enum BlockType {
    NONE,
    HOT,
    COLD
} BlockType_t;

typedef struct {
    int index;            // 該block在nand controller內部的index
    int invalidPage;      // 目前invalid Page的數量
    int currentPageIndex; // 目前寫入到哪個Page
    BlockType_t type;     // Block的種類 用來區分hot cold
    Page pages[PAGE_IN_BLOCK_NUM];    // 一個block裡面的page array
} Block;

Block GetNewBlock(int index);   // 回傳一個新的block

int ProgramBlock(Block *block, int lbas[], int lbaNums, BlockType_t type);  // 將lbas(1 - LBA_IN_PAGE_NUM)寫入指定的block, 回傳寫入的page address

bool IsBlockFull(Block block);  // 檢查block是否滿了

void EraseBlock(Block *block);  // erase掉block

void ShowBlockContent(Block block); // 印出block的資訊

#endif