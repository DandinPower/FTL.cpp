#include <address_translation.h>

AddressTranslation GetNewAddressTranslation() {
    AddressTranslation newAddressTranslation;
    newAddressTranslation.table = GetNewLPTable();
    return newAddressTranslation;
}

void UpdateTable(AddressTranslation* addressTranslation, long long lbas[], int lbaNums, int pageAddress) {
    
}