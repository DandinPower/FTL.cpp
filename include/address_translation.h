#ifndef ADDRESS_TRANSLATION_H
#define ADDRESS_TRANSLATION_H
#include <data_type.h>

typedef struct {
    LPTable table;
} AddressTranslation;

AddressTranslation GetNewAddressTranslation();  // 回傳一個新物件

// 將nandcontroller回傳的ppa放進table

// 先search來檢查是否有相同lba

// 如果該lba已經有ppa就讓ftl知道來對nandcontroller下update invalid

// addresstranslation則直接覆蓋掉lba紀錄

#endif
