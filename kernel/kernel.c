/*
    NekOS
    Generic main kernel code
*/
#include "kernel.h"

int kmain() {
    printk_dup(FDO_KERNEL "%wHello from kmain()%y\n", LIGHT_GREEN);

    // infinite loop. volatile preserves from optimizing out.
    volatile int a = 1;
    (void)a;
    while (1) {
        asm volatile ("hlt");
        a = 0;
    }
    
    return 0;
}
