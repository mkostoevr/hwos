#include <kernel/types.h>

#include "../vgatext.h"
#include "../debug.h"
#include "../pci.h"
#include <kernel/libk/assert.h>
#include <kernel/multiboot.h>
#include <kernel/io/fdo.h>
#include <kernel/kernel.h>
#include "gdt.h"
#include "idt.h"

void arch_kmain(struct multiboot* mboot, u32 mboot_magic) {

    printk_log("Hello, World!\n");

    vgatext_init((void *)0xB8000);

    assert(mboot_magic == MULTIBOOT_EAX_MAGIC);

    printk_dup(FDO_ARCH_i686 "Hello from arch_kmain\n");

    gdt_install();
    printk_dup(FDO_ARCH_i686 "GDT installed\n");

    idt_install();
    printk_dup(FDO_ARCH_i686 "IDT installed\n");

    kmain();
}

