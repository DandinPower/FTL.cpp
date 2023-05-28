#include <data_type.h>
#include <string.h>
#include <stdlib.h>

Node GetNullNode() {
    Node newNode;
    newNode.pair.lba = -1;
    newNode.pair.ppa = -1;
    newNode.next = NULL;
    return newNode;
}

Node GetNewNode(long long lba, int ppa) {
    Node newNode;
    newNode.pair.lba = lba;
    newNode.pair.ppa = ppa;
    newNode.next = NULL;
    return newNode;
}

int hash(long long lba) {
    return lba % TABLE_SIZE;
}

LPTable GetNewLPTable() {
    LPTable newTable;
    newTable.entries = (Node*)malloc(sizeof(Node) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        newTable.entries[i] = GetNullNode();
    }
    return newTable;
}

void FreeTable(LPTable* table) {
    free(table->entries);
}

void insert(LPTable* table, long long lba, int ppa) {
    int index = hash(lba);
    Node* current = &table->entries[index];
    if (current->pair.lba == -1) {
        *current = GetNewNode(lba, ppa);
    }
    else {
        while (current != NULL) {
            if (current->pair.lba == lba) {
                current->pair.ppa = ppa;
                return;
            }
            if (current->next == NULL) {
                Node newNode = GetNewNode(lba, ppa);
                current->next = &newNode;
                return;
            }
            current = current->next;
        }
    }
}

int searchPpa(LPTable *table, long long lba) {
    int index = hash(lba);
    Node* current = &table->entries[index];
    if (current->pair.lba == -1) return -1;
    while (current != NULL) {
        if (current->pair.lba == lba) {
            return current->pair.ppa;
        }
        current = current->next;
    }
    return -1;
}