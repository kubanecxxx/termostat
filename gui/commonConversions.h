/*
 * comonConversions.h
 *
 *  Created on: 5.9.2012
 *      Author: kubanec
 */

#ifndef COMMONCONVERSIONS_H_
#define COMMONCONVERSIONS_H_

namespace GUI
{

class ConversionsClass
{
protected:
	static void conv_dummy(char * data, int16_t value);
	static void conv_hours_minutes(char * data, int16_t value);

};
} /* namespace GUI */
#endif /* COMMONCONVERSIONS_H_ */
