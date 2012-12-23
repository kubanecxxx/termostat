/**
 * @file Wireless.h
 * @author kubanec
 * @date 23.12.2012
 *
 */

#ifndef WIRELESS_H_
#define WIRELESS_H_

#include "rfmIncludeCpp.h"

#define SLAVE_ADDR 5
#define RELAY_ADDR 1
#define TEMP_ADDR 0

class Wireless
{
public:
	Wireless();
	inline static int16_t GetTemperature()
	{
		rfm::ApplicationLayer::Get(SLAVE_ADDR,TEMP_ADDR);
		return TemperatureCache;
	}
	inline static void SetTopit(bool enabled)
	{
		rfm::ApplicationLayer::Set(SLAVE_ADDR, RELAY_ADDR, enabled);
	}
	inline static bool Responding() {return Response;}

private:
	static void arq_cb_error();
	static void timeout_error(uint8_t slave);
	static void user_cb(bool ok, rfm::ApplicationLayer::user_cb_packet_t type,
			uint8_t address, uint16_t modbus_addr, uint32_t modbus_data);

	const static rfm::ApplicationLayer::error_cb_t errors;
	const static rfm::ApplicationLayer::user_callbacks_t callbacks[2];

	static int16_t TemperatureCache;
	static bool Response;
};

#endif /* WIRELESS_H_ */
