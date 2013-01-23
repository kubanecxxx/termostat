/*
 * rfm_port.c
 *
 *  Created on: 5.6.2012
 *      Author: kubanec
 */

#ifndef RFM_PORT_C_
#define RFM_PORT_C_

#ifdef __cplusplus
extern "C"
{
#endif

#include "ch.h"
#include "hal.h"

#define RFM_868

#define 	FFIT_EVENT_FLAG 1

/*
 * udělany na ledky z discovery
 * červená přijimač
 * zelená vysilač
 * žlutá máme synchronizaci
 * a modrá když se posilá paket s datama (ne idle)
 */
//#define RFM_INDICATE_ON

void low_level_spi_init(void);
uint8_t low_level_wait_ffit_high(systime_t timeout)  __attribute__ ((optimize (0)));
void low_level_wait_nirq_low(void);
uint16_t low_level_spi_in_out(uint16_t data) ;//__attribute__ ((optimize (0)));
//void ffit_exti(EXTDriver *extp, expchannel_t channel);

#ifndef RFM_SENELA
#define FFIT_EXTI EXT_CH_MODE_RISING_EDGE | EXT_MODE_GPIOB, ffit_exti
#else
#define FFIT_EXTI EXT_CH_MODE_RISING_EDGE | EXT_MODE_GPIOE, ffit_exti
#endif
void rf_ffitThreadInit(Thread * thd);

#ifdef __cplusplus
}
#endif

#endif /* RFM_PORT_C_ */
