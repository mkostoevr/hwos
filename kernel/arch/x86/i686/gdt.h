#pragma once
#include <kernel/lib/string.h>
#include <kernel/types.h>
#include "tss.h"

typedef struct {
    u32 d0;
    u32 d1;
} gdt_entry_t;

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

void gdt_set_gate(u8 num, u64 base, u64 limit, u8 type, u32 flags);
void write_tss(int32_t num, u16 ss0, uint32_t esp0);
void gdt_install();
