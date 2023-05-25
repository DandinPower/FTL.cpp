#ifndef PAGE_H
#define PAGE_H

typedef enum PageStatus {
    FREE,
    VALID,
    INVALID
} PageStatus_t;

typedef struct {
    PageStatus_t status; // 紀錄Page目前的狀態
    int address;         // 該Page的實體Address
} Page;

Page GetInitialPage(int address);

#endif