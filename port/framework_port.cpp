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
uint32_t port::input_buttons(void)
{
	if (palReadPad(GPIOB,2))
		return 2;
	else if (palReadPad(GPIOD,0))
		return 0;
	else if (palReadPad(GPIOD,4))
		return 1;
	else
		return -1;
}

void port::init()
{
	St7735::Init();

	CLR_RES;
	CLR_RS;
	CLR_SDA;
	CLR_SCL;
	CLR_CS;

	SET_RES;
	CLR_RES;

	SET_RS;
	CLR_RS;

	SET_SDA;
	CLR_SDA;

	SET_SCL;
	CLR_SCL;

	SET_CS;
	CLR_CS;

	while(1)
	{
		asm ("nop");
	}
	palSetPadMode(GPIOA, 0, PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 0, PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 4, PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, 2, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPad(GPIOD, 2);

	palSetPadMode(GPIOB, 2, PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOB, 0, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPad(GPIOB, 0);
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
