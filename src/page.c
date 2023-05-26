#include <page.h>
#include <block.h>
#include <stdio.h>
#include <string.h>

Page GetNewPage(int address, void *parentBlock)
{
    Page newPage;
    newPage.status = FREE;
    newPage.address = address;
    newPage.parentBlock = parentBlock;
    newPage.lbaNums = 0;
    memset(newPage.storeLbas, -1, sizeof(int) * LBA_IN_PAGE_NUM);
    return newPage;
}

void ProgramPage(Page *page, int lbas[], int lbaNums)
{
    page->status = VALID;
    int totalNums = lbaNums + page->lbaNums;
    if (totalNums > LBA_IN_PAGE_NUM)
        printf("Exceeds page capacity\n");
    int j = 0;
    for (int i = page->lbaNums; i < totalNums; i++)
    {
        page->storeLbas[i] = lbas[j];
        j += 1;
    }
    page->lbaNums = totalNums;
}

void ResetPage(Page *page)
{
    page->status = FREE;
    page->lbaNums = 0;
    for (int i = 0; i < LBA_IN_PAGE_NUM; i++)
    {
        page->storeLbas[i] = -1; // -1 代表是空的
    }
}

void ShowPageContent(Page page)
{
    printf("Page Address: %d\n", page.address);
    printf("Page Status: %d\n", page.status);
    printf("Page Parent Block: %p\n", page.parentBlock);
    printf("Page LBA Nums: %d\n", page.lbaNums);
    printf("LBA Addresses:\n");
    for (int i = 0; i < page.lbaNums; i++)
    {
        printf("%d ", page.storeLbas[i]);
    }
    printf("\n\n");
}