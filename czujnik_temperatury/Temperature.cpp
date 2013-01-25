/*
 * Temperature.cpp
 *
 *  Created on: 11.9.2012
 *      Author: kubanec
 */

#include "ch.hpp"
#include "hal.h"
#include "Temperature.h"

static const I2CConfig i2conf =
{ OPMODE_I2C, 20000, STD_DUTY_CYCLE };

int16_t Temperature::temperature = 0;

void Temperature::Init()
{
	palSetPadMode(GPIOB,10,PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
	palSetPadMode(GPIOB,11,PAL_MODE_STM32_ALTERNATE_OPENDRAIN);

	uint8_t txbuf[3];
	i2cStart(&I2CD2, &i2conf);

	//sleep mode
	txbuf[0] = 1;
	txbuf[1] = 1;
	i2cMasterTransmit(&I2CD2, I2C_TEMP_ADDRESS, txbuf, 2, NULL, 0);
}

int16_t Temperature::GetTemperature()
{
	return temperature;
}

void Temperature::RefreshTemperature()
{
	uint8_t txbuf[2];
	uint8_t rxbuf[2];

	//wake up
	txbuf[0] = 1;
	txbuf[1] = 0;
	i2cMasterTransmit(&I2CD2, I2C_TEMP_ADDRESS, txbuf, 2, NULL, 0);
	chibios_rt::BaseThread::Sleep(MS2ST(200) );

	txbuf[0] = 0;

	i2cMasterTransmit(&I2CD2, I2C_TEMP_ADDRESS, txbuf, 1, rxbuf, 2);

	//sleep mode
	txbuf[0] = 1;
	txbuf[1] = 1;
	i2cMasterTransmit(&I2CD2, I2C_TEMP_ADDRESS, txbuf, 2, NULL, 0);

	temperature = (rxbuf[0] << 8 | rxbuf[1]) - 128;
}
