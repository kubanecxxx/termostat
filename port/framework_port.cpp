/**
 * @file gui_port.c
 *
 * @date 26.5.2012
 *      @author Kubanec
 *      @brief low level porting for gui framework
 */

#include "framework_port.h"
#include "ch.h"
#include "hal.h"
#include "st7735/st7735_2.h"

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
		return 0;
	else if (palReadPad(GPIOC,14))
		return 1;
	else if (palReadPad(GPIOC,15))
		return 2;
	else
		return -1;
}

void low_level_button_init()
{
	lcdInit();
	palSetPadMode(GPIOA, 0, PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOC, 14, PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOC, 15, PAL_MODE_INPUT_PULLDOWN);
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
