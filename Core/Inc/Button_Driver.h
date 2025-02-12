#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#include <stdbool.h>
#include "InterruptControl.h"

// user button - port GPIOA 0 (PA0)

#define USER_BUTTON_PORT 		0
#define USER_BUTTON_PIN 		0
#define USER_BUTTON_PRESSED 	1
#define USER_BUTTON_NOT_PRESSED 0
#define GPIOG_OFFSET			6

void buttonInit();

void clockEnable();

bool buttonPressed();

void initializeInterruptMode();

#endif
