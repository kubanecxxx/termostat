/*
 * commonConversions.cpp
 *
 *  Created on: 5.9.2012
 *      Author: kubanec
 */

#include "guiInclude.h"

namespace GUI
{

void ConversionsClass::conv_dummy(char * data, int16_t value)
{
	(void) value;
	data[0] = '\0';
}

void ConversionsClass::conv_hours_minutes(char * data, int16_t value)
{
	data[2] = 0;
	data[0] = value / 10 + '0';
	data[1] = value % 10 + '0';
}

} /* namespace GUI */
