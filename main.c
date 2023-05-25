#include <stdio.h>
#include <nand_controller.h>
#include <block.h>
#include <page.h>

int main() {
    NandController nandController = GetNewNandController();
    ShowNandControllerContent(nandController);
    FreeNandController(&nandController);
    return 0;
}