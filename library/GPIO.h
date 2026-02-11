#ifndef GPIO_H
#define GPIO_H

#include "stm32f103reg.h"
#include <stdint.h>

/* API */
void gpio_init(rcc_apb2enr_t periph);
void setMode(gpio_t *gpio, uint8_t pin, gpio_mode_t mode);
void digitalWrite(gpio_t *gpio, uint8_t pin, gpio_level_t level);
void toggle(gpio_t *gpio, uint8_t pin);
int digitalRead(gpio_t *gpio, uint8_t pin);

#endif