#include <kernel/types.h>

#include "../x86.h"
#include "../vgatext.h"
#include "../debug.h"
#include "../pci.h"
#include "../com.h"
#include <kernel/lib/assert.h>
#include <kernel/lib/fdo.h>
#include <kernel/kernel.h>
#include "gdt.h"
#include "idt.h"

void arch_kmain() {

    printk_log("Hello, World!\n");

    vgatext_init((void *)0xB8000);

    printk_dup(FDO_ARCH_i686 "Hello from arch_kmain\n");

    gdt_install();
    printk_dup(FDO_ARCH_i686 "GDT installed\n");

    idt_install();
    printk_dup(FDO_ARCH_i686 "IDT installed\n");

    if (!com1_initialize()) {
        printk_dup(FDO_ARCH_i686 "Failed to initialize COM1 serial\n");
    } else {
        printk_dup(FDO_ARCH_i686 "COM1 serial initialized\n");
    }

    kmain();
}

