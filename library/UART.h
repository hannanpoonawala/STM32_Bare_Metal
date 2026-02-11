#ifndef UART_H
#define UART_H

#include "stm32f103reg.h"

void usart1_begin(uint32_t baudrate);
uint8_t usart1_available(void);
char usart1_read(void);
void usart1_write(char c);
void usart1_print(char *str);
void usart1_println(char *str);
void usart1_print_int(int32_t num);
void usart1_print_hex(uint32_t num);
void usart1_flush(void);

#endif // UART_H