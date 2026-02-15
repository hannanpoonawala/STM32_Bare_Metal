#include "UART.h"
#include <stdio.h>

// Static ring buffer for background reception
static volatile char rx_buffer[UART_RX_BUF_SIZE];
static volatile uint16_t rx_head = 0;
static volatile uint16_t rx_tail = 0;

void usart1_begin(uint32_t baudrate) {
    // 1. Enable Clocks: GPIOA (for PA9/PA10) and USART1
    RCC->APB2ENR |= RCC_GPIOAEN | RCC_USART1EN;

    // 2. Configure PA9 (TX) as Alternate Function Push-Pull (50MHz)
    GPIOA->CRH &= ~(0xF << 4); 
    GPIOA->CRH |= (GPIOCR_AF_PP_50MHZ << 4);

    // 3. Configure PA10 (RX) as Input Floating
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |= (GPIOCR_INPUT_FLOATING << 8);

    // 4. Set Baud Rate (Assuming PCLK2 = 72MHz)
    // Formula: BRR = 72,000,000 / baudrate
    USART1->BRR = 72000000 / baudrate;

    // 5. Enable UART, Transmitter, Receiver, and RX-NotEmpty Interrupt
    USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;

    // 6. Enable USART1 Interrupt in NVIC (Vector 37)
    // Using the NVIC Set-Enable Register address directly
    *(volatile uint32_t*)(0xE000E104) |= (1 << (37 - 32));
}

uint8_t usart1_available(void) {
    return (rx_head != rx_tail);
}

char usart1_read(void) {
    if (rx_head == rx_tail) return 0;
    char c = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) % UART_RX_BUF_SIZE;
    return c;
}

void usart1_flush(void) {
    rx_head = rx_tail;
}

void usart1_write(char c) {
    // Wait until Transmit Data Register is empty
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = c;
}

void usart1_print(char *str) {
    while (*str) usart1_write(*str++);
}

void usart1_println(char *str) {
    usart1_print(str);
    usart1_print("\r\n");
}

/**
 * @brief ISR - Triggered automatically when a byte is received
 */
void USART1_IRQHandler(void) {
    // Check if the RXNE (Receive Not Empty) flag is set
    if (USART1->SR & USART_SR_RXNE) {
        char data = (char)USART1->DR;
        uint16_t next = (rx_head + 1) % UART_RX_BUF_SIZE;

        // If buffer isn't full, store the byte
        if (next != rx_tail) {
            rx_buffer[rx_head] = data;
            rx_head = next;
        }
    }
}