#ifndef SYSCLK_H
#define SYSCLK_H

#include "stm32f103reg.h"

void sysclk_init(void);
uint32_t millis(void);
void delay_ms(uint32_t ms);

#endif /* SYSCLK_H */