#include "idt.h"
#include "../pic.h"
#include "interrupts.h"

static idt_t idt;

void idt_set_gate(u8 num, idt_gate_t isr, u16 cs, u8 flags) {
    idt.entries[num].isr_low = ((uintptr_t)isr & 0xFFFF);
    idt.entries[num].isr_high = ((uintptr_t)isr >> 16) & 0xFFFF;
    idt.entries[num].cs = cs;
    idt.entries[num].reserved = 0;
    idt.entries[num].flags = flags;
}

void idt_install() {
    idt.idtr.limit = (sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS) - 1;
    idt.idtr.base = (u32)&idt.entries[0];
    memset(&idt.entries[0], 0, sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS);

    pic_remap();
    pic_unmask_all();

    // 0x08 - kernel CS segment
    // 0x8E - Present, DPL = 0, GateType = 0xE(32 bit trap gate)
    idt_set_gate(0, interrupt_handler0, 0x08, 0x8E);
    idt_set_gate(1, interrupt_handler1, 0x08, 0x8E);
    idt_set_gate(2, interrupt_handler2, 0x08, 0x8E);
    idt_set_gate(3, interrupt_handler3, 0x08, 0x8E);
    idt_set_gate(4, interrupt_handler4, 0x08, 0x8E);
    idt_set_gate(5, interrupt_handler5, 0x08, 0x8E);
    idt_set_gate(6, interrupt_handler6, 0x08, 0x8E);
    idt_set_gate(7, interrupt_handler7, 0x08, 0x8E);
    idt_set_gate(8, interrupt_handler8, 0x08, 0x8E);
    idt_set_gate(9, interrupt_handler9, 0x08, 0x8E);
    idt_set_gate(10, interrupt_handler10, 0x08, 0x8E);
    idt_set_gate(11, interrupt_handler11, 0x08, 0x8E);
    idt_set_gate(12, interrupt_handler12, 0x08, 0x8E);
    idt_set_gate(13, interrupt_handler13, 0x08, 0x8E);
    idt_set_gate(14, interrupt_handler14, 0x08, 0x8E);
    idt_set_gate(15, interrupt_handler15, 0x08, 0x8E);
    idt_set_gate(16, interrupt_handler16, 0x08, 0x8E);
    idt_set_gate(17, interrupt_handler17, 0x08, 0x8E);
    idt_set_gate(18, interrupt_handler18, 0x08, 0x8E);
    idt_set_gate(19, interrupt_handler19, 0x08, 0x8E);
    idt_set_gate(20, interrupt_handler20, 0x08, 0x8E);
    idt_set_gate(21, interrupt_handler21, 0x08, 0x8E);
    idt_set_gate(22, interrupt_handler22, 0x08, 0x8E);
    idt_set_gate(23, interrupt_handler23, 0x08, 0x8E);
    idt_set_gate(24, interrupt_handler24, 0x08, 0x8E);
    idt_set_gate(25, interrupt_handler25, 0x08, 0x8E);
    idt_set_gate(26, interrupt_handler26, 0x08, 0x8E);
    idt_set_gate(27, interrupt_handler27, 0x08, 0x8E);
    idt_set_gate(28, interrupt_handler28, 0x08, 0x8E);
    idt_set_gate(29, interrupt_handler29, 0x08, 0x8E);
    idt_set_gate(30, interrupt_handler30, 0x08, 0x8E);
    idt_set_gate(31, interrupt_handler31, 0x08, 0x8E);

    set_interrupt_handler(0, divide_by_zero);
    
    idt_load(&idt.idtr);
}