/**
 * @file gui_port.c
 *
 * @date 26.5.2012
 *      @author Kubanec
 *      @brief low level porting for gui framework
 */

#include "ch.h"
#include "hal.h"
#include "framework_port.h"
#include "st7735.hpp"
#include "stm32f10x_flash.h"

namespace GuiFramework
{
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
uint32_t port::input_buttons(void)
{
	if (palReadPad(GPIOB,4))
		return 2;
	else if (palReadPad(GPIOB,3))
		return 0;
	else if (palReadPad(GPIOB,5))
		return 1;
	else
		return -1;
}

void port::init()
{
	St7735::Init();
	AFIO->MAPR |= 0b010 << 24;
	palSetPadMode(GPIOB, 3, PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 4, PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 5, PAL_MODE_INPUT_PULLDOWN);
}

uint32_t port::address = 0;

void port::Erase(uint32_t start, uint32_t stop)
{
	address = start;
	FLASH_Unlock();
	while(start < stop)
	{
		if (FLASH_ErasePage(start) != FLASH_COMPLETE)
		{
			asm("bkpt");
		}
		start += 1024;
	}

	FLASH_Lock();
}

void * port::Write(const void * datas, uint32_t size)
{
	FLASH_Unlock();
	uint16_t * data = (uint16_t *)datas;
	void * temp = (void *)address;

	size = (size + 1) / 2;

	for (uint32_t i = 0 ; i < size ; i++)
	{
		if (FLASH_ProgramHalfWord(address,*data) != FLASH_COMPLETE)
		{
			asm("bkpt");
		}
		data++;
		address += 2;
	}

	return temp;
	FLASH_Lock();
}

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
