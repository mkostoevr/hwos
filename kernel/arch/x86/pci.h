#pragma once

#include <kernel/types.h>

u16 pci_legacy_read_16(u8 bus, u8 device, u8 function, u8 offset);

void lspci();
