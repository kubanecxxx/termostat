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
extern "C" {
#endif

#include "ch.h"
#include "hal.h"

//připadně mrsknout typedef 8, 16 pokud nejsou někde defaultně
#ifdef ST7735_default_typedefs
	typedef unsigned char uint8_t;
	typedef unsigned int uint16_t;
#endif

#define bit_set(x,y)  (x->ODR |= 1<<y)
#define bit_clr(x,y)  (x->ODR &= ~ (1<<y))

#define CLR_RS     	bit_clr(GPIOB,1)
#define SET_RS     	bit_set(GPIOB,1)
#define CLR_SDA    	bit_clr(GPIOA,6)
#define SET_SDA    	bit_set(GPIOA,6)
#define CLR_SCL    	bit_clr(GPIOA,7)
#define SET_SCL    	bit_set(GPIOA,7)
#define CLR_CS     	bit_clr(GPIOC,5)
#define SET_CS     	bit_set(GPIOC,5)
#define CLR_RES		bit_clr(GPIOB,0)
#define SET_RES		bit_set(GPIOB,0)

//backlight
#define CLR_BL
#define SET_BL


//low level functions
void low_level_output(uint8_t data);
void low_level_init(void);
void systickDelay(uint16_t time);

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
