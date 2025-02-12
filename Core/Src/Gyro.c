#include "Gyro.h"

SPI_HandleTypeDef halspi5;
static HAL_StatusTypeDef gyroHALStatus;

#define DELAY 20000

void Gyro_Init()
{
	__HAL_RCC_GPIOF_CLK_ENABLE();
	GPIO_InitTypeDef localStruct = {0};
	localStruct.Pin = (GYRO_MISO_PIN | GYRO_MOSI_PIN | GYRO_SCK_PIN);
	localStruct.Mode = GPIO_MODE_AF_PP;
	localStruct.Pull = GPIO_NOPULL;
	localStruct.Speed = GPIO_SPEED_FREQ_LOW;
	localStruct.Alternate = GPIO_AF5_SPI5;
	HAL_GPIO_Init(GPIOF, &localStruct);

	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitTypeDef localStruct2 = {0};
	localStruct2.Pin = GYRO_CS_PIN;
	localStruct2.Mode = GPIO_MODE_OUTPUT_OD;
	localStruct2.Pull = GPIO_PULLUP;
	localStruct2.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &localStruct2);
	Gyro_DisableSlave();

	halspi5.Instance = SPI5;
	halspi5.Init.Mode = SPI_MODE_MASTER;//
	halspi5.Init.Direction = SPI_DIRECTION_2LINES;//
	halspi5.Init.DataSize = SPI_DATASIZE_8BIT;//
	halspi5.Init.CLKPolarity = SPI_POLARITY_HIGH;//
	halspi5.Init.CLKPhase = SPI_PHASE_2EDGE;//
	halspi5.Init.NSS = SPI_NSS_SOFT;
	halspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;//
	halspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
	halspi5.Init.TIMode = SPI_TIMODE_DISABLE;
	halspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	halspi5.Init.CRCPolynomial = 0;
	HAL_SPI_Init(&halspi5);

	Gyro_VerifyHALStatus();
}

void Gyro_getDeviceID()
{
	uint16_t commandToSend = (I3G4250D_READ | WHO_AM_I);
	uint16_t receivedData = 0x00;
	Gyro_EnableSlave();
	gyroHALStatus = HAL_SPI_TransmitReceive(&halspi5, (uint8_t*) &commandToSend, (uint8_t*) &receivedData, 2, DELAY);
	Gyro_VerifyHALStatus();
	Gyro_DisableSlave();
	uint8_t dataReturned = (receivedData >> 8);
	printf("The Device ID is: 0x%X \n \r", dataReturned);
}

void Gyro_PowerOn()
{
	uint16_t commandToSend = (I3G4250D_READ | CTRL_REG1);
	uint16_t data;
	Gyro_EnableSlave();
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) != GPIO_PIN_RESET);
	gyroHALStatus = HAL_SPI_TransmitReceive(&halspi5, (uint8_t*) &commandToSend, (uint8_t*) &data, 2, DELAY);
	Gyro_VerifyHALStatus();
	Gyro_DisableSlave();
	uint16_t command = (data & (0xFF00 | 0x08)) | (0 << 7 | CTRL_REG1);
	Gyro_EnableSlave();
	HAL_SPI_Transmit(&halspi5, (uint8_t*) &command, 2, DELAY);
	Gyro_DisableSlave();
}

void Gyro_PrintTemp()
{
	uint16_t commandToSend = (I3G4250D_READ | OUT_TEMP);
	uint16_t receivedData = 0x00;

	Gyro_EnableSlave();
	gyroHALStatus = HAL_SPI_TransmitReceive(&halspi5, (uint8_t*) &commandToSend, (uint8_t*) &receivedData, 2, DELAY);
	Gyro_VerifyHALStatus();
	Gyro_DisableSlave();
	uint8_t DataReturned = (0xFF00 & receivedData) >> 8;
	printf("The temperature is: %u \n", DataReturned);
}

void Gyro_RegConfig()
{
	// CTRL1 CONFIG
	uint16_t commandToSend = (I3G4250D_WRITE | CTRL_REG1);
	commandToSend |= (0x1F << 8);
	Gyro_EnableSlave();
	gyroHALStatus = HAL_SPI_Transmit(&halspi5, (uint8_t*)&commandToSend, 2, DELAY);
	if (gyroHALStatus != HAL_OK)
	{
		for(;;);
	}
	Gyro_DisableSlave();

	// CTRL4 CONFIG
	commandToSend = (I3G4250D_WRITE | CTRL_REG4);
	commandToSend |= (0x10 << 8);
	Gyro_EnableSlave();
	gyroHALStatus = HAL_SPI_Transmit(&halspi5, (uint8_t*)&commandToSend, 2, DELAY);
	if (gyroHALStatus != HAL_OK)
	{
		for(;;);
	}
	Gyro_DisableSlave();

	// CTRL5 CONFIG
	commandToSend = (I3G4250D_WRITE | CTRL_REG5);
	commandToSend |= (0xC0 << 8);
	Gyro_EnableSlave();
	gyroHALStatus = HAL_SPI_Transmit(&halspi5,(uint8_t*)&commandToSend, 2, DELAY);
	if (gyroHALStatus != HAL_OK)
	{
		for(;;);
	}
	Gyro_DisableSlave();

	// FIFO CONFIG
	commandToSend = (I3G4250D_WRITE | FIFO_CTRL_REG);
	commandToSend |= (0x20 << 8);
	Gyro_EnableSlave();
	gyroHALStatus = HAL_SPI_Transmit(&halspi5, (uint8_t*)&commandToSend, 2, DELAY);

	if (gyroHALStatus != HAL_OK)
	{
		for(;;);
	}
	Gyro_DisableSlave();
}

void Gyro_ReadReg();

void Gyro_Reboot() // was told this could be useful by a TA
{
	uint16_t send = (I3G4250D_WRITE | CTRL_REG5);
	uint16_t other;
	Gyro_EnableSlave();
	gyroHALStatus = HAL_SPI_TransmitReceive(&halspi5, (uint8_t*) &send, (uint8_t*) &other, 2, DELAY);
	Gyro_VerifyHALStatus();
	Gyro_DisableSlave();
	other = other >> 8;
	other |= 1 << 8;
	send = (I3G4250D_WRITE | CTRL_REG5 | other);
	Gyro_EnableSlave();
	HAL_SPI_Transmit(&halspi5, (uint8_t*) &send, 2, DELAY);
	Gyro_DisableSlave();
}

void Gyro_VerifyHALStatus()
{
	APPLICATION_ASSERT(gyroHALStatus == HAL_OK);
}

void Gyro_EnableSlave()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
}

void Gyro_DisableSlave()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
}

