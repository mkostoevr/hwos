#include "com.h"
#include "ports.h"

int com1_initialize() {
    // Enable interrupts
    outb(PORT_COM1_IER, PORT_COM_IER_RECEIVED_DATA_AVAILABLE
                      | PORT_COM_IER_TRANSMITTER_HOLDING_REGISTER_EMPTY
                      | PORT_COM_IER_RECEIVER_LINE_STATUS_REGISTER_CHANGE
                      | PORT_COM_IER_MODEM_STATUS_REGISTER_CHANGE);
    // Change speed (set divisor to 3)
    outb(PORT_COM1_LCR, PORT_COM_LCR_DLAB_ON);
    outb(PORT_COM1_DLL, 3);
    outb(PORT_COM1_DLM, 0);
    // 8 bits, no parity, one stop bit
    outb(PORT_COM1_LCR, PORT_COM_LCR_8_DATA_BITS
                      | PORT_COM_LCR_NO_PARITY
                      | PORT_COM_LCR_1_STOP_BIT);
    // Enable FIFO, clear them, with 1 byte threshold
    outb(PORT_COM1_FCR, PORT_COM_FCR_ENABLE_FIFOS
                      | PORT_COM_FCR_CLEAR_RX_FIFO
                      | PORT_COM_FCR_CLEAR_TX_FIFO
                      | PORT_COM_FCR_FIFO_ITL_1);
    // IRQs enabled, RTS/DSR set
    outb(PORT_COM1_MCR, PORT_COM_MCR_DATA_TERMINAL_READY
                      | PORT_COM_MCR_REQUEST_TO_SEND
                      | PORT_COM_MCR_AUXILIARY_OUTPUT_2);
    // Set in loopback mode, test the serial chip
    outb(PORT_COM1_MCR, PORT_COM_MCR_LOOPBACK_MODE
                      | PORT_COM_MCR_REQUEST_TO_SEND
                      | PORT_COM_MCR_AUXILIARY_OUTPUT_1
                      | PORT_COM_MCR_AUXILIARY_OUTPUT_2);
    // Test serial chip (send bytr 0xAE and check if serial returns same byte)
    outb(PORT_COM1_THR, 0xAE);

    // Check if serial is faulty (i.e: not same byte as sent)
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
    return 1;
}

int com1_is_transmit_empty() {
   return inb(PORT_COM1_LSR) & 0x20;
}

int com1_is_data_ready() {
   return inb(PORT_COM1_LSR) & 0x1;
}

void com1_write_char(char a) {
   while (com1_is_transmit_empty() == 0);
   outb(PORT_COM1_RBR, a);
}

char com1_read_char() {
    while (com1_is_data_ready() == 0);
    return inb(PORT_COM1_RBR);
}
