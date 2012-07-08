/*
 * rtc.h
 *
 *  Created on: 28.5.2012
 *      Author: kubanec
 */

#ifndef GUI_RTC_H_
#define GUI_RTC_H_

uint8_t rtc_Init(void);
void RTC_TimeShow(void *);

void rtc_CallbackDown(void * item);
void rtc_CallbackUp(void * item);

#endif /* GUI_RTC_H_ */
