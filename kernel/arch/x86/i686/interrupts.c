#include "interrupts.h"
#include "../pic.h"
#include "../ports.h"
#include <kernel/io/fdo.h>

interrupt_handler_t interrupt_handler_table[256];

void set_interrupt_handler(u8 num, interrupt_handler_t handler) {
    interrupt_handler_table[num] = handler;
}

void common_interrupt_handler(interrupt_ctx_t regs) {
    if (interrupt_handler_table[regs.int_num]) {
        interrupt_handler_table[regs.int_num](regs);
    }
    // if interrupts goes through PIC we must send End Of Interrupt (EOI) to PIC
    if (regs.int_num >= 32) {
        // if interrupt came from slave PIC, send EOI to it
        if (regs.int_num >= 40) {
            outb(PIC_SLAVE_CMD, PIC_EOI);
        }
        // send EOI to master PIC enyway
        outb(PIC_MASTER_CMD, PIC_EOI);
    }
}

void divide_by_zero(interrupt_ctx_t regs) {
    (void)regs;
    printk_dup(FDO_ARCH_i686 "%wDivide by zero!%y", LIGHT_RED);
    asm("hlt");
}

