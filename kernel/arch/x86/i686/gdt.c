#include "gdt.h"

void gdt_set_gate(u8 num, u64 base, u64 limit, u8 access, u8 gran) {
    gdt.entries[num].base_low = (base & 0xFFFF);
    gdt.entries[num].base_middle = (base >> 16) & 0xFF;
    gdt.entries[num].base_high = (base >> 24) & 0xFF;

    gdt.entries[num].limit_low = (limit & 0xFFFF);
    gdt.entries[num].granularity = (limit >> 16) & 0X0F;

    gdt.entries[num].granularity |= (gran & 0xF0);

    gdt.entries[num].access = access;
}

void write_tss(int32_t num, u16 ss0, uint32_t esp0) {
    tss_entry_t *tss = &gdt.tss;
    uintptr_t base = (uintptr_t)tss;
    uintptr_t limit = base + sizeof *tss;

    // Add the TSS descriptor to the GDT
    gdt_set_gate(num, base, limit, 0xE9, 0x00);

    memset(tss, 0x0, sizeof *tss);

    tss->ss0 = ss0;
    tss->esp0 = esp0;
    tss->cs = 0x0b;
    tss->ss = 0x13;
    tss->ds = 0x13;
    tss->es = 0x13;
    tss->fs = 0x13;
    tss->gs = 0x13;

    tss->iomap_base = sizeof *tss;
}

void gdt_install() {
    gdt_pointer_t *gdtp = &gdt.pointer;
    gdtp->limit = sizeof gdt.entries - 1;
    gdtp->base = (uintptr_t)&gdt.entries[0];

    gdt_set_gate(0, 0, 0, 0, 0);                // NULL segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User code
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User data
    write_tss(5, 0x10, 0x0);
    gdt_set_gate(6, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    gdt_flush((uintptr_t)gdtp);
    tss_flush();
}

