#include "gdt.h"

void gdt_set_gate(u8 num, u64 base, u64 limit, u8 type, u8 s, u8 dpl, u8 p, u8 gran) {
    gdt.entries[num].base_low = (base & 0xFFFF);
    gdt.entries[num].base_middle = (base >> 16) & 0xFF;
    gdt.entries[num].base_high = (base >> 24) & 0xFF;

    gdt.entries[num].limit_low = (limit & 0xFFFF);
    gdt.entries[num].granularity = (limit >> 16) & 0X0F;

    gdt.entries[num].granularity |= (gran & 0xF0);

    gdt.entries[num].type = type;
    gdt.entries[num].s = s;
    gdt.entries[num].dpl = dpl;
    gdt.entries[num].p = p;
}

void write_tss(int32_t num, u16 ss0, uint32_t esp0) {
    tss_entry_t *tss = &gdt.tss;
    uintptr_t base = (uintptr_t)tss;
    uintptr_t limit = base + sizeof *tss;

    // Add the TSS descriptor to the GDT
    gdt_set_gate(num, base, limit, 0x9, 0, 3, 1, 0x00);

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

    gdt_set_gate(0, 0, 0, 0, 0, 0, 0, 0);               // NULL segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0xA, 1, 0, 1, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x2, 1, 0, 1, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xA, 1, 3, 1, 0xCF); // User code
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0x2, 1, 3, 1, 0xCF); // User data
    write_tss(5, 0x10, 0x0);
    gdt_set_gate(6, 0, 0xFFFFFFFF, 0x2, 1, 3, 1, 0xCF);

    gdt_flush((uintptr_t)gdtp);
    tss_flush();
}

