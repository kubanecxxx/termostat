/**
 * @file Wireless.cpp
 * @author kubanec
 * @date 23.12.2012
 *
 */

#include "Wireless.h"

using namespace rfm;

const ApplicationLayer::error_cb_t Wireless::errors =
{ timeout_error, arq_cb_error };

const ApplicationLayer::user_callbacks_t Wireless::callbacks[2] =
{
{ user_cb, NULL },
{ user_cb, NULL } };

int16_t Wireless::TemperatureCache = 0;
bool Wireless::Response = false;

Wireless::Wireless()
{
	rfm::ApplicationLayer::Init(1, 1 << SLAVE_ADDR, &errors, callbacks, 2);
}

void Wireless::arq_cb_error()
{

}

void Wireless::timeout_error(uint8_t slave)
{
	if (slave == SLAVE_ADDR)
	{
		Response = false;
	}
}

void Wireless::user_cb(bool ok, ApplicationLayer::user_cb_packet_t type,
		uint8_t address, uint16_t modbus_addr, uint32_t modbus_data)
{
	Response = true;
	if (ok && address == SLAVE_ADDR)
	{
		if (modbus_addr == TEMP_ADDR)
		{
			TemperatureCache = modbus_data;
		}
		else if (modbus_addr == RELAY_ADDR)
		{

		}
	}
}

