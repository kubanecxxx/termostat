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
uint32_t low_level_input_buttons(void)
{
	if (palReadPad(GPIOA,0))
		return 2;
	else if (palReadPad(GPIOD,0))
		return 0;
	else if (palReadPad(GPIOD,4))
		return 1;
	else
		return -1;
}

void low_level_button_init()
{
	St7735::Init();
	palSetPadMode(GPIOA, 0, PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 0, PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 4, PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD,2,PAL_MODE_OUTPUT_PUSHPULL);
	palSetPad(GPIOD,2);
}

void low_level_FillRGB(uint16_t color)
{
	St7735::FillRGB(color);
}

void low_level_lcdPutsStringBackground(const char * data, uint16_t x,
		uint16_t y, uint16_t color, uint16_t background_color, uint8_t size)
{
	St7735::PutsStringBackground(data, x, y, color, background_color, size);
}

void * gui_malloc(uint16_t size)
{
	return chCoreAlloc(size);
}

void gui_freeMemory(void * data)
{
	(void) data;
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
