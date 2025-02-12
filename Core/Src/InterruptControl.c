#include "InterruptControl.h"

void IRQ_enable(uint8_t pin_number)
{
	HAL_NVIC_EnableIRQ(pin_number);
}

void IRQ_disable(uint8_t pin_number)
{
	HAL_NVIC_DisableIRQ(pin_number);
}

void IRQ_clearPending(uint8_t pin_number)
{
	HAL_NVIC_ClearPendingIRQ(pin_number);
}

void IRQ_setPending(uint8_t pin_number)
{
	HAL_NVIC_SetPendingIRQ(pin_number);
}

// HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
