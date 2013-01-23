/*
 * rtc.c
 *
 *  Created on: 28.5.2012
 *      Author: kubanec
 */

#include "guiInclude.h"
#include "ch.h"
#include "hal.h"
#include <time.h>

using namespace GuiFramework;

GUI::Gui * rtcClass::ui;

static void localtime(uint32_t time, struct tm & t)
{
	t.tm_sec = time % 60;
	time /= 60;
	t.tm_min = time % 60;
	time /= 60;
	t.tm_hour = time % 24;
	time /= 24;
	time *= 100;
	uint32_t temp = (time % 36525) / 100; //pocet dni od zacatku roku
	t.tm_wday = (temp) % 7;
}

static uint32_t maketime(const struct tm & t)
{
	uint32_t temp;
	temp = t.tm_sec;
	temp += t.tm_min * 60;
	temp += t.tm_hour * 3600;
	temp += t.tm_wday * 24 * 3600;

	return temp;
}

void rtcClass::Init(void)
{
	RTCTime time;
	struct tm t;

	rtcInit();
	t.tm_hour = 18;
	t.tm_min = 27;
	t.tm_wday = 2;
	t.tm_sec = 0;
	time.tv_sec = maketime(t);

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
	struct tm t;
	localtime(time.tv_sec, t);

	ui->ScreenMain->Minuty->SetValue(t.tm_min);
	ui->ScreenMain->Minuty->print();

	ui->ScreenMain->Hodiny->SetValue(t.tm_hour);
	ui->ScreenMain->Hodiny->print();

	ui->ScreenMain->Den->SetValue(t.tm_wday + 1);
	ui->ScreenMain->Den->print();

}

void rtcClass::zlepsovak()
{
	RTCTime time;
	struct tm t;

	rtcGetTime(&RTCD1, &time);
	t.tm_hour = ui->ScreenMain->Hodiny->GetValue();
	t.tm_min = ui->ScreenMain->Minuty->GetValue();
	t.tm_wday = ui->ScreenMain->Den->GetValue() - 1;
	t.tm_sec = 0;

	time.tv_sec = maketime(t);
	rtcSetTime(&RTCD1, &time);

}

void rtcClass::CallbackUp(void * data)
{
	gui_Item & item = *(gui_Item *) data;

	++item;
	zlepsovak();
}

void rtcClass::CallbackDown(void * data)
{
	gui_Item & item = *(gui_Item *) data;

	--item;
	zlepsovak();
}

