/*
 * Temperature.h
 *
 *  Created on: 11.9.2012
 *      Author: kubanec
 */

#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#define I2C_TEMP_ADDRESS 0b1001111

class Temperature
{
private:

public:
	static void Init(void);
	static int16_t GetTemperature(void);
};

#endif /* TEMPERATURE_H_ */
