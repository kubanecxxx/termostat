/*
 * Gui.cppitem.
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "guiInclude.h"

namespace GUI
{
using namespace GuiFramework;

Gui::Gui()
{
	PwmBacklight::Init();
	port::init();

	port::Erase(100 * 1024, 120 * 1024 - 1);

	ScreenMain = new MainScreenClass;
	ScreenMenu = new MenuScreenClass;
	ScreenTopeni = new TopeniScreenClass;
	ScreenTopeniVikend = new TopeniScreenClass(true);
	ScreenVoda = new VodaScreenClass;

	gui_Screen::printActiveScreen();

	rtcClass::Init();
	new delay_class(scan, this, 150);
	new delay_class(rtcClass::TimeShow, this, 20000);
	del_returnMain = new delay_class(ReturnMain, this, 10000);

	rtcClass::TimeShow(this);
}

void Gui::scan(void * data)
{
	Gui * cha = (Gui *) data;
	if (GuiFramework::gui_Screen::ButtonScan())
	{
		cha->del_returnMain->ResetDelay();
	}
}

void Gui::ReturnMain(void * data)
{
	Gui * ui = (Gui*) data;
	PwmBacklight::FadeOut();
	if (!ui->ScreenMain->IsActive())
	{
		ui->ScreenMain->MakeActiveCB();
	}
}
}
