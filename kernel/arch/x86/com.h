#pragma once

// Read on DLAB = 0: Receiver Buffer Register
#define PORT_COM1_RBR (PORT_COM1 + 0)

// Write on DLAB = 0: Transmitter Holding Register
#define PORT_COM1_THR (PORT_COM1 + 0)

// Read/write on DLAB = 0: Interrupt Enable Register
#define PORT_COM1_IER (PORT_COM1 + 1)

#define PORT_COM_IER_RECEIVED_DATA_AVAILABLE              0x01
#define PORT_COM_IER_TRANSMITTER_HOLDING_REGISTER_EMPTY   0x02
#define PORT_COM_IER_RECEIVER_LINE_STATUS_REGISTER_CHANGE 0x04
#define PORT_COM_IER_MODEM_STATUS_REGISTER_CHANGE         0x08
#define PORT_COM_IER_SLEEP_MODE                           0x10 // 16750 only
#define PORT_COM_IER_LOW_POWER_MODE                       0x20 // 16750 only
#define PORT_COM_IER_RSVD0                                0x40 // Reserved
#define PORT_COM_IER_RSVD1                                0x80 // Reserved

// Read/write on DLAB = 1: Divisor Latch LSB
#define PORT_COM1_DLL (PORT_COM1 + 0)

// Read/write on DLAB = 1: Divisor Latch MSB
#define PORT_COM1_DLM (PORT_COM1 + 1)

// Read: Interrupt Identification Register
#define PORT_COM1_IIR (PORT_COM1 + 2)

#define PORT_COM_IIR_INTERRUPT_PENDING(iir) ((iir & 0x01) == 0x00) // xxxxxxx0
#define PORT_COM_IIR_MSR_CHANGE(iir)        ((iir & 0x0E) == 0x00) // xxxx000x
#define PORT_COM_IIR_THR_EMPTY(iir)         ((iir & 0x0E) == 0x02) // xxxx001x
#define PORT_COM_IIR_DATA_AVAIL(iir)        ((iir & 0x0E) == 0x04) // xxxx010x
#define PORT_COM_IIR_LSR_CHANGE(iir)        ((iir & 0x0E) == 0x06) // xxxx011x
#define PORT_COM_IIR_CHAR_TIMEOUT(iir)      ((iir & 0x0E) == 0x0c) // xxxx110x
#define PORT_COM_IIR_RSVD0(iir)             ((iir & 0x10) == 0x00) // xxx0xxxx
#define PORT_COM_IIR_RSVD1(iir)             ((iir & 0x20) == 0x00) // xx0xxxxx
#define PORT_COM_IIR_64B_FIFO_ENABLED(iir)  ((iir & 0x20) == 0x20) // xx1xxxxx
#define PORT_COM_IIR_NO_FIFO(iir)           ((iir & 0xc0) == 0x00) // 00xxxxxx
#define PORT_COM_IIR_UNUSABLE_FIFO(iir)     ((iir & 0xc0) == 0x40) // 01xxxxxx
#define PORT_COM_IIR_FIFO_ENABLED(iir)      ((iir & 0xc0) == 0xc0) // 11xxxxxx

// Write: FIFO Control Register
#define PORT_COM1_FCR (PORT_COM1 + 2)

#define PORT_COM_FCR_DISABLE_FIFOS     0x00 // xxxxxxx0
#define PORT_COM_FCR_ENABLE_FIFOS      0x01 // xxxxxxx1
#define PORT_COM_FCR_CLEAR_RX_FIFO     0x02 // xxxxxx1x
#define PORT_COM_FCR_CLEAR_TX_FIFO     0x04 // xxxxx1xx
#define PORT_COM_FCR_SELECT_DMA_MODE_0 0x00 // xxxx0xxx
#define PORT_COM_FCR_SELECT_DMA_MODE_1 0x08 // xxxx1xxx
#define PORT_COM_FCR_RSVD0             0x00 // xxx0xxxx
#define PORT_COM_FCR_RSVD1             0x00 // xx0xxxxx
#define PORT_COM_FCR_ENABLE_64B_FIFO   0x20 // xx1xxxxx
#define PORT_COM_FCR_FIFO_ITL_1        0x00 // 00xxxxxx
#define PORT_COM_FCR_FIFO_ITL_4        0x40 // 01xxxxxx
#define PORT_COM_FCR_FIFO_ITL_8        0x80 // 10xxxxxx
#define PORT_COM_FCR_FIFO_ITL_14       0xc0 // 11xxxxxx

// Line Control Register
#define PORT_COM1_LCR (PORT_COM1 + 3)

#define PORT_COM_LCR_5_DATA_BITS   0x00 // xxxxxx00
#define PORT_COM_LCR_6_DATA_BITS   0x01 // xxxxxx01
#define PORT_COM_LCR_7_DATA_BITS   0x02 // xxxxxx10
#define PORT_COM_LCR_8_DATA_BITS   0x03 // xxxxxx11
#define PORT_COM_LCR_1_STOP_BIT    0x00 // xxxxx0xx
#define PORT_COM_LCR_2_STOP_BITS   0x04 // xxxxx1xx
#define PORT_COM_LCR_NO_PARITY     0x00 // xxxx0xxx
#define PORT_COM_LCR_ODD_PARITY    0x08 // xx001xxx
#define PORT_COM_LCR_EVEN_PARITY   0x18 // xx011xxx
#define PORT_COM_LCR_HIGH_PARITY   0x28 // xx101xxx
#define PORT_COM_LCR_LOW_PARITY    0x38 // xx111xxx
#define PORT_COM_LCR_SIGBREAK_OFF  0x00 // x0xxxxxx
#define PORT_COM_LCR_SIGBREAK_ON   0x40 // x1xxxxxx
#define PORT_COM_LCR_DLAB_OFF      0x00 // 0xxxxxxx
#define PORT_COM_LCR_DLAB_ON       0x80 // 1xxxxxxx

// Modem Control Register
#define PORT_COM1_MCR (PORT_COM1 + 4)

#define PORT_COM_MCR_DATA_TERMINAL_READY 0x01
#define PORT_COM_MCR_REQUEST_TO_SEND     0x02
#define PORT_COM_MCR_AUXILIARY_OUTPUT_1  0x04
#define PORT_COM_MCR_AUXILIARY_OUTPUT_2  0x08
#define PORT_COM_MCR_LOOPBACK_MODE       0x10
#define PORT_COM_MCR_AUTOFLOW_CONTROL    0x20
#define PORT_COM_MCR_RSVD0               0x40
#define PORT_COM_MCR_RSVD1               0x80

// Line Status Register
#define PORT_COM1_LSR (PORT_COM1 + 5)

#define PORT_COM_LSR_DATA_AVAILABLE                0x01
#define PORT_COM_LSR_OVERRUN_ERROR                 0x02
#define PORT_COM_LSR_PARITY_ERROR                  0x04
#define PORT_COM_LSR_FRAMING_ERROR                 0x08
#define PORT_COM_LSR_BREAK_SIGNAL                  0x10
#define PORT_COM_LSR_THR_IS_EMPTY                  0x20
#define PORT_COM_LSR_THR_IS_EMPTY_AND_LINE_IS_IDLE 0x40
#define PORT_COM_LSR_ERRORNOUS_DATA_IN_FIFO        0x80

// Modem Status Register
#define PORT_COM1_MSR (PORT_COM1 + 6)

#define PORT_COM_MSR_CHANGE_IN_CLEAR_TO_SEND      0x01
#define PORT_COM_MSR_CHANGE_IN_DATA_SET_READY     0x02
#define PORT_COM_MSR_TRAILING_ENGE_RING_INDOCATOR 0x04
#define PORT_COM_MSR_CHANGE_IN_CARRIER_DETECT     0x08
#define PORT_COM_MSR_CLEAR_TO_SEND                0x10
#define PORT_COM_MSR_DATA_SET_READY               0x20
#define PORT_COM_MSR_RING_INDICATOR               0x40
#define PORT_COM_MSR_CARRIER_DETECT               0x80

// SCratch Register
#define PORT_COM1_SCR (PORT_COM1 + 7)

int com1_is_transmit_empty();
int com1_is_data_ready();
void com1_write_char(char a);
char com1_read_char();
