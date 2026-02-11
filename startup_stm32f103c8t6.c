/* Startup code for STM32F103C8T6 */

#include <stdint.h>

#define STACK_START 0x20005000  /* 20KB RAM */

/* Function prototypes */
void Reset_Handler(void);
void Default_Handler(void);

/* External symbols from linker script */
extern uint32_t _sdata, _edata, _sidata;
extern uint32_t _sbss, _ebss;
extern int main(void);

/* Weak aliases for exception handlers */
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
/* SysTick_Handler is defined in systick.c, so don't alias it */
void SysTick_Handler(void);

/* Vector table */
uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    STACK_START,                    /* Initial stack pointer */
    (uint32_t)Reset_Handler,        /* Reset Handler */
    (uint32_t)NMI_Handler,          /* NMI Handler */
    (uint32_t)HardFault_Handler,    /* Hard Fault Handler */
    (uint32_t)MemManage_Handler,    /* MPU Fault Handler */
    (uint32_t)BusFault_Handler,     /* Bus Fault Handler */
    (uint32_t)UsageFault_Handler,   /* Usage Fault Handler */
    0,                              /* Reserved */
    0,                              /* Reserved */
    0,                              /* Reserved */
    0,                              /* Reserved */
    (uint32_t)SVC_Handler,          /* SVCall Handler */
    (uint32_t)DebugMon_Handler,     /* Debug Monitor Handler */
    0,                              /* Reserved */
    (uint32_t)PendSV_Handler,       /* PendSV Handler */
    (uint32_t)SysTick_Handler,      /* SysTick Handler */
    /* Add more interrupt handlers as needed */
};

void Reset_Handler(void)
{
    /* Copy data section from flash to RAM */
    volatile uint8_t *src = (volatile uint8_t*)&_sidata;
    volatile uint8_t *dst = (volatile uint8_t*)&_sdata;
    
    while (dst < (volatile uint8_t*)&_edata) {
        *dst++ = *src++;
    }

    /* Zero fill the bss section */
    dst = (volatile uint8_t*)&_sbss;
    
    while (dst < (volatile uint8_t*)&_ebss) {
        *dst++ = 0;
    }

    /* Call main */
    main();

    /* Infinite loop if main returns */
    while (1);
}

void Default_Handler(void)
{
    /* Infinite loop */
    while (1);
}