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

/**
 * @brief Low level spi output for display
 * @param 8-bit data to be sent
 * @return void
 */
void low_level_output(uint8_t data)
{
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
}

/**
 * @brief low level spi initialization
 * @param none
 * @return none
 */
void low_level_init(void)
{
	palSetPadMode(GPIOA, 7, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOB, 1, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOA, 6, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, 5, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOB, 0, PAL_MODE_OUTPUT_PUSHPULL);
}

/**
 * @brief low level delay for display
 * @param ms delay in miliseconds
 * @return void
 * @note also can be used RTOS implementation to suspend thread
 */
void systickDelay(uint16_t ms)
{
	while (ms--)
		;
}

/**
 * @}
 */

/**
 * @}
 */
