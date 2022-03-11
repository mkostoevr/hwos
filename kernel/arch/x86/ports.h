#pragma once

#include <kernel/types.h>

#define PORT_COM1 0x3F8
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
