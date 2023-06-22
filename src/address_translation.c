#include <address_translation.h>

AddressTranslation GetNewAddressTranslation() {
    AddressTranslation newAddressTranslation;
    newAddressTranslation.table = GetNewLPTable();
    return newAddressTranslation;
}

void UpdateTable(AddressTranslation* addressTranslation, long long lbas[], int lbaNums, int pageAddress) {
    // 將nandcontroller回傳的ppa放進table

    // 先search來檢查是否有相同lba

    // 可能需要刻一個Struct來放回傳override pair array

    // 如果該lba已經有ppa就讓ftl知道來對nandcontroller下update invalid

    // addresstranslation則直接覆蓋掉lba紀錄
}