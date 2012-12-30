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

//připadně mrsknout typedef 8, 16 pokud nejsou někde defaultně
#ifdef ST7735_default_typedefs
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
#endif

#define bit_set(x,y)  (x->BSRR = 1<<y)
#define bit_clr(x,y)  (x->BRR = 1<<y)

#define CLR_RS     	bit_clr(GPIOA,1)
#define SET_RS     	bit_set(GPIOA,1)
#define CLR_SDA    	bit_clr(GPIOA,2)
#define SET_SDA    	bit_set(GPIOA,2)
#define CLR_SCL    	bit_clr(GPIOA,3)
#define SET_SCL    	bit_set(GPIOA,3)
#define CLR_CS     	bit_clr(GPIOA,4)
#define SET_CS     	bit_set(GPIOA,4)
#define CLR_RES		bit_clr(GPIOA,0)
#define SET_RES		bit_set(GPIOA,0)

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
