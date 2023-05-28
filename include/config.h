#ifndef CONFIG_H
#define CONFIG_H

#define LBA_BYTES 4096
#define LBA_IN_PAGE_NUM 4
#define PAGE_IN_BLOCK_NUM 10
#define BLOCK_NUM 5

#define BLOCK_GC_LEVEL 0.95

// lba to ppa map size
#define TABLE_SIZE 20000

// Type
#define bool int
#define True 1
#define False 0

#endif