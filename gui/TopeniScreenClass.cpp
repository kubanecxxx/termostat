/*
 * TopeniScreenClass.cpp
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#include "guiInclude.h"

namespace GUI
{

using namespace GuiFramework;
//extern logika_ItemsTypedef * logika_Items;

gui_Screen * TopeniScreenClass::screenPoPa = NULL;
gui_Screen * TopeniScreenClass::screenSoNe = NULL;

void SwitchToTopeniVikend(void * data);

TopeniScreenClass::TopeniScreenClass(bool weekend)
{
	gui_Screen * screen = new gui_Screen;

	if (!weekend)
		screenPoPa = screen;
	else
		screenSoNe = screen;

	for (int i = 0; i < 4; i++)
	{
		CreateRow(i, screen);
		if (weekend && i == 1)
			break;
	}

	if (weekend)
	{
		Hodiny[0]->GetSecondaryCoordinates()->SetY(49);
		Minuty[0]->GetSecondaryCoordinates()->SetY(49);
	}
	else
	{
		Hodiny[0]->GetSecondaryCoordinates()->SetY(97);
		Minuty[0]->GetSecondaryCoordinates()->SetY(97);
	}

	CreateRest(weekend, screen);
}

void TopeniScreenClass::CreateRest(bool weekend, gui_Screen * screen)
{
	gui_Item items[2];
	//po-pa
	if (weekend)
	{
		items[1].SetText("So-Ne");
		items[1].SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
				MakeActivePoPaCB);
	}
	else
	{
		items[1].SetText("Po-Pa");
		items[1].SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
				MakeActiveSoNeCB);
	}
	items[1].SetShownValue(false);
	items[1].SetPrimaryX(10);
	items[1].SetPrimaryY(10);
	items[1].SetConvFunction(conv_dummy);

	//zpet
	items[0].SetText("Zpet");
	items[0].SetShownValue(false);
	items[0].SetPrimaryX(50);
	items[0].SetPrimaryY(140);
	items[0].SetConvFunction(conv_dummy);
	items[0].SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
			MenuScreenClass::MakeActiveCB);

	screen->Register(&items[0], true);
	screen->Register(&items[1], true);
}

#define SIZE 8
#define SIZEY 12
#define X1 10
#define X2 (X1+2*SIZE)
#define X3 (X1+8*SIZE)
#define X4 (X1+10*SIZE)
#define Y1 25
#define Y2 (Y1 + 2 * SIZEY)
#define Y3 (Y1 + 4 * SIZEY)
#define Y4 (Y1 + 6 * SIZEY)

#define T1 (Y1 + SIZEY)
#define T2 (Y1 + 3*SIZEY)
#define T3 (Y1 + 5*SIZEY)
#define T4 (Y1 + 7*SIZEY)
#define XT 50

void TopeniScreenClass::CreateRow(int i, gui_Screen * screen)
{
	gui_Item items[3];

	int16_t hodiny;
	int16_t minuty;
	int16_t teplota;
	Table::time_temp_t * temp;

	if (screen == screenPoPa)
		temp = &ui->Tabulka->PoPa[i];
	else
		temp = &ui->Tabulka->SoNe[i];

	hodiny = temp->time.hour;
	minuty = temp->time.min;
	teplota = temp->temperature;

	//hodiny
	items[0].SetPrimaryX(X1);
	items[0].SetPrimaryY(Y1 + 2 * i * SIZEY);
	items[0].SetLowLimit(0);
	items[0].SetHighLimit(23);
	items[0].SetValue(hodiny);
	items[0].SetConvFunction(conv_hours_minutes);
	items[0].AddSecondaryCoor(10, 10, screen);
	items[0].SetText("");

	items[0].GetSecondaryCoordinates()->SetX(X3);
	items[0].GetSecondaryCoordinates()->SetY(Y1 + 2 * (i - 1) * SIZEY);
	Hodiny[i] = screen->Register(&items[0], true);

	//minuty
	items[1].SetPrimaryX(X2);
	items[1].SetPrimaryY(Y1 + 2 * i * SIZEY);
	items[1].SetLowLimit(0);
	items[1].SetHighLimit(59);
	items[1].SetValue(minuty);
	items[1].SetConvFunction(conv_hours_minutes);
	items[1].AddSecondaryCoor(10, 10, screen);
	items[1].SetText(":");
	items[1].GetSecondaryCoordinates()->SetX(X4);
	items[1].GetSecondaryCoordinates()->SetY(Y1 + 2 * (i - 1) * SIZEY);
	Minuty[i] = screen->Register(&items[1], true);

	//teploty
	items[2].SetPrimaryX(XT);
	items[2].SetPrimaryY(Y1 + (2 * i + 1) * SIZEY);
	items[2].SetLowLimit(10);
	items[2].SetHighLimit(35);
	items[2].SetValue(teplota);
	items[2].SetConvFunction(conv_hours_minutes);
	items[2].SetText("T:");
	Teploty[i] = screen->Register(&items[2], true);
}

void TopeniScreenClass::MakeActivePoPaCB(void * item)
{
	(void) item;
	screenPoPa->printScreen();
}

void TopeniScreenClass::MakeActiveSoNeCB(void * data)
{
	(void) data;
	screenSoNe->printScreen();
}
}

