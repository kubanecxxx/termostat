/**
 * @file gui_port.h
 *
 * @date 26.5.2012
 *      @author Kubanec
 */

#ifndef GUI_PORT_H_
#define GUI_PORT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx.h"
#include "st7735/st7735_2.h"

/**
 * @defgroup GUI_PORT
 * @{
 */

/**
 * @defgroup STM32F407_PORT
 * @{
 */

/**
 * @brief number of functional buttons
 */
#define BUTTON_COUNT 3

uint32_t low_level_input_buttons(void);
void low_level_button_init(void);

void low_level_FillRGB(uint16_t color);
void low_level_lcdPutsStringBackground(const char * data, uint16_t x,
		uint16_t y, uint16_t color, uint16_t background_color, uint8_t size);

void * super_malloc(uint16_t size);
/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* GUI_PORT_H_ */
