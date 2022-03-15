#include "../x86.h"

.section .text
.align 4

.global gdt_flush
.type gdt_flush, @function

gdt_flush:
    mov 4(%esp), %eax
    lgdt (%eax)
    mov $SS(2), %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %ss
    mov %ax, %gs
    ljmp $SS(1), $.flush
.flush:
    ret
