#include <page.h>
#include <stdio.h>

int main() {
    int someAddress = 123;
    Page initialPage = GetInitialPage(someAddress);
    
    // Access the values of the returned Page object
    printf("Page status: %d\n", initialPage.status);
    printf("Page address: %d\n", initialPage.address);
    
    return 0;
}