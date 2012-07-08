/**
 * @file gui_port.c
 *
 * @date 26.5.2012
 *      @author Kubanec
 *      @brief low level porting for gui framework
 */

#include "framework_port.h"

void * _sbrk(int incr);

/**
 * @addtogroup GUI
 * @{
 */

/**
 * @addtogroup GUI_PORT
 * @{
 */

/**
 * @addtogroup STM32F407_PORT
 * @{
 */

/**
 * @brief low level function for scanning buttons
 * @return bit state of buttons
 */
uint32_t low_level_input_buttons(void)
{
	if (GPIOA->IDR & GPIO_Pin_0)
		return 0;
	else if (GPIOC->IDR & GPIO_Pin_14)
		return 1;
	else if (GPIOC->IDR & GPIO_Pin_15)
		return 2;
	else
		return -1;
}

void low_level_button_init()
{
	GPIO_InitTypeDef GPIO_Struct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_Struct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_DOWN;

	GPIO_Init(GPIOA, &GPIO_Struct);

	GPIO_Struct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14;
	GPIO_Init(GPIOC, &GPIO_Struct);
}

void low_level_FillRGB(uint16_t color)
{
	lcdFillRGB(color);
}

void low_level_lcdPutsStringBackground(const char * data, uint16_t x,
		uint16_t y, uint16_t color, uint16_t background_color, uint8_t size)
{
	lcdPutsStringBackground(data, x, y, color, background_color, size);
}

void * super_malloc(uint16_t size)
{
	return (void *) _sbrk(size);
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
