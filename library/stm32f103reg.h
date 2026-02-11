#ifndef STM32F103REG_H
#define STM32F103REG_H

#include <stdint.h>

typedef struct {
    volatile uint32_t CRL, CRH, IDR, ODR, BSRR, BRR, LCKR;
} gpio_t;

typedef struct{
    volatile uint32_t CR, CFGR, CIR, APB2RSTR, APB1RSTR, AHBENR, APB2ENR, APB1ENR, BDCR, CSR;
}rcc_t;

typedef struct {
    volatile uint32_t ACR, KEYR, OPTKEYR, SR, CR, AR, RESERVED, OBR, WRPR;
} flash_t;

typedef struct {
    volatile uint32_t CSR, RVR, CVR, CALIB;
} systick_t;

/* =====================================================
 * GPIO Modes
 * ===================================================== */

typedef enum {
    GPIO_MODE_INPUT_ANALOG,
    GPIO_MODE_INPUT_FLOATING,
    GPIO_MODE_INPUT_PULLUP,
    GPIO_MODE_INPUT_PULLDOWN,

    GPIO_MODE_OUTPUT_10MHZ,
    GPIO_MODE_OUTPUT_2MHZ,
    GPIO_MODE_OUTPUT_50MHZ,

    GPIO_MODE_AF_OUTPUT_10MHZ,
    GPIO_MODE_AF_OUTPUT_2MHZ,
    GPIO_MODE_AF_OUTPUT_50MHZ
} gpio_mode_t;

/* =====================================================
 * GPIO Configuration Register (CRL/CRH) Bits
 * ===================================================== */

typedef enum {
    /* INPUT modes (MODE = 00) */
    GPIOCR_INPUT_ANALOG        = 0x0,  // CNF=00 MODE=00
    GPIOCR_INPUT_FLOATING      = 0x4,  // CNF=01 MODE=00
    GPIOCR_INPUT_PULLUPDOWN    = 0x8,  // CNF=10 MODE=00

    /* OUTPUT 10 MHz (MODE = 01) */
    GPIOCR_OUTPUT_PP_10MHZ     = 0x1,  // CNF=00 MODE=01
    GPIOCR_OUTPUT_OD_10MHZ     = 0x5,  // CNF=01 MODE=01
    GPIOCR_AF_PP_10MHZ         = 0x9,  // CNF=10 MODE=01
    GPIOCR_AF_OD_10MHZ         = 0xD,  // CNF=11 MODE=01

    /* OUTPUT 2 MHz (MODE = 10) */
    GPIOCR_OUTPUT_PP_2MHZ      = 0x2,  // CNF=00 MODE=10
    GPIOCR_OUTPUT_OD_2MHZ      = 0x6,  // CNF=01 MODE=10
    GPIOCR_AF_PP_2MHZ          = 0xA,  // CNF=10 MODE=10
    GPIOCR_AF_OD_2MHZ          = 0xE,  // CNF=11 MODE=10

    /* OUTPUT 50 MHz (MODE = 11) */
    GPIOCR_OUTPUT_PP_50MHZ     = 0x3,  // CNF=00 MODE=11
    GPIOCR_OUTPUT_OD_50MHZ     = 0x7,  // CNF=01 MODE=11
    GPIOCR_AF_PP_50MHZ         = 0xB,  // CNF=10 MODE=11
    GPIOCR_AF_OD_50MHZ         = 0xF   // CNF=11 MODE=11
} gpio_cr_t;

typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH = 1
} gpio_level_t;

/* =====================================================
 * RCC APB2ENR Register Bits
 * ===================================================== */

typedef enum {
    RCC_GPIOAEN = (1 << 2),
    RCC_GPIOBEN = (1 << 3),
    RCC_GPIOCEN = (1 << 4),
    RCC_GPIODEN = (1 << 5),
    RCC_GPIOEEN = (1 << 6),
    RCC_GPIOFEN = (1 << 7),
    RCC_GPIOGEN = (1 << 8),
    RCC_ADC1EN = (1 << 9),
    RCC_ADC2EN = (1 << 10),
    RCC_TIM1EN = (1 << 11),
    RCC_SPI1EN = (1 << 12),
    RCC_TIM8EN = (1 << 13),
    RCC_USART1EN = (1 << 14),
    RCC_ADC3EN = (1 << 15),
}rcc_apb2enr_t;

/* =====================================================
 * RCC CR Register Bits
 * ===================================================== */

typedef enum {
    RCC_CR_HSION    = (1 << 0),
    RCC_CR_HSIRDY   = (1 << 1),
    RCC_CR_HSEON    = (1 << 16),
    RCC_CR_HSERDY   = (1 << 17),
    RCC_CR_HSEBYP   = (1 << 18),
    RCC_CR_CSSON    = (1 << 19),
    RCC_CR_PLLON    = (1 << 24),
    RCC_CR_PLLRDY   = (1 << 25)
} rcc_cr_t;

/* =====================================================
 * RCC CFGR System Clock Switch (SW/SWS)
 * ===================================================== */

typedef enum {
    RCC_SYSCLK_HSI = 0,
    RCC_SYSCLK_HSE = 1,
    RCC_SYSCLK_PLL = 2
} rcc_sysclk_t;

/* =====================================================
 * RCC CFGR Prescalers
 * ===================================================== */

typedef enum {
    RCC_HPRE_DIV1   = (0x0 << 4),
    RCC_HPRE_DIV2   = (0x8 << 4),
    RCC_HPRE_DIV4   = (0x9 << 4),
    RCC_HPRE_DIV8   = (0xA << 4),
    RCC_HPRE_DIV16  = (0xB << 4),
    RCC_HPRE_DIV64  = (0xC << 4),
    RCC_HPRE_DIV128 = (0xD << 4),
    RCC_HPRE_DIV256 = (0xE << 4),
    RCC_HPRE_DIV512 = (0xF << 4)
} rcc_hpre_t;

typedef enum {
    RCC_PPRE1_DIV1  = (0x0 << 8),
    RCC_PPRE1_DIV2  = (0x4 << 8),
    RCC_PPRE1_DIV4  = (0x5 << 8),
    RCC_PPRE1_DIV8  = (0x6 << 8),
    RCC_PPRE1_DIV16 = (0x7 << 8)
} rcc_ppre1_t;

typedef enum {
    RCC_PPRE2_DIV1  = (0x0 << 11),
    RCC_PPRE2_DIV2  = (0x4 << 11),
    RCC_PPRE2_DIV4  = (0x5 << 11),
    RCC_PPRE2_DIV8  = (0x6 << 11),
    RCC_PPRE2_DIV16 = (0x7 << 11)
} rcc_ppre2_t;

/* =====================================================
 * RCC CFGR PLL Configuration
 * ===================================================== */

typedef enum {
    RCC_PLLSRC_HSI_DIV2 = (0 << 16),
    RCC_PLLSRC_HSE      = (1 << 16)
} rcc_pllsrc_t;

typedef enum {
    RCC_PLLMUL_2  = (0x0 << 18),
    RCC_PLLMUL_3  = (0x1 << 18),
    RCC_PLLMUL_4  = (0x2 << 18),
    RCC_PLLMUL_5  = (0x3 << 18),
    RCC_PLLMUL_6  = (0x4 << 18),
    RCC_PLLMUL_7  = (0x5 << 18),
    RCC_PLLMUL_8  = (0x6 << 18),
    RCC_PLLMUL_9  = (0x7 << 18),
    RCC_PLLMUL_10 = (0x8 << 18),
    RCC_PLLMUL_11 = (0x9 << 18),
    RCC_PLLMUL_12 = (0xA << 18),
    RCC_PLLMUL_13 = (0xB << 18),
    RCC_PLLMUL_14 = (0xC << 18),
    RCC_PLLMUL_15 = (0xD << 18),
    RCC_PLLMUL_16 = (0xE << 18)
} rcc_pllmul_t;

/* =====================================================
 * Flash ACR Register
 * ===================================================== */

typedef enum {
    FLASH_LATENCY_0WS = (0 << 0),
    FLASH_LATENCY_1WS = (1 << 0),
    FLASH_LATENCY_2WS = (2 << 0),
    FLASH_PRFTBE      = (1 << 4)
} flash_acr_t;

/* =====================================================
 * SysTick CSR Register
 * ===================================================== */

typedef enum {
    SYSTICK_ENABLE    = (1 << 0),
    SYSTICK_TICKINT   = (1 << 1),
    SYSTICK_CLKSOURCE = (1 << 2),
    SYSTICK_COUNTFLAG = (1 << 16)
} systick_csr_t;

/* =====================================================
 * USART Registers
 * ===================================================== */

typedef struct {
    volatile uint32_t SR;   // Status
    volatile uint32_t DR;   // Data
    volatile uint32_t BRR;  // Baud rate
    volatile uint32_t CR1;  // Control 1
    volatile uint32_t CR2;  // Control 2
    volatile uint32_t CR3;  // Control 3
    volatile uint32_t GTPR; // Guard time and prescaler
} usart_t;

#define USART1 ((usart_t *)0x40013800)
#define USART2 ((usart_t *)0x40004400)
#define USART3 ((usart_t *)0x40004800)
#define UART4  ((usart_t *)0x40004C00)
#define UART5  ((usart_t *)0x40005000)

/* GPIO base addresses */
#define GPIOA ((gpio_t *)0x40010800)
#define GPIOB ((gpio_t *)0x40010C00)
#define GPIOC ((gpio_t *)0x40011000)
#define GPIOD ((gpio_t *)0x40011400)
#define GPIOE ((gpio_t *)0x40011800)
#define GPIOF ((gpio_t *)0x40011C00)
#define GPIOG ((gpio_t *)0x40012000)

/* RCC registers */
#define RCC ((rcc_t *)0x40021000)
#define FLASH   ((flash_t *)0x40022000)
#define SYSTICK ((systick_t *)0xE000E010)



#endif