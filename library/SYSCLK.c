#include "SYSCLK.h"

static volatile uint32_t _millis = 0;

void SysTick_Handler(void)
{
    _millis++;
}

void sysclk_init(void)
{
    /* 1. Configure Flash: 2 wait states + prefetch for 72 MHz */
    FLASH->ACR = FLASH_LATENCY_2WS | FLASH_PRFTBE;
    
    /* 2. Enable HSE and wait for ready */
    RCC->CR |= RCC_CR_HSEON;
    uint32_t timeout = 0x5000;
    while (!(RCC->CR & RCC_CR_HSERDY) && timeout--);

    if (!(RCC->CR & RCC_CR_HSERDY)) {
        // HSE failed - fallback to HSI or handle error
        return; // Or use HSI instead
    }
    
    /* 3. Configure prescalers: AHB=72MHz, APB1=36MHz, APB2=72MHz */
    RCC->CFGR &= ~(0xF << 4 | 0x7 << 8 | 0x7 << 11);  /* Clear HPRE, PPRE1, PPRE2 */
    RCC->CFGR |= RCC_HPRE_DIV1 | RCC_PPRE1_DIV2 | RCC_PPRE2_DIV1;
    
    /* 4. Configure PLL: HSE × 9 = 72 MHz */
    RCC->CFGR &= ~(0x1 << 16 | 0xF << 18);  /* Clear PLLSRC, PLLMUL */
    RCC->CFGR |= RCC_PLLSRC_HSE | RCC_PLLMUL_9;
    
    /* 5. Enable PLL and wait for ready */
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));
    
    /* 6. Switch SYSCLK to PLL */
    RCC->CFGR &= ~0x3;  /* Clear SW */
    RCC->CFGR |= RCC_SYSCLK_PLL;
    while ((RCC->CFGR & (0x3 << 2)) != (RCC_SYSCLK_PLL << 2));  /* Wait for SWS */
    
    /* 7. Configure SysTick: 1 ms @ 72 MHz */
    SYSTICK->RVR = 72000 - 1;
    SYSTICK->CVR = 0;
    SYSTICK->CSR = SYSTICK_CLKSOURCE | SYSTICK_TICKINT | SYSTICK_ENABLE;
}

uint32_t millis(void)
{
    return _millis;
}

void delay_ms(uint32_t ms)
{
    uint32_t start = millis();
    while ((millis() - start) < ms);
}