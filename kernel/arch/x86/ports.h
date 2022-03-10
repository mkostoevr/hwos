#pragma once

#include <kernel/types.h>

#define PORT_COM1 0x3F8
#define PORT_COM1_DATA (PORT_COM1 + 0)
#define PORT_COM1_INERRUPT_ENABLE (PORT_COM1 + 1)
#define PORT_COM1_INERRUPT_IDENTIFICATION (PORT_COM1 + 2)
#define PORT_COM1_LINE_CONTROL (PORT_COM1 + 3)
#define PORT_COM1_MODEM_CONTROL (PORT_COM1 + 4)
#define PORT_COM1_LINE_STATUS (PORT_COM1 + 5)
#define PORT_COM1_MODEM_STATUS (PORT_COM1 + 6)
#define PORT_COM1_SCRATCH (PORT_COM1 + 7)

#define PORT_PCI_CONFIG_SPACE_ADDRESS 0xCF8
#define PORT_PCI_CONFIG_SPACE_DATA 0xCFC

static inline u8 inb(u16 port) {
    u8 ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

static inline u16 inw(u16 port) {
    u16 ret;
    asm volatile ( "inw %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

static inline u32 inl(u16 port) {
    u32 ret;
    asm volatile ( "inl %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

static inline void outb(u16 port, u8  val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline void outw(u16 port, u16 val) {
    asm volatile ( "outw %0, %1" : : "a"(val), "Nd"(port) );
}

static inline void outl(u16 port, u32 val) {
    asm volatile ( "outl %0, %1" : : "a"(val), "Nd"(port) );
}

static inline void insl(u16 port, void *buffer, size_t count) {
    asm volatile ("cld; rep; insl" :: "D" (buffer), "d" (port), "c" (count));
}

// It does nothing byt takes a few nanoseconds
static inline void io_wait() {
    outb(0x80, 0);
}

static inline int com1_is_transmit_empty() {
   return inb(PORT_COM1_LINE_STATUS) & 0x20;
}

static inline int com1_is_data_ready() {
   return inb(PORT_COM1_LINE_STATUS) & 0x1;
}

static inline void com1_write_char(char a) {
   while (com1_is_transmit_empty() == 0);
   outb(PORT_COM1_DATA, a);
}

static inline char com1_read_char() {
    while (com1_is_data_ready() == 0);
    return inb(PORT_COM1_DATA);
}

