/*
 * VodaScreenClass.cpp
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#include "guiInclude.h"

namespace GUI
{

using namespace GuiFramework;

gui_Screen * VodaScreenClass::screen;

#define SIZE 8
#define SIZEY 12
#define X1 10
#define X2 (X1+10*SIZE)
#define Y1 45
#define Y2 (Y1 + SIZEY)

VodaScreenClass::VodaScreenClass()
{
	screen = new gui_Screen;

	CreateHalf();
	CreateRest();
}

void VodaScreenClass::CreateHalf()
{
	gui_Item pole[3];

	pole[0].SetText("Hlidat t. ");
	pole[0].SetValue(0);
	pole[0].SetLowLimit(0);
	pole[0].SetHighLimit(1);
	pole[0].SetConvFunction(conv_onoff);
	pole[0].SetPrimaryX(10);
	pole[0].SetPrimaryY(10);

	pole[1].SetText("Teplota    ");
	pole[1].SetValue(50);
	pole[1].SetHighLimit(80);
	pole[1].SetLowLimit(20);
	pole[1].SetPrimaryX(10);
	pole[1].SetPrimaryY(26);
	pole[1].SetConvFunction(conv_hours_minutes);

	pole[2].SetText("Zacit   ");
	pole[2].SetLowLimit(0);
	pole[2].SetHighLimit(23);
	pole[2].SetValue(10);
	pole[2].SetConvFunction(conv_hours_minutes);
	pole[2].SetPrimaryX(X1);
	pole[2].SetPrimaryY(Y1);

	Teplota = screen->Register(&pole[0],true);
	HlidatTeplotu = screen->Register(&pole[1],true);
	HodinyZacit = screen->Register(&pole[2],true);
}

void VodaScreenClass::CreateRest()
{
	gui_Item pole[4];

	pole[0].SetText(":");
	pole[0].SetValue(0);
	pole[0].SetHighLimit(59);
	pole[0].SetLowLimit(0);
	pole[0].SetConvFunction(conv_hours_minutes);
	pole[0].SetPrimaryX(X2);
	pole[0].SetPrimaryY(Y1);

	pole[1].SetText("Vypnout ");
	pole[1].SetLowLimit(0);
	pole[1].SetHighLimit(23);
	pole[1].SetValue(10);
	pole[1].SetConvFunction(conv_hours_minutes);
	pole[1].SetPrimaryX(X1);
	pole[1].SetPrimaryY(Y2);

	pole[2].SetText(":");
	pole[2].SetValue(0);
	pole[2].SetHighLimit(59);
	pole[2].SetLowLimit(0);
	pole[2].SetConvFunction(conv_hours_minutes);
	pole[2].SetPrimaryX(X2);
	pole[2].SetPrimaryY(Y2);

	pole[3].SetText("Zpet");
	pole[3].SetPrimaryX(50);
	pole[3].SetPrimaryY(140);
	pole[3].SetShownValue(false);
	pole[3].SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
			MenuScreenClass::MakeActiveCB);
	pole[3].SetConvFunction(conv_dummy);

	MinutyZacit = screen->Register(&pole[0],true);
	HodinyKonec = screen->Register(&pole[1],true);
	MinutyKonec = screen->Register(&pole[2],true);
	screen->Register(&pole[3],true);
}

void VodaScreenClass::MakeActiveCB(void * item)
{
	(void) item;
	screen->printScreen();
}

void VodaScreenClass::conv_onoff(char * data, int16_t value)
{
	const char hoj[2][4] =
	{
	{ "Off" },
	{ " On" } };

	strcpy(data, hoj[value]);
}
}
