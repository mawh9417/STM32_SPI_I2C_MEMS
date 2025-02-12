#ifndef APPLICATIONCODE_H_
#define APPLICATIONCODE_H_

#include "LED_Driver.h"
#include "Scheduler.h"
#include "Button_Driver.h"
#include "Gyro.h"

#define LENGTH_FIRST_NAME 3

#define NAME 3
#define MAGNIFY_DELAY 25000

#define USE_INTERRUPT_FOR_BUTTON 1

void applicationInit();

void greenLEDInit();

void redLEDInit();

void toggleGreenLED();

void toggleRedLED();

void activateGreenLED();

void activateRedLED();

void deactivateGreenLED();

void deactivateRedLED();

void appDelay(uint32_t t);

void buttonInitApp();

void executeButtonPollingRoutine();

void initializeButtonForInterrupt();

void gyroOn();

void gyroInit();

void gyroGetID();

void gyroPrintTemp();

void gyroRegConfig();

void rebootGyro();

#endif
