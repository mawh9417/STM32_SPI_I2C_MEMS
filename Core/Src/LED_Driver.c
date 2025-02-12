#include "LED_Driver.h"

void LED_Init (uint8_t led)
{
	switch(led)
	{
	case RED_LED:
		__HAL_RCC_GPIOG_CLK_ENABLE();
		GPIO_InitTypeDef localStruct = {0};
		localStruct.Pin = RED_LED;
		localStruct.Mode = GPIO_MODE_OUTPUT_PP;
		localStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		localStruct.Pull = GPIO_PULLUP;
		localStruct.Alternate = 0;
		HAL_GPIO_Init(GPIOG, &localStruct);
		break;

	case GREEN_LED:
		__HAL_RCC_GPIOG_CLK_ENABLE();
		GPIO_InitTypeDef localStruct2 = {0};
		localStruct2.Pin = GREEN_LED;
		localStruct2.Mode = GPIO_MODE_OUTPUT_PP;
		localStruct2.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		localStruct2.Pull = GPIO_PULLUP;
		localStruct2.Alternate = 0;
		HAL_GPIO_Init(GPIOG, &localStruct2);
		break;
	}
}

void Toggle_LED (uint8_t led)
{
	switch(led)
		{
		case RED_LED:
			HAL_GPIO_TogglePin(GPIOG, RED_LED);
			break;

		case GREEN_LED:
			HAL_GPIO_TogglePin(GPIOG, GREEN_LED);
			break;
		}
}

void TurnOffLED (uint8_t led)
{
	switch(led)
		{
		case RED_LED:
			HAL_GPIO_WritePin(GPIOG, RED_LED, GPIO_PIN_RESET);
			break;

		case GREEN_LED:
			HAL_GPIO_WritePin(GPIOG, GREEN_LED, GPIO_PIN_RESET);
			break;
		}
}

void TurnOnLED (uint8_t led)
{
	switch(led)
		{
		case RED_LED:
			HAL_GPIO_WritePin(GPIOG, RED_LED, GPIO_PIN_SET);
			break;

		case GREEN_LED:
			HAL_GPIO_WritePin(GPIOG, GREEN_LED, GPIO_PIN_SET);
			break;
		}
}
