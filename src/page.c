#include <page.h>

Page GetInitialPage(int address) {
    Page newPage = {FREE, address};
    return newPage;
}