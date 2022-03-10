#pragma once

#include <kernel/types.h>

#ifdef __cplusplus
extern "C" {
#endif

u16 pci_legacy_read_16(u8 bus, u8 device, u8 function, u8 offset);

void lspci();

#ifdef __cplusplus
}
#endif
