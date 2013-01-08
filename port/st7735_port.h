/**
 * @file 	st7735_port.h
 * @date 	23.5.2012
 * @author 	Kubanec
 * @brief	STM32F407 low level implementation for st7735 display driver
 */

#ifndef ST7735_PORT_H_
#define ST7735_PORT_H_

/**	@addtogroup ST7735_display
 * @{
 */

/**	@addtogroup ST7735_low_level_STM32F407
 * @{
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include "ch.h"
#include "hal.h"

#define CLR_RES		palClearPad(GPIOA,8)
#define SET_RES		palSetPad(GPIOA,8)
#define CLR_RS     	palClearPad(GPIOA,9)
#define SET_RS     	palSetPad(GPIOA,9)
#define CLR_SDA    	palClearPad(GPIOA,10)
#define SET_SDA    	palSetPad(GPIOA,10)
#define CLR_SCL    	palClearPad(GPIOA,11)
#define SET_SCL    	palSetPad(GPIOA,11)
#define CLR_CS     	palClearPad(GPIOA,12)
#define SET_CS     	palSetPad(GPIOA,12)

//backlight
#define CLR_BL
#define SET_BL

//low level functions
void low_level_output(uint8_t data)  __attribute__ ((optimize (0)));
void low_level_init(void);
void systickDelay(uint16_t time)  __attribute__ ((optimize (0)));

#ifdef __cplusplus
}
#endif

#endif /* ST7735_PORT_H_ */

/**
 * @}
 */

/**
 * @}
 */
