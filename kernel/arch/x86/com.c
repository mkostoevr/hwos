#include "com.h"
#include "ports.h"

int com1_initialize() {
    // Initialize the chip:
    // - configure speed (set divisor to 3)
    // - use 8 bits, no parity, one stop bit
    // - enable FIFO, clear them, with 1 byte threshold
    outb(PORT_COM1_LCR, PORT_COM_LCR_DLAB_ON);
    outb(PORT_COM1_DLL, 3);
    outb(PORT_COM1_DLM, 0);
    outb(PORT_COM1_LCR, PORT_COM_LCR_8_DATA_BITS
                      | PORT_COM_LCR_NO_PARITY
                      | PORT_COM_LCR_1_STOP_BIT);
    outb(PORT_COM1_FCR, PORT_COM_FCR_ENABLE_FIFOS
                      | PORT_COM_FCR_CLEAR_RX_FIFO
                      | PORT_COM_FCR_CLEAR_TX_FIFO
                      | PORT_COM_FCR_FIFO_ITL_1);

    // Set in loopback mode and test the serial chip
    outb(PORT_COM1_MCR, PORT_COM_MCR_LOOPBACK_MODE
                      | PORT_COM_MCR_REQUEST_TO_SEND
                      | PORT_COM_MCR_AUXILIARY_OUTPUT_1
                      | PORT_COM_MCR_AUXILIARY_OUTPUT_2);
    outb(PORT_COM1_THR, 0xAE);
    unsigned byte_read = inb(PORT_COM1_RBR);
    if (byte_read != 0xAE) {
        return 0;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(PORT_COM1_MCR, PORT_COM_MCR_DATA_TERMINAL_READY
                      | PORT_COM_MCR_REQUEST_TO_SEND
                      | PORT_COM_MCR_AUXILIARY_OUTPUT_1
                      | PORT_COM_MCR_AUXILIARY_OUTPUT_2);

    // Enable interrupts
    outb(PORT_COM1_IER, PORT_COM_IER_RECEIVED_DATA_AVAILABLE
                      | PORT_COM_IER_RECEIVER_LINE_STATUS_REGISTER_CHANGE
                      | PORT_COM_IER_MODEM_STATUS_REGISTER_CHANGE);

    return 1;
}

int com1_is_transmit_empty() {
   return inb(PORT_COM1_LSR) & 0x20;
}

int com1_is_data_ready() {
   return inb(PORT_COM1_LSR) & 0x1;
}

void com1_write_char_raw(char c) {
    outb(PORT_COM1_RBR, c);
}

void com1_write_char(char a) {
    while (com1_is_transmit_empty() == 0);
    com1_write_char_raw(a);
}

char com1_read_char_raw() {
    return inb(PORT_COM1_RBR);
}

char com1_read_char() {
    while (com1_is_data_ready() == 0);
    return com1_read_char_raw();
}
