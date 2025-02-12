#ifndef INTERRUPTCONTROL_H_
#define INTERRUPTCONTROL_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

#define SHIFT_BIT(x) (1 << x)

#define EXTI0_IRQ_NUMBER 6

void IRQ_enable(uint8_t IRQ_number);

void IRQ_disable(uint8_t IRQ_number);

void IRQ_clearPending(uint8_t IRQ_number);

void IRQ_setPending(uint8_t IRQ_number);

#endif
