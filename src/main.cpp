#include "address_translation/address_translation.h"
#include "garbage_collection/garbage_collection.h"
#include "nand_controller/nand_controller.h"

#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<AddressTranslation> address_translation = std::make_unique<AddressTranslation>();
    std::unique_ptr<GarbageCollection> garbage_collection = std::make_unique<GarbageCollection>();
    std::unique_ptr<NandController> nand_controller = std::make_unique<NandController>();

    // Use the FTL simulator components here
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
