#pragma once

int com1_is_transmit_empty();
int com1_is_data_ready();
void com1_write_char(char a);
char com1_read_char();
