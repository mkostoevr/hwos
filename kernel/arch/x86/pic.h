#pragma once

#define PIC_MASTER_CMD 0x20
#define PIC_MASTER_DAT 0x21
#define PIC_SLAVE_CMD  0xa0
#define PIC_SLAVE_DAT  0xa1

#define PIC_EOI 0x20

#ifdef __cplusplus
extern "C" {
#endif

void pic_mask_all();
void pic_unmask_all();

void pic_remap();

#ifdef __cplusplus
}
#endif
