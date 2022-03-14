#pragma once
#include <kernel/lib/string.h>
#include <kernel/types.h>
#include "tss.h"

typedef struct {
    u16 limit_low;
    u16 base_low;
    u8 base_middle;
    u8 type: 4,       // Segment type
       s: 1,          // Descriptor type
       dpl: 2,        // Descriptor privilige level (ring)
       p: 1;          // Segment present
    u8 limit_high: 4,
       avl: 1,        // Available for use by system software
       l: 1,          // 64-bit code segment (IA-32e mode only)
       db: 1,         // Default operation size (0 = 16-bit, 1 = 32-bit)
       g: 1;          // Granularity
    u8 base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
    u16 limit;
    uintptr_t base;
} __attribute__((packed)) gdt_pointer_t;

static struct {
    gdt_entry_t entries[7];
    gdt_pointer_t pointer;
    tss_entry_t tss;
} gdt __attribute__((used));

void gdt_flush(uintptr_t);

void gdt_set_gate(u8 num, u64 base, u64 limit, u8 type, u8 s, u8 dpl, u8 p, u8 avl, u8 l, u8 db, u8 g);
void write_tss(int32_t num, u16 ss0, uint32_t esp0);
void gdt_install();
