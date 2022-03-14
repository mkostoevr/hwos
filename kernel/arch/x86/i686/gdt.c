#include <kernel/lib/assert.h>
#include "gdt.h"
#include "../x86.h"

// SDM Vol. 3 Ch. 3.4.5 Segment Descriptors
// Figure 3-8. Segment Descriptor
void gdt_set_gate(u8 num, u64 base, u64 limit, u8 type, u32 flags) {
    gdt.entries[num].d0 = (limit & 0xFFFF) | ((base & 0xFFFF) << 16);
    gdt.entries[num].d1 = (((base  >> 16) & 0xFF) << 0)
                        | (((type)        & 0x0F) << 8)
                        | (((limit >> 16) & 0x0F) << 16)
                        | (((base  >> 24) & 0xFF) << 24)
                        | flags;
}

void write_tss(int32_t num, u16 ss0, uint32_t esp0) {
    tss_entry_t *tss = &gdt.tss;
    uintptr_t base = (uintptr_t)tss;
    uintptr_t limit = base + sizeof *tss;

    // Add the TSS descriptor to the GDT
    gdt_set_gate(num, base, limit, 0x9, SD_D1_DPL_RING3 | SD_D1_PRESENT);

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

    u32 flags = SD_D1_S_CODE_OR_DATA | SD_D1_PRESENT | SD_D1_DB_32BIT_SEGMENT
              | SD_D1_GRANULARITY;

    gdt_set_gate(0, 0, 0, 0, 0); // NULL segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0xA, flags | SD_D1_DPL_RING0); // Code
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x2, flags | SD_D1_DPL_RING0); // Data
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xA, flags | SD_D1_DPL_RING3); // User code
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0x2, flags | SD_D1_DPL_RING3); // User data
    write_tss(5, 0x10, 0x0);
    gdt_set_gate(6, 0, 0xFFFFFFFF, 0x2, flags | SD_D1_DPL_RING3);

    gdt_flush((uintptr_t)gdtp);
    tss_flush();
}

