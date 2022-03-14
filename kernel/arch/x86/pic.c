#include "pic.h"
#include "ports.h"

void pic_mask_all() {
    outb(PIC_MASTER_DAT, 0xFF);
    outb(PIC_SLAVE_DAT, 0xFF);
}

void pic_unmask_all() {
    outb(PIC_MASTER_DAT, 0x00);
    outb(PIC_SLAVE_DAT, 0x00);
}

// Performs PIC remapping
// Offset of controller is a number,
// that controller adds to irq line number before passing it to the cpu.
// Offset must be divisible by 8 because its first 3 bits stand for irq line number.
// We set master offset to 0x20 (32), slave offset to 0x28 (40),
// this done because vectors 0..31 used for cpu exceptions, and 0x20 is 32.
// After that master will give interrupt vectors 32..39, and slave will give 40..47.
// Interrupt vector 34 cannot happen because irq2 is connected with slave controller.
// So, we can receive only 15 external interrupts.
// Its not much, but we also use software interrupts (int instruction),
// because they go directly to the cpu, bypassing pic.
void pic_remap() {
    unsigned char a1 = inb(PIC_MASTER_DAT);
    unsigned char a2 = inb(PIC_SLAVE_DAT);

    // Start the initialization sequence (in cascade mode)
    outb(PIC_MASTER_CMD, ICW1_INIT | ICW1_ICW4);
    wait_few_usecs();
    outb(PIC_SLAVE_CMD, ICW1_INIT | ICW1_ICW4);
    wait_few_usecs();

    // ICW2: set Master PIC vector offset to 32
    outb(PIC_MASTER_DAT, 0x20);
    wait_few_usecs();

    // ICW2: set Slave PIC vector offset to 40
    outb(PIC_SLAVE_DAT, 0x28);
    wait_few_usecs();

    // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    outb(PIC_MASTER_DAT, 0x04);
    wait_few_usecs();

    // ICW3: tell Slave PIC its cascade identity (0000 0010)
    outb(PIC_SLAVE_DAT, 0x02);
    wait_few_usecs();

    // 8086/88 (MCS-80/85) mode
    outb(PIC_MASTER_DAT, ICW4_8086);
    wait_few_usecs();
    outb(PIC_SLAVE_DAT, ICW4_8086);
    wait_few_usecs();

    // Restore saved masks
    outb(PIC_MASTER_DAT, a1);
    outb(PIC_SLAVE_DAT, a2);
}

void pic_initialize() {
    pic_remap();
    pic_unmask_all();
}
