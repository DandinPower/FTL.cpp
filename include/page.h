#ifndef PAGE_H
#define PAGE_H
#include <config.h>

typedef enum PageStatus
{
    FREE,
    VALID,
    INVALID
} PageStatus_t;

typedef struct
{
    int address;                    // 該Page的實體Address
    PageStatus_t status;            // 紀錄Page目前的狀態
    void *parentBlock;              // 指向擁有該Page的Block，特別注意這裡的pointer要傳入Block的pointer
    int lbaNums;                    // 目前有的lba數量
    int storeLbas[LBA_IN_PAGE_NUM]; // 一個page裡面的lba address array
} Page;

Page GetNewPage(int address, void *parentBlock); // 回傳一個新的Page

void ProgramPage(Page *page, int lbas[], int lbaNums); // 將lbas 寫入進page裡

void ResetPage(Page *page); // 清空Page內的lba相關資訊

void ShowPageContent(Page page); // 顯示Page的資訊

#endif