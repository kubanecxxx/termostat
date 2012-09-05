/*
 * rtc.h
 *
 *  Created on: 28.5.2012
 *      Author: kubanec
 */

#ifndef GUI_RTC_H_
#define GUI_RTC_H_

namespace GUI
{

class rtcClass
{
public:
	static void Init(void);
	static void TimeShow(void *);

	static void CallbackDown(void * item);
	static void CallbackUp(void * item);

private:
	static void zlepsovak(GuiFramework::gui_Item * item);
	static void TimeRegulate(void);
};
}
#endif /* GUI_RTC_H_ */
