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

u8 inb(u16 port);
u16 inw(u16 port);
u32 inl(u16 port);
void outb(u16 port, u8 val);
void outw(u16 port, u16 val);
void outl(u16 port, u32 val);
void insl(u16 port, void *buffer, size_t count);

void wait_few_usecs();
