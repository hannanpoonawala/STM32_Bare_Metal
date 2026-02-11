#include "GPIO.h"
#include "SYSCLK.h"

#include <string.h>

void gpio_init(rcc_apb2enr_t periph) {
    /* GPIO initialization can be added here if needed */
    RCC->APB2ENR |= periph;
}

void setMode(gpio_t *gpio, uint8_t pin, gpio_mode_t mode)
{
    uint32_t shift = (pin % 8) * 4;
    volatile uint32_t *reg = (pin < 8) ? &gpio->CRL : &gpio->CRH;

    *reg &= ~(0xF << shift);

    switch (mode) {

        case GPIO_MODE_INPUT_ANALOG:
            *reg |= (GPIOCR_INPUT_ANALOG << shift);
            break;

        case GPIO_MODE_INPUT_FLOATING:
            *reg |= (GPIOCR_INPUT_FLOATING << shift);
            break;

        case GPIO_MODE_INPUT_PULLUP:
            *reg |= (GPIOCR_INPUT_PULLUPDOWN << shift);
            gpio->ODR |=  (1U << pin);   // pull-up
            break;

        case GPIO_MODE_INPUT_PULLDOWN:
            *reg |= (GPIOCR_INPUT_PULLUPDOWN << shift);
            gpio->ODR &= ~(1U << pin);   // pull-down
            break;

        case GPIO_MODE_OUTPUT_10MHZ:
            *reg |= (GPIOCR_OUTPUT_PP_10MHZ << shift);
            break;

        case GPIO_MODE_OUTPUT_2MHZ:
            *reg |= (GPIOCR_OUTPUT_PP_2MHZ << shift);
            break;

        case GPIO_MODE_OUTPUT_50MHZ:
            *reg |= (GPIOCR_OUTPUT_PP_50MHZ << shift);
            break;

        case GPIO_MODE_AF_OUTPUT_10MHZ:
            *reg |= (GPIOCR_AF_PP_10MHZ << shift);
            break;

        case GPIO_MODE_AF_OUTPUT_2MHZ:
            *reg |= (GPIOCR_AF_PP_2MHZ << shift);
            break;

        case GPIO_MODE_AF_OUTPUT_50MHZ:
            *reg |= (GPIOCR_AF_PP_50MHZ << shift);
            break;

        default:
            /* optional error handling */
            break;
    }
}

void digitalWrite(gpio_t *gpio, uint8_t pin, gpio_level_t level) {
    if (level)
        gpio->BSRR = (1 << pin);
    else
        gpio->BRR = (1 << pin);
}

void toggle(gpio_t *gpio, uint8_t pin) {
    gpio->ODR ^= (1 << pin);
}

int digitalRead(gpio_t *gpio, uint8_t pin) {
    return (gpio->IDR & (1 << pin)) != 0;
}