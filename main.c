#include "GPIO.h"
#include "SYSCLK.h"
#include "UART.h"

int main(void) {
    // ===== Set TX pin to idle HIGH state FIRST =====
    RCC->APB2ENR |= (1 << 2);  // Enable GPIOA
    
    // Configure PA9 as output push-pull 50MHz
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |= (0x3 << 4);
    
    // Set PA9 HIGH (UART idle state)
    GPIOA->BSRR = (1 << 9);  // Set bit 9 HIGH
    
    // Small delay before clock changes
    for (volatile uint32_t i = 0; i < 10000; i++);

    // Initialize system clock to 72MHz
    sysclk_init();
    
    // Small delay to let power stabilize
    delay_ms(50);
    
    // Initialize USART1 at 115200 baud
    usart1_begin(115200);
    
    // Additional delay for ESP32 UART to stabilize
    delay_ms(50);
    
    // Send startup messages
    usart1_println("========================================");
    usart1_println("STM32F103 Register-Level UART Demo");
    usart1_println("========================================");
    usart1_print("System Clock: ");
    usart1_print_int(72);
    usart1_println(" MHz");
    usart1_print("Baud Rate: ");
    usart1_print_int(115200);
    usart1_println(" bps");
    usart1_println("========================================");
    usart1_println("Type something and I will echo it back!");
    usart1_println("========================================");
    usart1_print("\r\n> ");
    
    while (1) {
        // Check if data has been received
        if (usart1_available()) {
            // Read the received character
            char received = usart1_read();
            
            // Echo the character back
            usart1_write(received);
            
            // If Enter key is pressed, add newline and prompt
            if (received == '\r' || received == '\n') {
                usart1_print("\r\nReceived: ");
                usart1_write(received);
                usart1_print("\r\n> ");
            }
        }
        
        // Small delay to prevent tight polling
        delay_ms(10);
    }
}