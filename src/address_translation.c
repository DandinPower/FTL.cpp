#include <address_translation.h>

AddressTranslation GetNewAddressTranslation() {
    AddressTranslation newAddressTranslation;
    newAddressTranslation.table = GetNewLPTable();
    return newAddressTranslation;
}