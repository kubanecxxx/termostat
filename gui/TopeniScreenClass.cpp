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

void SwitchToTopeniVikend(void * data);

gui_Screen * TopeniScreenClass::screenPoPa;
gui_Screen * TopeniScreenClass::screenSoNe;

TopeniScreenClass::TopeniScreenClass(bool weekend)
{
	gui_Screen * screen = new gui_Screen;
	gui_Item items[14];

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

	for (int i = 0; i < 4; i++)
	{
		//hodiny
		items[3 * i].SetPrimaryX(X1);
		items[3 * i].SetPrimaryY(Y1 + 2 * i * SIZEY);
		items[3 * i].SetLowLimit(0);
		items[3 * i].SetHighLimit(23);
		items[3 * i].SetValue(i);
		items[3 * i].SetConvFunction(conv_hours_minutes);
		items[3 * i].AddSecondaryCoor(10, 10, screen);
		items[3 * i].SetText("");

		items[3 * i].GetSecondaryCoordinates()->SetX(X3);
		items[3 * i].GetSecondaryCoordinates()->SetY(Y1 + 2 * (i - 1) * SIZEY);
		Hodiny[i] = screen->Register(&items[3 * i], true);

		//minuty
		items[3 * i + 1].SetPrimaryX(X2);
		items[3 * i + 1].SetPrimaryY(Y1 + 2 * i * SIZEY);
		items[3 * i + 1].SetLowLimit(0);
		items[3 * i + 1].SetHighLimit(59);
		items[3 * i + 1].SetValue(i * 5);
		items[3 * i + 1].SetConvFunction(conv_hours_minutes);
		items[3 * i + 1].AddSecondaryCoor(10, 10, screen);
		items[3 * i + 1].SetText(":");
		items[3 * i + 1].GetSecondaryCoordinates()->SetX(X4);
		items[3 * i + 1].GetSecondaryCoordinates()->SetY(
				Y1 + 2 * (i - 1) * SIZEY);
		Minuty[i] = screen->Register(&items[3 * i + 1], true);

		//teploty
		items[3 * i + 2].SetPrimaryX(XT);
		items[3 * i + 2].SetPrimaryY(Y1 + (2 * i + 1) * SIZEY);
		items[3 * i + 2].SetLowLimit(10);
		items[3 * i + 2].SetHighLimit(35);
		items[3 * i + 2].SetValue(3 * i);
		items[3 * i + 2].SetConvFunction(conv_hours_minutes);
		items[3 * i + 2].SetText("T:");
		Teploty[i] = screen->Register(&items[3 * i + 2], true);

		if (!weekend)
		{
			screenPoPa = screen;
		}
		else
		{
			screenSoNe = screen;
		}

		if (weekend && i == 1)
			break;
	}

	if (weekend)
	{
		items[0].GetSecondaryCoordinates()->SetY(49);
		items[1].GetSecondaryCoordinates()->SetY(49);
	}
	else
	{
		items[0].GetSecondaryCoordinates()->SetY(97);
		items[1].GetSecondaryCoordinates()->SetY(97);
	}

	//po-pa
	int temp = 0;
	if (weekend)
	{
		temp = 7;
		items[temp].SetText("So-Ne");
		items[temp].SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
				MakeActivePoPaCB);
	}
	else
	{
		temp = 13;
		items[temp].SetText("Po-Pa");
		items[temp].SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
				MakeActiveSoNeCB);
	}
	items[temp].SetShownValue(false);
	items[temp].SetPrimaryX(10);
	items[temp].SetPrimaryY(10);
	items[temp].SetConvFunction(conv_dummy);

	//zpet
	items[temp - 1].SetText("Zpet");
	items[temp - 1].SetShownValue(false);
	items[temp - 1].SetPrimaryX(50);
	items[temp - 1].SetPrimaryY(140);
	items[temp - 1].SetConvFunction(conv_dummy);
	items[temp - 1].SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
			MenuScreenClass::MakeActiveCB);

	screen->Register(&items[temp - 1], true);
	screen->Register(&items[temp], true);
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

