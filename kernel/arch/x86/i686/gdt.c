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

    gdt_set_gate(GDT_NULL,        0x00000000, 0x00000000, 0);
    gdt_set_gate(GDT_KERNEL_CODE, ADDR32_MIN, ADDR32_MAX, flags | ring0 | code);
    gdt_set_gate(GDT_KERNEL_DATA, ADDR32_MIN, ADDR32_MAX, flags | ring0 | data);
    gdt_set_gate(GDT_USER_CODE,   ADDR32_MIN, ADDR32_MAX, flags | ring3 | code);
    gdt_set_gate(GDT_USER_DATA,   ADDR32_MIN, ADDR32_MAX, flags | ring3 | data);

    gdt_flush((uintptr_t)gdtp);
}
