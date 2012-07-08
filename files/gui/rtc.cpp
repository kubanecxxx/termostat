/*
 * rtc.c
 *
 *  Created on: 28.5.2012
 *      Author: kubanec
 */

#include "stm32f4xx.h"
#include "rtc.h"
#include "Gui.h"

/**
 * @todo teď to utiká o minutu za hodinu, bud zkalibrovat nebo předělat na externi LS šutr
 * @todo dodělat vteřinovej wake-up
 */

extern Gui * ui;

void RTC_TimeRegulate(void);

uint8_t rtc_Init(void)
{
	RTC_TimeRegulate();

	return 0;
}

void RTC_TimeShow(void * data)
{
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;

	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);

	RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
	ui->ScreenMain->Hodiny->SetValue(RTC_TimeStructure.RTC_Hours);
	ui->ScreenMain->Minuty->SetValue(RTC_TimeStructure.RTC_Minutes);
	ui->ScreenMain->Hodiny->printItem();
	ui->ScreenMain->Minuty->printItem();

	RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
	ui->ScreenMain->Den->SetValue(RTC_DateStructure.RTC_WeekDay);
	ui->ScreenMain->Den->printItem();
}

void RTC_TimeRegulate(void)
{
	uint32_t tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;
	RTC_InitTypeDef rtc;
	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	RCC_LSICmd(ENABLE);

	/* Wait till LSI is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{
	}

	/* Select the RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

	rtc.RTC_SynchPrediv = 0xFF;
	rtc.RTC_AsynchPrediv = 0x7F;
	rtc.RTC_HourFormat = RTC_HourFormat_24;

	/* Enable the RTC Clock */
	RCC_RTCCLKCmd(ENABLE);

	/* Wait for RTC APB registers synchronisation */
	RTC_WaitForSynchro();

	RTC_Init(&rtc);

	RTC_TimeStructure.RTC_H12 = RTC_H12_AM;
	tmp_hh = 1;
	RTC_TimeStructure.RTC_Hours = tmp_hh;
	tmp_mm = 10;
	RTC_TimeStructure.RTC_Minutes = tmp_mm;
	tmp_ss = 5;
	RTC_TimeStructure.RTC_Seconds = tmp_ss;

	RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Monday;

	/* Configure the RTC time register */
	if (RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure) == ERROR)
	{
		while (1)
			;
	}

	if (RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure) == ERROR)
	{
		while (1)
			;
	}
}

void rtc_zlepsovak(gui_Item * item)
{
	int16_t temp = item->GetHighLimit();

	RTC_TimeTypeDef RTC_TimeStructure;
	RTC_DateTypeDef RTC_DateStructure;

	switch (temp)
	{
	case 7:
		RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
		RTC_DateStructure.RTC_WeekDay = item->GetValue();
		RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure);
		break;
	case 59:
		RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
		RTC_TimeStructure.RTC_Minutes = item->GetValue();
		RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
		break;
	case 23:
		RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
		RTC_TimeStructure.RTC_Hours = item->GetValue();
		RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
		break;
	}
}

void rtc_CallbackUp(void * data)
{
	gui_Item * item = (gui_Item *) data;

	++(*item);
	rtc_zlepsovak(item);
}

void rtc_CallbackDown(void * data)
{
	gui_Item * item = (gui_Item *) data;

	--(*item);
	rtc_zlepsovak(item);
}

