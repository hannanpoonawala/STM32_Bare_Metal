#include "UART.h"

void usart1_begin(uint32_t baudrate) {
    // Enable GPIOA and USART1 clocks
    RCC->APB2ENR |= RCC_GPIOAEN | RCC_USART1EN;

    // Configure PA9 (TX) as Alternate Function Push-Pull 50MHz
    GPIOA->CRH &= ~(0xF << 4);  // Clear PA9 configuration bits
    GPIOA->CRH |= GPIOCR_AF_PP_50MHZ << 4;

    // Configure PA10 (RX) as Floating Input
    GPIOA->CRH &= ~(0xF << 8);  // Clear PA10 configuration bits
    GPIOA->CRH |= GPIOCR_INPUT_FLOATING << 8;

    // Calculate and set baud rate (APB2 = 72MHz)
    // BRR = PCLK / baudrate
    if (baudrate == 9600) {
        USART1->BRR = 7500;  // 72MHz / 9600 = 7500
    }
    else if (baudrate == 115200) {
        USART1->BRR = 625;   // 72MHz / 115200 = 625 (0x271)
    }
    else {
        // Generic calculation for other baud rates
        USART1->BRR = 72000000 / baudrate;
    }

    // Enable USART1
    USART1->CR1 |= (1 << 13);  // UE: USART Enable

    // Wait for USART to be ready before enabling transmitter
    // This prevents garbage on the TX line during initialization
    while (!(USART1->SR & (1 << 7)));  // Wait for TXE (Transmit Data Register Empty)

    // Enable Transmitter and Receiver
    USART1->CR1 |= (1 << 3);   // TE: Transmitter Enable
    USART1->CR1 |= (1 << 2);   // RE: Receiver Enable

    // Clear any pending flags by reading SR and DR
    (void)USART1->SR;
    (void)USART1->DR;

    // Wait for Transmission Complete to ensure line is stable
    while (!(USART1->SR & (1 << 6)));  // Wait for TC (Transmission Complete)
}

uint8_t usart1_available(void) {
    // Check if data is available to read
    // RXNE: Read Data Register Not Empty (bit 5)
    return (USART1->SR & (1 << 5)) != 0;
}

char usart1_read(void) {
    // Wait until data is available
    while (!usart1_available());
    
    // Read and return the received data
    return (char)(USART1->DR & 0xFF);
}

void usart1_write(char c) {
    // Wait until TXE (Transmit Data Register Empty) is set
    while (!(USART1->SR & (1 << 7)));
    
    // Write the character to the data register
    USART1->DR = c;
}

void usart1_print(char *str) {
    // Transmit each character in the string
    while (*str) {
        usart1_write(*str++);
    }
}

void usart1_println(char *str) {
    // Print string followed by carriage return and line feed
    usart1_print(str);
    usart1_write('\r');
    usart1_write('\n');
}

void usart1_print_int(int32_t num) {
    char buffer[12];  // Enough for -2147483648 + null terminator
    int i = 0;
    int is_negative = 0;

    // Handle negative numbers
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Handle zero case
    if (num == 0) {
        usart1_write('0');
        return;
    }

    // Convert number to string (reversed)
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Add negative sign if needed
    if (is_negative) {
        usart1_write('-');
    }

    // Print digits in correct order
    while (i > 0) {
        usart1_write(buffer[--i]);
    }
}

void usart1_print_hex(uint32_t num) {
    const char hex_chars[] = "0123456789ABCDEF";
    char buffer[9];  // 8 hex digits + null terminator
    int i;

    usart1_print("0x");

    // Convert to hex string
    for (i = 7; i >= 0; i--) {
        buffer[i] = hex_chars[num & 0xF];
        num >>= 4;
    }
    buffer[8] = '\0';

    // Skip leading zeros
    i = 0;
    while (i < 7 && buffer[i] == '0') {
        i++;
    }

    // Print hex number
    usart1_print(&buffer[i]);
}

void usart1_flush(void) {
    // Wait for transmission to complete
    while (!(USART1->SR & (1 << 6)));  // Wait for TC (Transmission Complete)
}