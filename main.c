#include "GPIO.h"
#include "SYSCLK.h"
#include "UART.h"

int main(void) {
    usart1_begin(115200);
    delay_ms(100);
    
    usart1_println("STM32F103 Ready");
    usart1_print("> ");
    
    while (1) {
        if (usart1_available()) {
            char received = usart1_read();
            usart1_write(received);
            
            if (received == '\r' || received == '\n') {
                usart1_print("\r\n> ");
            }
        }
    }
}