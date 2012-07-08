/**
 * @file 	st7735_port.c
 * @date 	23.5.2012
 * @author 	Kubanec
 * @brief	STM32F407 low level implementation for st7735 display driver
 */

/** @addtogroup ST7735_display
 *  @{
 */

/**	@defgroup ST7735_low_level_STM32F407
 * @{
 */

#include "st7735_port.h"
#include "interrupts.h"

#define SOFTWARE_SPI

/**
 * @brief Low level spi output for display
 * @param 8-bit data to be sent
 * @return void
 */
void low_level_output(uint8_t data)
{
#ifdef SOFTWARE_SPI
	uint8_t i = 0;
	systickDelay(1);
	for (i = 0; i < 8; i++)
	{
		CLR_SCL;
		//systickDelay(1);
		if (data & 0x80)
			SET_SDA;
		else
			CLR_SDA;
		//systickDelay(1);

		data <<= 1;
		SET_SCL;
		//systickDelay(1);
	}
#else
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1,data);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
#endif
}

/**
 * @brief low level spi initialization
 * @param none
 * @return none
 */
void low_level_init(void)
{
	GPIO_InitTypeDef GPIO_Struct;
#ifndef SOFTWARE_SPI
	SPI_InitTypeDef SPI_Struct;
#endif

	RCC_AHB1PeriphClockCmd(
			RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC,
			ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	GPIO_Struct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_6;
#ifdef  SOFTWARE_SPI
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
#else
	GPIO_Struct.GPIO_Mode = GPIO_Mode_AF;
#endif
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_Struct);

	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA, &GPIO_Struct);

	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_Struct);

	GPIO_Struct.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_Struct);

#ifndef SOFTWARE_SPI
	//HW SPI
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5, GPIO_AF_SPI1);

	//SPI configuration
	SPI_I2S_DeInit(SPI1);
	SPI_Struct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_Struct.SPI_DataSize = SPI_DataSize_8b;
	SPI_Struct.SPI_CPOL = SPI_CPOL_Low;
	SPI_Struct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_Struct.SPI_NSS = SPI_NSS_Soft;
	SPI_Struct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_Struct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Struct.SPI_CRCPolynomial = 7;
	SPI_Struct.SPI_Mode = SPI_Mode_Master;

	SPI_Init(SPI1, &SPI_Struct);
	SPI_Cmd(SPI1, ENABLE);

#endif

}

/**
 * @brief low level delay for display
 * @param ms delay in miliseconds
 * @return void
 * @note also can be used RTOS implementation to suspend thread
 */
void systickDelay(uint16_t ms)
{
	//uint32_t temp;

	//1ms timeCounter

	while (ms--)
		;

	return;

	/*temp = GetTimeCounter();

	 while(GetTimeCounter() - temp >= ms );
	 */
}

/**
 * @}
 */

/**
 * @}
 */
