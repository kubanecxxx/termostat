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
	low_level_button_init();
	gui_FlashWrite::Erase(gui_FlashWrite::SEC_8, gui_FlashWrite::SEC_9);

	ScreenMain = new MainScreenClass;
	ScreenMenu = new MenuScreenClass;
	ScreenTopeni = new TopeniScreenClass;
	ScreenTopeniVikend = new TopeniScreenClass(true);
	ScreenVoda = new VodaScreenClass;

	gui_Screen::printActiveScreen();

	rtcClass::Init();
	delej = new delay_class(pica, this, 150);
	del_rtcRefresh = new delay_class(rtcClass::TimeShow, 0, 20000);
	del_jenom = new delay_class(rtcClass::TimeShow, 0, 500, true); //poprvé
	del_returnMain = new delay_class(ReturnMain, this, 10000);
}

void Gui::pica(void * data)
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
	if (!ui->ScreenMain->IsActive())
	{
		ui->ScreenMain->MakeActiveCB();
	}
}
}
