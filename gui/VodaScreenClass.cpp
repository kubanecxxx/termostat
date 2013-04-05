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
	CreateCas(0, casy[0], 0);
	CreateCas(30, casy[1], 1);
	CreateBack();

}

void VodaScreenClass::CreateBack()
{
	gui_Item pole;
	pole.SetText("Zpet");
	pole.SetPrimaryX(50);
	pole.SetPrimaryY(140);
	pole.SetShownValue(false);
	pole.SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
			MenuScreenClass::MakeActiveCB);
	pole.SetConvFunction(conv_dummy);
	screen->Register(&pole, true);
}

void VodaScreenClass::CreateHalf()
{
	gui_Item pole[2];

	pole[0].SetText("Hlidat t. ");
	pole[0].SetValue(ui->Tabulka->WaterWatchEnable);
	pole[0].SetLowLimit(0);
	pole[0].SetHighLimit(1);
	pole[0].SetConvFunction(conv_onoff);
	pole[0].SetPrimaryX(10);
	pole[0].SetPrimaryY(10);

	pole[1].SetText("Teplota ");
	pole[1].SetValue(ui->Tabulka->WaterTemperature);
	pole[1].SetHighLimit(800);
	pole[1].SetLowLimit(200);
	pole[1].SetPrimaryX(10);
	pole[1].SetPrimaryY(26);
	pole[1].SetStep(5);
	pole[1].SetConvFunction(MainScreenClass::conv_teplota);

	HlidatTeplotu = screen->Register(&pole[0], true);
	Teplota = screen->Register(&pole[1], true);

}

void VodaScreenClass::CreateCas(uint16_t pixel, cas_t & cas, uint8_t table)
{
	gui_Item pole[4];
	gui_Item * it = pole;

	Table::water_time_t & voda = ui->Tabulka->vody[table];

	it->SetText("Zacit   ");
	it->SetLowLimit(0);
	it->SetHighLimit(23);
	it->SetValue(voda.WaterStart.hour);
	it->SetConvFunction(conv_hours_minutes);
	it->SetPrimaryX(X1);
	it->SetPrimaryY(Y1 + pixel);
	it++;

	it->SetText(":");
	it->SetValue(voda.WaterStart.min);
	it->SetHighLimit(59);
	it->SetLowLimit(0);
	it->SetConvFunction(conv_hours_minutes);
	it->SetPrimaryX(X2);
	it->SetPrimaryY(Y1 + pixel);
	it++;

	it->SetText("Vypnout ");
	it->SetLowLimit(0);
	it->SetHighLimit(23);
	it->SetValue(voda.WaterStop.hour);
	it->SetConvFunction(conv_hours_minutes);
	it->SetPrimaryX(X1);
	it->SetPrimaryY(Y2 + pixel);
	it++;

	it->SetText(":");
	it->SetValue(voda.WaterStop.min);
	it->SetHighLimit(59);
	it->SetLowLimit(0);
	it->SetConvFunction(conv_hours_minutes);
	it->SetPrimaryX(X2);
	it->SetPrimaryY(Y2 + pixel);
	it++;

	cas.ZacitH = screen->Register(&pole[0], true);
	cas.ZacitM = screen->Register(&pole[1], true);
	cas.KonecH = screen->Register(&pole[2], true);
	cas.KonecM = screen->Register(&pole[3], true);
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
