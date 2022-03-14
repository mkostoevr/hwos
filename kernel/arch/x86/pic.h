#pragma once

#define PIC_MASTER_CMD 0x20
#define PIC_MASTER_DAT 0x21
#define PIC_SLAVE_CMD  0xa0
#define PIC_SLAVE_DAT  0xa1

#define ICW1_ICW4       0x01 // ICW4 (not) needed
#define ICW1_SINGLE     0x02 // Single (cascade) mode
#define ICW1_INTERVAL4  0x04 // Call address interval 4 (8)
#define ICW1_LEVEL      0x08 // Level triggered (edge) mode
#define ICW1_INIT       0x10 // Initialization - required!

#define ICW4_8086       0x01 // 8086/88 (MCS-80/85) mode
#define ICW4_AUTO       0x02 // Auto (normal) EOI
#define ICW4_BUF_SLAVE  0x08 // Buffered mode/slave
#define ICW4_BUF_MASTER 0x0C // Buffered mode/master
#define ICW4_SFNM       0x10 // Special fully nested (not)

#define PIC_EOI 0x20

void pic_mask_all();
void pic_unmask_all();

void pic_remap();
void pic_initialize();
