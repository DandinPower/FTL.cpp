#include <block.h>
#include <page.h>
#include <stdio.h>
#include <stdlib.h>

Block GetNewBlock(int index)
{
    Block newBlock;
    newBlock.index = index;
    newBlock.invalidPage = 0;
    newBlock.currentPageIndex = 0;
    newBlock.type = NONE;
    newBlock.pages = malloc(sizeof(Page) * PAGE_IN_BLOCK_NUM);
    for (int i = 0; i < PAGE_IN_BLOCK_NUM; i++)
    {
        int address = index * PAGE_IN_BLOCK_NUM + i;
        newBlock.pages[i] = GetNewPage(address, &newBlock);
    }
    return newBlock;
}

int ProgramBlock(Block *block, int lbas[], int lbaNums, BlockType_t type)
{
    if (block->type == NONE)
        block->type = type;
    if (block->type != type)
        printf("Program on different block type\n");
    if (block->currentPageIndex == PAGE_IN_BLOCK_NUM)
        printf("Insufficent space in block to program\n");
    if (block->pages[block->currentPageIndex].status != FREE)
        printf("Program on not free page\n");
    ProgramPage(&block->pages[block->currentPageIndex], lbas, lbaNums);
    int programAddress = block->pages[block->currentPageIndex].address;
    block->currentPageIndex += 1;
    return programAddress;
}

bool IsBlockFull(Block block)
{
    return block.currentPageIndex == PAGE_IN_BLOCK_NUM;
}

void EraseBlock(Block *block)
{
    block->invalidPage = 0;
    block->currentPageIndex = 0;
    block->type = NONE;
    for (int i = 0; i < PAGE_IN_BLOCK_NUM; i++)
    {
        ResetPage(&block->pages[i]);
    }
}

void ShowBlockContent(Block block)
{
    printf("Block index: %d\n", block.index);
    printf("Invalid pages: %d\n", block.invalidPage);
    printf("Current page index: %d\n", block.currentPageIndex);
    printf("Block type: %d\n", block.type);
    // Display the content of each page within the block
    for (int i = 0; i < PAGE_IN_BLOCK_NUM; i++)
    {
        if (block.pages[i].status != FREE)
        {
            ShowPageContent(block.pages[i]);
        }
    }
    printf("\n");
}

void FreeBlock(Block *block) {
    free(block->pages);
}
