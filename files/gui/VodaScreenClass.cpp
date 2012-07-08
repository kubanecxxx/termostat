/*
 * VodaScreenClass.cpp
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#include "logika.h"
#include "VodaScreenClass.h"
#include "Gui.h"
#include "string.h"

Gui * chat;
extern logika_ItemsTypedef * logika_Items;

void conv_onoff(char * data, int16_t value);

VodaScreenClass::VodaScreenClass()
{

}

VodaScreenClass::~VodaScreenClass()
{

}

void VodaScreenClass::Init(gui_Screen * screen, void * parent)
{
	chat = (Gui*) parent;

	gui_Item pole[7];

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
#define SIZE 8
#define SIZEY 12
#define X1 10
#define X2 (X1+10*SIZE)
#define Y1 45
#define Y2 (Y1 + SIZEY)
	pole[2].SetText("Zacit   ");
	pole[2].SetLowLimit(0);
	pole[2].SetHighLimit(23);
	pole[2].SetValue(10);
	pole[2].SetConvFunction(conv_hours_minutes);
	pole[2].SetPrimaryX(X1);
	pole[2].SetPrimaryY(Y1);

	pole[3].SetText(":");
	pole[3].SetValue(0);
	pole[3].SetHighLimit(59);
	pole[3].SetLowLimit(0);
	pole[3].SetConvFunction(conv_hours_minutes);
	pole[3].SetPrimaryX(X2);
	pole[3].SetPrimaryY(Y1);

	pole[4].SetText("Vypnout ");
	pole[4].SetLowLimit(0);
	pole[4].SetHighLimit(23);
	pole[4].SetValue(10);
	pole[4].SetConvFunction(conv_hours_minutes);
	pole[4].SetPrimaryX(X1);
	pole[4].SetPrimaryY(Y2);

	pole[5].SetText(":");
	pole[5].SetValue(0);
	pole[5].SetHighLimit(59);
	pole[5].SetLowLimit(0);
	pole[5].SetConvFunction(conv_hours_minutes);
	pole[5].SetPrimaryX(X2);
	pole[5].SetPrimaryY(Y2);

	pole[6].SetText("Zpet");
	pole[6].SetPrimaryX(50);
	pole[6].SetPrimaryY(140);
	pole[6].SetShownValue(false);
	pole[6].SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
			SwitchToMenu);
	pole[6].SetConvFunction(conv_dummy);

	screen->AddItems(pole,7);


	logika_Items->VodaSetting.CasH_Start = pole[2].GetValueConstPointer();
	logika_Items->VodaSetting.CasM_Start = pole[3].GetValueConstPointer();
	logika_Items->VodaSetting.CasH_Stop= pole[4].GetValueConstPointer();
	logika_Items->VodaSetting.CasM_Stop = pole[5].GetValueConstPointer();
	logika_Items->VodaSetting.HlidatTeplotu = pole[0].GetValueConstPointer();
	logika_Items->VodaSetting.TeplotaVodyChtena = pole[1].GetValueConstPointer();
}

void conv_onoff(char * data, int16_t value)
{
	const char hoj[2][4] =
	{
	{ "Off" },
	{ " On" } };

	strcpy(data, hoj[value]);
}
