#include <kernel/lib/assert.h>
#include "gdt.h"
#include "../x86.h"

// SDM Vol. 3 Ch. 3.4.5 Segment Descriptors
// Figure 3-8. Segment Descriptor
void gdt_set_gate(u8 num, u64 base, u64 limit, u32 flags) {
    gdt.entries[num].d0 = (limit & 0xFFFF) | ((base & 0xFFFF) << 16);
    gdt.entries[num].d1 = (((base  >> 16) & 0xFF) << 0)
                        | (((limit >> 16) & 0x0F) << 16)
                        | (((base  >> 24) & 0xFF) << 24)
                        | flags;
}

void write_tss(int32_t num) {
    tss_entry_t *tss = &gdt.tss;
    uintptr_t base = (uintptr_t)tss;
    uintptr_t limit = base + sizeof *tss;

    // Add the TSS descriptor to the GDT
    gdt_set_gate(num, base, limit, SD_D1_TYPE_SYSTEM_32BIT_TSS_AVAILABLE
                                 | SD_D1_DPL_RING3
                                 | SD_D1_PRESENT);

    memset(tss, 0x0, sizeof *tss);

    tss->ss0 = SS(2) | SS_RPL_RING0;
    tss->esp0 = 0;
    tss->cs = SS(1) | SS_RPL_RING3;
    tss->ss = SS(2) | SS_RPL_RING3;
    tss->ds = SS(2) | SS_RPL_RING3;
    tss->es = SS(2) | SS_RPL_RING3;
    tss->fs = SS(2) | SS_RPL_RING3;
    tss->gs = SS(2) | SS_RPL_RING3;

    tss->iomap_base = sizeof *tss;
}

void gdt_install() {
    gdt_pointer_t *gdtp = &gdt.pointer;
    gdtp->limit = sizeof gdt.entries - 1;
    gdtp->base = (uintptr_t)&gdt.entries[0];

    u32 flags = SD_D1_S_CODE_OR_DATA | SD_D1_PRESENT | SD_D1_DB_32BIT_SEGMENT
              | SD_D1_GRANULARITY;
    u32 ring3 = SD_D1_DPL_RING3;
    u32 ring0 = SD_D1_DPL_RING0;
    u32 code = SD_D1_TYPE_CODE | SD_D1_TYPE_CODE_R;
    u32 data = SD_D1_TYPE_DATA | SD_D1_TYPE_DATA_W;

    gdt_set_gate(0, 0, 0, 0); // NULL segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, flags | ring0 | code);
    gdt_set_gate(2, 0, 0xFFFFFFFF, flags | ring0 | data);
    gdt_set_gate(3, 0, 0xFFFFFFFF, flags | ring3 | code);
    gdt_set_gate(4, 0, 0xFFFFFFFF, flags | ring3 | data);
    write_tss(5);
    gdt_set_gate(6, 0, 0xFFFFFFFF, flags | ring3 | data);

    gdt_flush((uintptr_t)gdtp);
    tss_flush();
}

