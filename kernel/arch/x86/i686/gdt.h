#pragma once

#define GDT_NULL        0
#define GDT_KERNEL_CODE 1
#define GDT_KERNEL_DATA 2
#define GDT_USER_CODE   3
#define GDT_USER_DATA   4

#ifndef __ASSEMBLER__

#include <kernel/lib/string.h>
#include <kernel/types.h>

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
} gdt __attribute__((used));

void gdt_flush(uintptr_t);

void gdt_set_gate(u8 num, u64 base, u64 limit, u32 flags);
void write_tss(int32_t num);
void gdt_install();

#endif
