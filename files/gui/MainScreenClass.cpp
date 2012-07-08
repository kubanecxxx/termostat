/*
 * MainScreenClass.cpp
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#include "Gui.h"
#include "MainScreenClass.h"
#include "string.h"
#include "rtc.h"

void conv_hours_minutes(char * data, int16_t value);
void conv_days(char* data, int16_t value);
void conv_program(char* data, int16_t value);
void conv_topit(char * data, int16_t value);
void conv_dummy(char * data, int16_t value);

Gui * fotr;

void MainScreenClass::Init(gui_Screen * screen, void * parent)
{
	gui_Item cha[10];
	gui_Label be[4];

	gui_Item * chaj;
	gui_Label * Doma;
	gui_Label * Dole;

	fotr = (Gui *) parent;

	Hodiny = &cha[0];
	Minuty = &cha[1];
	Den = &cha[2];
	Program = &cha[3];
	TeplotaManual = &cha[4];
	TeplotaChtena = &cha[5];
	Menu = &cha[6];
	Topi = &cha[7];

	TeplotaDole = &cha[8];
	TeplotaDoma = &cha[9];

	Doma = &be[0];
	Dole = &be[1];

	Hodiny->SetText("");
	Hodiny->SetHighLimit(23);
	Hodiny->SetLowLimit(0);
	Hodiny->SetValue(2);
	Hodiny->SetConvFunction(conv_hours_minutes);
	Hodiny->SetValueRounding(true);
	Hodiny->SetPrimaryX(10);
	Hodiny->SetPrimaryY(10);
	Hodiny->SetCallback(gui_Item::BUTTON_DOWN, gui_Item::CLICKED,
			rtc_CallbackDown);
	Hodiny->SetCallback(gui_Item::BUTTON_UP, gui_Item::CLICKED, rtc_CallbackUp);

	Minuty->SetText(":");
	Minuty->SetHighLimit(59);
	Minuty->SetLowLimit(0);
	Minuty->SetValue(10);
	Minuty->SetConvFunction(conv_hours_minutes);
	Minuty->SetValueRounding(true);
	Minuty->SetPrimaryX(26);
	Minuty->SetPrimaryY(10);
	Minuty->SetCallback(gui_Item::BUTTON_DOWN, gui_Item::CLICKED,
			rtc_CallbackDown);
	Minuty->SetCallback(gui_Item::BUTTON_UP, gui_Item::CLICKED, rtc_CallbackUp);

	Den->SetText("");
	Den->SetPrimaryX(100);
	Den->SetPrimaryY(10);
	Den->SetValue(1);
	Den->SetLowLimit(1);
	Den->SetHighLimit(7);
	Den->SetValueRounding(true);
	Den->SetConvFunction(conv_days);
	Den->SetCallback(gui_Item::BUTTON_DOWN, gui_Item::CLICKED,
			rtc_CallbackDown);
	Den->SetCallback(gui_Item::BUTTON_UP, gui_Item::CLICKED, rtc_CallbackUp);

	Program->SetLowLimit(0);
	Program->SetHighLimit(3);
	Program->SetValue(0);
	Program->SetPrimaryX(10);
	Program->SetPrimaryY(25);
	Program->SetConvFunction(conv_program);
	Program->SetFontSize(16);
	Program->SetValueRounding(true);
	Program->SetText("");

	TeplotaManual->SetText("");
	TeplotaManual->SetPrimaryX(80);
	TeplotaManual->SetPrimaryY(50);
	TeplotaManual->SetLowLimit(10);
	TeplotaManual->SetHighLimit(35);
	TeplotaManual->SetFontSize(16);
	TeplotaManual->SetShownGlobal(false);
	TeplotaManual->SetValue(25);
	TeplotaManual->SetConvFunction(conv_hours_minutes);

	TeplotaChtena->SetConvFunction(conv_hours_minutes);
	TeplotaChtena->SetText("");
	TeplotaChtena->SetPrimaryX(10);
	TeplotaChtena->SetPrimaryY(50);
	TeplotaChtena->SetFontSize(16);
	TeplotaChtena->SetChoseable(false);
	TeplotaChtena->SetShownGlobal(false);
	TeplotaChtena->SetValue(10);

	Menu->SetText("MENU");
	Menu->SetPrimaryX(10);
	Menu->SetPrimaryY(140);
	Menu->SetShownValue(false);
	Menu->SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
			SwitchToMenu);
	Menu->SetConvFunction(conv_dummy);

	Topi->SetPrimaryX(60);
	Topi->SetPrimaryY(140);
	Topi->SetTextColor(0x8000);
	Topi->SetValue(0);
	Topi->SetChoseable(false);
	Topi->SetConvFunction(conv_topit);
	Topi->SetText("");
	Topi->SetUseDefaultTextColor(false);

	TeplotaDole->SetPrimaryX(50);
	TeplotaDole->SetPrimaryY(110);
	TeplotaDole->SetText("");
	TeplotaDole->SetFontSize(16);
	TeplotaDole->SetChoseable(false);
	TeplotaDole->SetValue(40);
	TeplotaDole->SetConvFunction(conv_hours_minutes);

	TeplotaDoma->SetPrimaryX(50);
	TeplotaDoma->SetPrimaryY(80);
	TeplotaDoma->SetFontSize(16);
	TeplotaDoma->SetChoseable(false);
	TeplotaDoma->SetText("");
	TeplotaDoma->SetValue(23);
	TeplotaDoma->SetConvFunction(conv_hours_minutes);

	Doma->SetPrimaryX(10);
	Doma->SetPrimaryY(84);
	Doma->SetText("Doma");

	Dole->SetPrimaryX(10);
	Dole->SetPrimaryY(114);
	Dole->SetText("Voda");

	be[2].SetText("~C");
	be[2].SetPrimaryX(82);
	be[2].SetPrimaryY(80);
	be[2].AddSecondaryCoor(82, 110, screen);
	be[2].SetFontSize(16);

	chaj = screen->AddItems(cha, 10);
	screen->AddLabels(be, 3);

	Hodiny = &chaj[0];
	Minuty = &chaj[1];
	Den = &chaj[2];
	Program = &chaj[3];
	TeplotaManual = &chaj[4];
	TeplotaChtena = &chaj[5];
	Menu = &chaj[6];
	Topi = &chaj[7];
	TeplotaDole = &chaj[8];
	TeplotaDoma = &chaj[9];

	rtc_Init();
}

void conv_hours_minutes(char * data, int16_t value)
{
	data[2] = 0;
	data[0] = value / 10 + '0';
	data[1] = value % 10 + '0';
}

MainScreenClass::MainScreenClass()
{

}

void conv_days(char* data, int16_t value)
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

MainScreenClass::~MainScreenClass()
{

}

void conv_dummy(char * data, int16_t value)
{
	data[0] = '\0';
}

void conv_topit(char * data, int16_t value)
{
	const char top[2][10] =
	{
	{ "Netopim" },
	{ "Topim  " } };
	strcpy(data, top[value]);
}

void conv_program(char* data, int16_t value)
{
	const char programy[4][8] =
	{
	{ "Vypnuto" },
	{ "Voda   " },
	{ "Topeni " },
	{ "Manual " } };

	strcpy(data, programy[value]);
}

void SwitchToMenu(void * data)
{
	fotr->SwitchMenuScreen();
}
