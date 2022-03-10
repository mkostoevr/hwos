#include "com.h"
#include "ports.h"

int com1_is_transmit_empty() {
   return inb(PORT_COM1_LINE_STATUS) & 0x20;
}

int com1_is_data_ready() {
   return inb(PORT_COM1_LINE_STATUS) & 0x1;
}

void com1_write_char(char a) {
   while (com1_is_transmit_empty() == 0);
   outb(PORT_COM1_DATA, a);
}

char com1_read_char() {
    while (com1_is_data_ready() == 0);
    return inb(PORT_COM1_DATA);
}
