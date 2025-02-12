#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include "stm32f4xx_hal.h"


#define RED_LED 14
#define GREEN_LED 13

void LED_Init (uint8_t led);

void Toggle_LED (uint8_t led);

void TurnOffLED (uint8_t led);

void TurnOnLED (uint8_t led);



#endif
