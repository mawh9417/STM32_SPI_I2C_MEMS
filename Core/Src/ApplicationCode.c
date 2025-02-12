#include "ApplicationCode.h"

void applicationInit()
{
   //LED_Init(RED_LED);
	//TurnOffLED(GREEN_LED);
	addSchedulerEvent(DELAY_EVENT);
	if (USE_INTERRUPT_FOR_BUTTON != 0)
	{
		initializeInterruptMode();
	}
	if (USE_INTERRUPT_FOR_BUTTON == 0)
	{
		addSchedulerEvent(POLL_EVENT);
		buttonInit();
	}
	gyroInit();
	gyroOn();
}

void greenLEDInit()
{
	LED_Init(GREEN_LED);
}

void redLEDInit()
{
	LED_Init(RED_LED);
}

void toggleGreenLED()
{
	Toggle_LED(GREEN_LED);
}

void toggleRedLED()
{
	Toggle_LED(RED_LED);
}

void activateGreenLED()
{
	TurnOnLED(GREEN_LED);
}

void activateRedLED()
{
	TurnOnLED(RED_LED);
}

void deactivateGreenLED()
{
	TurnOffLED(GREEN_LED);
}

void deactivateRedLED()
{
	TurnOffLED(RED_LED);
}

void buttonInitApp()
{
	buttonInit();
}

void appDelay(uint32_t t)
{
	char max[LENGTH_FIRST_NAME] = {'M', 'A', 'X'};
	[[maybe_unused]]char destinationArray[LENGTH_FIRST_NAME] = {};
	for (int i = 0; i <= t; i++)	{
		for (int j = 0; j <= LENGTH_FIRST_NAME; j++)	{
			destinationArray[j] = max[j];
		}
	}
}

void gyroOn()
{
	Gyro_PowerOn();
}

void gyroInit()
{
	Gyro_Init();
}

void gyroGetID()
{
	Gyro_getDeviceID();
}

void gyroPrintTemp()
{
	Gyro_PrintTemp();
}

void gyroRegConfig()
{
	Gyro_RegConfig();
}

void rebootGyro()
{
	Gyro_Reboot();
}
/*
void EXTI0_IRQHandler()
{
	EXTI_HandleTypeDef localStruct = {0};
	localStruct.Line = EXTI_LINE_0;
	addSchedulerEvent(DEVICE_ID_AND_TEMP_EVENT);
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	HAL_NVIC_ClearPendingIRQ(EXTI0_IRQn);
	HAL_EXTI_ClearPending(&localStruct, EXTI_TRIGGER_RISING_FALLING);
	addSchedulerEvent(DEVICE_ID_AND_TEMP_EVENT);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
*/
//  ANOTHER WAY TO DO THIS?
void EXTI0_IRQHandler()
{
	EXTI_HandleTypeDef localStruct = {0};
	localStruct.Line = EXTI_LINE_0;
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	HAL_NVIC_ClearPendingIRQ(EXTI0_IRQn);
	HAL_EXTI_ClearPending(&localStruct, EXTI_TRIGGER_RISING);
	gyroOn();
	gyroPrintTemp();
	gyroGetID();
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

