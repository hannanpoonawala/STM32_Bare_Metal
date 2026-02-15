#include "GPIO.h"
#include "SYSCLK.h"
#include "UART.h"

int main(void) {
    // Initialize USART1 at 115200 baud
    usart1_begin(115200);
    
    // Send startup messages
    usart1_println("STM32F103 USART Echo Example");
    usart1_println("Type something and it will be echoed back:");
    usart1_print("> ");
    
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
    }
}