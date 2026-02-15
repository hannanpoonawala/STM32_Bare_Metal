#ifndef UART_H
#define UART_H

#include "stm32f103reg.h"

#define UART_RX_BUF_SIZE 128

// Initialization and Control
void usart1_begin(uint32_t baudrate);
uint8_t usart1_available(void);
char usart1_read(void);
void usart1_flush(void);

// Transmission
void usart1_write(char c);
void usart1_print(char *str);
void usart1_println(char *str);

#endif // UART_H