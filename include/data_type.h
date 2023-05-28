#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include <config.h>

typedef struct {
    long long  lba;   // lba地址in bytes
    int ppa;    // ppa地址 一個page可以裝4個lba
} LogicPhysicalPair;

typedef struct {
    LogicPhysicalPair pair; //key value pair
    void* next;  // linked list節點
} Node;

typedef struct {
    Node* entries;  // entry array (TABLE_SIZE)
} LPTable;  // hashtable

Node GetNullNode(); // 取得初始化的node

Node GetNewNode(long long lba, int ppa);    //  取得新的node

int hash(long long lba); // hash function

LPTable GetNewLPTable();    // 取得一個新的table instance

void FreeTable(LPTable* table); // free掉entry array

void insert(LPTable* table, long long lba, int ppa);    // 插入新的lba -> ppa pair

int searchPpa(LPTable *table, long long lba); // 找出該lba被放的ppa, 如果回傳-1代表找不到

#endif