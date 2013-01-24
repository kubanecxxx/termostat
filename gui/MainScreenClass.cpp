/*
 * MainScreenClass.cpp
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#include "guiInclude.h"
#include "logika.h"
#include "Wireless.h"

namespace GUI
{
using namespace GuiFramework;

gui_Screen * MainScreenClass::screen;

bool MainScreenClass::IsActive()
{
	return (screen == gui_Screen::GetActiveScreen());
}

void MainScreenClass::MakeActiveCB(void * item)
{
	(void) item;
	screen->printScreen();
}

const uint16_t SKOLOR = 0x07E0;

/**
 * vytvořit screen
 * najebat do něho všecko
 */
MainScreenClass::MainScreenClass()
{
	screen = new gui_Screen;
	CreateHours();
	CreateTemps();
	CreateRest();

	Temperature::Init();

	new delay_class(RefreshTemp, this, 5000);
}

void MainScreenClass::CreateHours(void)
{
	gui_Item cha[3];
	Hodiny = &cha[0];
	Minuty = &cha[1];
	Den = &cha[2];

	Hodiny->SetText("");
	Hodiny->SetHighLimit(23);
	Hodiny->SetLowLimit(0);
	Hodiny->SetValue(2);
	Hodiny->SetConvFunction(conv_hours_minutes);
	Hodiny->SetValueRounding(true);
	Hodiny->SetPrimaryX(10);
	Hodiny->SetPrimaryY(10);
	Hodiny->SetTextColor(SKOLOR);
	Hodiny->SetUseDefaultTextColor(false);
	Hodiny->SetCallback(gui_Item::BUTTON_DOWN, gui_Item::CLICKED,
			rtcClass::CallbackDown);
	Hodiny->SetCallback(gui_Item::BUTTON_UP, gui_Item::CLICKED,
			rtcClass::CallbackUp);
	Hodiny = screen->Register(Hodiny, true);

	Minuty->SetText(":");
	Minuty->SetHighLimit(59);
	Minuty->SetLowLimit(0);
	Minuty->SetValue(10);
	Minuty->SetConvFunction(conv_hours_minutes);
	Minuty->SetValueRounding(true);
	Minuty->SetPrimaryX(26);
	Minuty->SetPrimaryY(10);
	Minuty->SetCallback(gui_Item::BUTTON_DOWN, gui_Item::CLICKED,
			rtcClass::CallbackDown);
	Minuty->SetCallback(gui_Item::BUTTON_UP, gui_Item::CLICKED,
			rtcClass::CallbackUp);
	Minuty->SetTextColor(SKOLOR);
	Minuty->SetUseDefaultTextColor(false);
	Minuty = screen->Register(Minuty, true);

	Den->SetText("");
	Den->SetPrimaryX(100);
	Den->SetPrimaryY(10);
	Den->SetValue(1);
	Den->SetLowLimit(1);
	Den->SetHighLimit(7);
	Den->SetValueRounding(true);
	Den->SetConvFunction(conv_days);
	Den->SetCallback(gui_Item::BUTTON_DOWN, gui_Item::CLICKED,
			rtcClass::CallbackDown);
	Den->SetCallback(gui_Item::BUTTON_UP, gui_Item::CLICKED,
			rtcClass::CallbackUp);
	Den = screen->Register(Den, true);
}

void MainScreenClass::CreateTemps(void)
{
	gui_Item cha[4];
	Program = &cha[0];
	TeplotaManual = &cha[1];
	TeplotaChtena = &cha[2];
	Menu = &cha[3];

	Program->SetLowLimit(0);
	Program->SetHighLimit(3);
	Program->SetValue(ui->Tabulka->Program);
	Program->SetPrimaryX(10);
	Program->SetPrimaryY(25);
	Program->SetConvFunction(conv_program);
	Program->SetFontSize(16);
	Program->SetValueRounding(true);
	Program->SetText("");
	Program = screen->Register(Program, true);

	TeplotaManual->SetText("");
	TeplotaManual->SetPrimaryX(80);
	TeplotaManual->SetPrimaryY(50);
	TeplotaManual->SetLowLimit(10);
	TeplotaManual->SetHighLimit(35);
	TeplotaManual->SetFontSize(16);
	TeplotaManual->SetShownGlobal(false);
	TeplotaManual->SetValue(ui->Tabulka->ManualTemp);
	TeplotaManual->SetConvFunction(conv_hours_minutes);
	TeplotaManual = screen->Register(TeplotaManual, true);

	TeplotaChtena->SetConvFunction(conv_hours_minutes);
	TeplotaChtena->SetText("");
	TeplotaChtena->SetPrimaryX(10);
	TeplotaChtena->SetPrimaryY(50);
	TeplotaChtena->SetFontSize(16);
	TeplotaChtena->SetChoseable(false);
	TeplotaChtena->SetShownGlobal(false);
	TeplotaChtena->SetValue(10);
	TeplotaChtena = screen->Register(TeplotaChtena, true);

	Menu->SetText("MENU");
	Menu->SetPrimaryX(10);
	Menu->SetPrimaryY(140);
	Menu->SetShownValue(false);
	// enter the menu
	Menu->SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
			MenuScreenClass::MakeActiveCB);
	Menu->SetConvFunction(conv_dummy);
	Menu = screen->Register(Menu, true);
}

void MainScreenClass::CreateRest(void)
{
	gui_Item cha[3];

	Topi = &cha[0];
	TeplotaDole = &cha[1];
	TeplotaDoma = &cha[2];

	Topi->SetPrimaryX(60);
	Topi->SetPrimaryY(140);
	Topi->SetTextColor(SKOLOR);
	Topi->SetValue(0);
	Topi->SetChoseable(false);
	Topi->SetConvFunction(conv_topit);
	Topi->SetText("");
	Topi->SetUseDefaultTextColor(false);
	Topi = screen->Register(Topi, true);

	TeplotaDole->SetPrimaryX(50);
	TeplotaDole->SetPrimaryY(110);
	TeplotaDole->SetText("");
	TeplotaDole->SetFontSize(16);
	TeplotaDole->SetChoseable(false);
	TeplotaDole->SetValue(40);
	TeplotaDole->SetConvFunction(conv_hours_minutes);
	TeplotaDole = screen->Register(TeplotaDole, true);

	TeplotaDoma->SetPrimaryX(50);
	TeplotaDoma->SetPrimaryY(80);
	TeplotaDoma->SetFontSize(16);
	TeplotaDoma->SetChoseable(false);
	TeplotaDoma->SetText("");
	TeplotaDoma->SetValue(23);
	TeplotaDoma->SetConvFunction(conv_hours_minutes);
	TeplotaDoma = screen->Register(TeplotaDoma, true);

	gui_Label be[4];

	gui_Label * Doma;
	gui_Label * Dole;

	Doma = &be[0];
	Dole = &be[1];

	Doma->SetPrimaryX(10);
	Doma->SetPrimaryY(84);
	Doma->SetText("Doma");
	Doma = screen->Register(Doma, true);

	Dole->SetPrimaryX(10);
	Dole->SetPrimaryY(114);
	Dole->SetText("Voda");
	Dole = screen->Register(Dole, true);

	be[2].SetText("~C");
	be[2].SetPrimaryX(82);
	be[2].SetPrimaryY(80);
	be[2].AddSecondaryCoor(82, 110, screen);
	be[2].SetFontSize(16);

	screen->Register(&be[2], true);
}

void MainScreenClass::RefreshTemp(void * data)
{
	MainScreenClass * scren = (MainScreenClass*) data;
	static int16_t prev;

	Temperature::RefreshTemperature();
	int16_t temp = Temperature::GetTemperature();
	//if (prev != temp)
	{
		scren->TeplotaDoma->SetValue(temp);
		scren->TeplotaDoma->print();
		prev = temp;

		scren->TeplotaDole->SetValue(Wireless::GetTemperature());
		scren->TeplotaDole->print();
	}
}

void MainScreenClass::conv_days(char* data, int16_t value)
{
	const char dny[7][3] =
	{
	{ "Po" },
	{ "Ut" },
	{ "St" },
	{ "Ct" },
	{ "Pa" },
	{ "So" },
	{ "Ne" } };

	strcpy(data, dny[value - 1]);
}

void MainScreenClass::conv_topit(char * data, int16_t value)
{
	if (value == Logic::TOPIT)
		strcpy(data, "Topim  ");
	else if (value == Logic::NETOPIT)
		strcpy(data, "Netopim");
	else
		strcpy(data, "");
}

void MainScreenClass::conv_program(char* data, int16_t value)
{
	if (value == Logic::PROGRAM_VYPNOUT)
		strcpy(data, "Vypnuto");
	else if (value == Logic::PROGRAM_TOPENI)
		strcpy(data, "Topeni ");
	else if (value == Logic::PROGRAM_VODA)
		strcpy(data, "Voda   ");
	else if (value == Logic::PROGRAM_MANUAL)
		strcpy(data, "Manual ");
	else
		strcpy(data, "");
}

}
