#include "../x86.h"
#include "gdt.h"

.section .text
.align 4

.global gdt_flush
.type gdt_flush, @function

gdt_flush:
    mov 4(%esp), %eax
    lgdt (%eax)
    mov $SS(GDT_KERNEL_DATA), %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %ss
    mov %ax, %gs
    ljmp $SS(GDT_KERNEL_CODE), $.flush
.flush:
    ret
