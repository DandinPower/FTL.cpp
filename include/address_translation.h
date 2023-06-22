#ifndef ADDRESS_TRANSLATION_H
#define ADDRESS_TRANSLATION_H
#include <data_type.h>

typedef struct {
    LPTable table;
} AddressTranslation;

AddressTranslation GetNewAddressTranslation();  // 回傳一個新物件

void UpdateTable(AddressTranslation* addressTranslation, long long lbas[], int lbaNums, int pageAddress); // 更新logic -> physical table

#endif
