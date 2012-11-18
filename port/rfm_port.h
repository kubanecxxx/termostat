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

void low_level_spi_init(void);
void low_level_wait_ffit_high(void);
void low_level_wait_nirq_low(void);
uint16_t low_level_spi_in_out(uint16_t data);
void ffit_exti(EXTDriver *extp, expchannel_t channel);

#define FFIT_EXTI EXT_CH_MODE_RISING_EDGE | EXT_MODE_GPIOB, ffit_exti
void rf_ffitThreadInit(void);

#ifdef __cplusplus
}
#endif

#endif /* RFM_PORT_C_ */
