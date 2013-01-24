/*
 * MenuScreenClass.cpp
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#include "guiInclude.h"

namespace GUI
{
using namespace GuiFramework;

gui_Screen * MenuScreenClass::screen;

/**
 * constructor
 */
MenuScreenClass::MenuScreenClass()
{
	screen = new gui_Screen;
	gui_Item pole[4];

	Voda = &pole[0];
	Topeni = &pole[1];
	Zpet = &pole[2];
	gui_Item * save = &pole[3];

	Voda->SetText("Ohrev vody");
	Voda->SetPrimaryX(10);
	Voda->SetPrimaryY(10);
	Voda->SetShownValue(false);
	Voda->SetConvFunction(conv_dummy);
	Voda->SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
			VodaScreenClass::MakeActiveCB);
	Voda = screen->Register(Voda, true);

	Topeni->SetText("Topeni");
	Topeni->SetPrimaryX(10);
	Topeni->SetPrimaryY(25);
	Topeni->SetShownValue(false);
	Topeni->SetConvFunction(conv_dummy);
	Topeni->SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
			TopeniScreenClass::MakeActivePoPaCB);
	Topeni = screen->Register(Topeni, true);

	save->SetText("Ulozit");
	save->SetPrimaryX(10);
	save->SetPrimaryY(40);
	save->SetShownValue(false);
	save->SetConvFunction(conv_dummy);
	save->SetCallback(gui_Item::BUTTON_ENTER,gui_Item::NOTCLICKED, SaveSetup);
	save = screen->Register(save,true);

	Zpet->SetText("Zpet");
	Zpet->SetPrimaryX(50);
	Zpet->SetPrimaryY(140);
	Zpet->SetShownValue(false);
	Zpet->SetConvFunction(conv_dummy);
	Zpet->SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
			MainScreenClass::MakeActiveCB);
	Zpet = screen->Register(Zpet, true);
}

void MenuScreenClass::SaveSetup(void *)
{
	ui->Tabulka->Save();
}

void MenuScreenClass::MakeActiveCB(void * item)
{
	(void) item;
	screen->printScreen();
}
}
