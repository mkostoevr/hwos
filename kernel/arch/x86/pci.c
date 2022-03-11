#include "pci.h"
#include "ports.h"
#include <kernel/lib/fdo.h>

u16 pci_legacy_read_16(u8 bus, u8 device, u8 function, u8 offset) {
	u32 address;
    u32 lbus  = (u32)bus;
    u32 ldevice = (u32)device;
    u32 lfunction = (u32)function;
    u16 tmp = 0;
 
    // Create configuration address as per Figure 1
    address = (u32)((lbus << 16) | (ldevice << 11) |
              (lfunction << 8) | (offset & 0xFC) | ((u32)0x80000000));
 
    // Write out the address
    outl(PORT_PCI_CONFIG_SPACE_ADDRESS, address);
    // Read in the data
    // (offset & 2) * 8) = 0 will choose the first word of the 32-bit register
    tmp = (u16)((inl(PORT_PCI_CONFIG_SPACE_DATA) >> ((offset & 2) * 8)) & 0xFFFF);
    return tmp;
}

u16 getVendorID(u8 bus, u8 device, u8 function) {
    return pci_legacy_read_16(bus, device, function, 0x0);
}

u16 getDeviceID(u8 bus, u8 device, u8 function) {
    return pci_legacy_read_16(bus, device, function, 0x2);
}

u16 getRevision(u8 bus, u8 device, u8 function) {
    return pci_legacy_read_16(bus, device, function, 0x8);
}

u16 getHeaderType(u8 bus, u8 device, u8 function) {
    return pci_legacy_read_16(bus, device, function, 0xe);
}

const char *vendev2name(u16 vendorID, u16 deviceID) {
    switch (vendorID) {
    case 0x1234:
        switch (deviceID) {
        case 0x1111:
            return "QEMU Virtual Video Controller";
        default:
            return "Undefined QEMU device";
        }
    case 0x8086:
        switch (deviceID) {
        case 0x100e:
            return "Intel 82540EM Gigabit Ethernet controller";
        case 0x1237:
            return "Intel 82440FX CPU to PCI bridge";
        case 0x7000:
            return "Intel 82371SB PIIX3 ISA";
        case 0x7010:
            return "Intel 82371SB PIIX3 IDE";
        case 0x7113:
            return "Intel 82371AB/EB/MB PIIX4 ACPI";
        default:
            return "Undefined Intel device";
        }
    default:
        return "Undefined vendor's device";
    }
}

void checkFunction(u8 bus, u8 device, u8 function) {
    u16 vendorID = getVendorID(bus, device, function);
    u16 deviceID = getDeviceID(bus, device, function);
    const char *name = vendev2name(vendorID, deviceID);
    printk_dup("%x:%x:%x: %x %x (%s)\n",
        bus, device, function,
        vendorID, deviceID, name);
}

void checkDevice(u8 bus, u8 device) {
    u8 function = 0;

    u16 vendorID = getVendorID(bus, device, function);
    if (vendorID == 0xFFFF) return; // Device doesn't exist
    checkFunction(bus, device, function);
    u8 headerType = getHeaderType(bus, device, function);
    if( (headerType & 0x80) != 0) {
        // It's a multi-function device, so check remaining functions
        for (function = 1; function < 8; function++) {
            if (getVendorID(bus, device, function) != 0xFFFF) {
             checkFunction(bus, device, function);
            }
        }
    }
}

void checkAllBuses(void) {
    u16 bus;
    u8 device;

    for (bus = 0; bus < 256; bus++) {
        for (device = 0; device < 32; device++) {
            checkDevice(bus, device);
        }
    }
}

void lspci() {
    printk_dup("PCI:\n");
    checkAllBuses();
}
