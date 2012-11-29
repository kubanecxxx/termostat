/*
 * rtc.c
 *
 *  Created on: 28.5.2012
 *      Author: kubanec
 */

#include "guiInclude.h"
#include "ch.h"
#include "hal.h"

/**
 * @todo teď to utiká o minutu za hodinu, bud zkalibrovat nebo předělat na externi LS šutr
 * @todo dodělat vteřinovej wake-up
 */

#define GetNeco(time, u_off) \
	(((time >> u_off )& 0xF) + (((time >> (u_off + 4)) & 0xF) * 10))

#define SetNeco(time,off,val) \
	time &= ~(0xF << off); \
	time |= val << off
#define Num2BcdU(num) (num % 10)
#define Num2BcdT(num) (num / 10)
#define Num2Bcd(num) (Num2BcdU(num) | (Num2BcdT(num) << 4))

#define SetNecoLip(time,u_off,val) \
	SetNeco (time, u_off, Num2BcdU(val)); \
	SetNeco (time, (u_off + 4), Num2BcdT(val))

#define GetSeconds(time) GetNeco(time,RTC_TR_SU_OFFSET)
#define GetMinutes(time) GetNeco(time,RTC_TR_MNU_OFFSET)
#define GetHours(time)  \
	(((time >> RTC_TR_HU_OFFSET )& 0xF) + (((time >> (RTC_TR_HT_OFFSET)) & 0x3) * 10))
#define GetDay(day) ((day >> RTC_DR_WDU_OFFSET )& 0x7)

#define SetSeconds(time,val) SetNecoLip(time,RTC_TR_SU_OFFSET,val)
#define SetMinutes(time,val) SetNecoLip(time,RTC_TR_MNU_OFFSET,val)
#define SetHours(time,val)	\
	SetNeco(time, RTC_TR_HU_OFFSET,Num2BcdU(val)); \
	time &= ~(0x7 << RTC_TR_HT_OFFSET); \
	time |= Num2BcdT(val) << RTC_TR_HT_OFFSET
#define SetDay(time,val) \
	time &= ~(0x7 << RTC_DR_WDU_OFFSET); \
	time |= (Num2BcdU(val) << RTC_DR_WDU_OFFSET)

using namespace GuiFramework;

GUI::Gui * rtcClass::ui;

void rtcClass::Init(void)
{
	rtcInit();

	RTCTime time;

	SetMinutes(time.tv_time, 58);
	SetHours(time.tv_time, 23);
	SetDay(time.tv_date, 6);
	time.h12 = FALSE;
	time.tv_time &= ~ (1 << 22);

	rtcSetTime(&RTCD1, &time);
}

/**
 * @brief refrešne čas
 */
void rtcClass::TimeShow(void * data)
{
	ui = (GUI::Gui*) data;
	RTCTime time;

	rtcGetTime(&RTCD1, &time);

	ui->ScreenMain->Minuty->SetValue(GetMinutes(time.tv_time));
	ui->ScreenMain->Minuty->print();

	ui->ScreenMain->Hodiny->SetValue(GetHours(time.tv_time));
	ui->ScreenMain->Hodiny->print();

	ui->ScreenMain->Den->SetValue(GetDay(time.tv_date));
	ui->ScreenMain->Den->print();
}

void rtcClass::zlepsovak(gui_Item & item)
{
	int16_t temp = item.GetHighLimit();
	int16_t be = item.GetValue();

	RTCTime time;
	rtcGetTime(&RTCD1, &time);

	switch (temp)
	{
	case 7:
		SetDay(time.tv_date, be);
		break;
	case 59:
		SetMinutes(time.tv_time, be);
		break;
	case 23:
		SetHours(time.tv_time, be);
		break;
	}

	time.h12 = FALSE;
	rtcSetTime(&RTCD1, &time);
}

void rtcClass::CallbackUp(void * data)
{
	gui_Item & item = *(gui_Item *) data;

	++item;
	zlepsovak(item);
}

void rtcClass::CallbackDown(void * data)
{
	gui_Item & item = *(gui_Item *) data;

	--item;
	zlepsovak(item);
}

