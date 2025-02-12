#ifndef INC_GYRO_H_
#define INC_GYRO_H_

#include "stm32f4xx.h"
#include "ErrorHandling.h"

#define WHO_AM_I 		0x0f
#define CTRL_REG1 		0x20
#define CTRL_REG2 		0x21
#define CTRL_REG3 		0x22
#define CTRL_REG4		0x23
#define CTRL_REG5		0x24
#define REF_DATA_CAP	0x25
#define OUT_TEMP		0x26
#define STATUS_REG 		0x27
#define OUT_X_L 		0x28
#define OUT_X_H 		0x29
#define OUT_Y_L			0x2A
#define OUT_Y_H			0x2B
#define	OUT_Z_L			0x2C
#define OUT_Z_H			0x2D
#define FIFO_CTRL_REG 	0x2E
#define FIF_SRC_REG		0x2F
#define INT1_CFG 		0x30
#define INT1_SRC 		0x31
#define INT1_THS_XH		0x32
#define INT1_THS_HL		0x33
#define INT1_THS_YH		0x34
#define INT1_THS_YL		0x35
#define INT1_THS_ZH		0x36
#define INT1_THS_ZL		0x37
#define INT1_DURATION	0x38

#define GYRO_MISO_PIN 	GPIO_PIN_8
#define GYRO_MOSI_PIN	GPIO_PIN_9
#define GYRO_SCK_PIN 	GPIO_PIN_7
#define GYRO_CS_PIN		GPIO_PIN_1
#define GYRO_PORT 		GPIOF

#define CTRL_REG1_PD_OFFSET 	3;
#define CTRL_REG5_BOOT_OFFSET 	7;

#define I3G4250D_READ 	1<<7
#define I3G4250D_WRITE 	0<<7

void Gyro_Init();

void Gyro_getDeviceID();

void Gyro_PowerOn();

void Gyro_PrintTemp();

void Gyro_RegConfig();

void Gyro_ReadReg();

void Gyro_VerifyHALStatus();

void Gyro_EnableSlave();

void Gyro_DisableSlave();

void Gyro_Reboot();

#endif
