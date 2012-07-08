/*
 * Gui.cppitem.
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#include "Gui.h"
#include "string.h"
#include "rtc.h"
#include "logika.h"

void pica(void * data);
void ReturnMain(void * data);

Gui::Gui()
{
	constructor();
}

Gui::~Gui()
{

}

void Gui::constructor()
{
	gui = (gui_GuiBase*) super_malloc(sizeof(gui_GuiBase));
	gui->constructor();
	MainScreen = gui->MakeScreen();
	MenuScreen = gui->MakeScreen();
	VodaScreen = gui->MakeScreen();
	TopeniScreen = gui->MakeScreen();
	TopeniVikendScreen = gui->MakeScreen();

	ScreenMain = &cha;
	ScreenMenu = &che;
	ScreenTopeni = &chi;
	ScreenTopeniVikend = &ne;
	ScreenVoda = &pi;

	gui_FlashWrite flash;
	flash.Erase(ADDR_FLASH_SECTOR_8, ADDR_FLASH_SECTOR_9);

	ScreenTopeni->Init(TopeniScreen, this, false);
	ScreenMain->Init(MainScreen, this);
	ScreenMenu->Init(MenuScreen, this);
	ScreenTopeniVikend->Init(TopeniVikendScreen, this, true);
	ScreenVoda->Init(VodaScreen, this);

	gui->print_gui();

	delej = (delay_class *) super_malloc(sizeof(delay_class));
	del_rtcRefresh = (delay_class *) super_malloc(sizeof(delay_class));
	del_logicRefresh = (delay_class *) super_malloc(sizeof(delay_class));
	del_jenom = (delay_class *) super_malloc(sizeof(delay_class));
	del_returnMain = (delay_class *) super_malloc(sizeof(delay_class));

	del_rtcRefresh->constructor(RTC_TimeShow, 0, 20000);
	delej->constructor(pica, this, 150);
	del_logicRefresh->constructor(logika_refresh, 0, 1000);
	del_jenom->constructor(RTC_TimeShow, 0, 500, true);
	del_returnMain->constructor(ReturnMain, this, 10000);
}

void Gui::SwitchMainScreen(void)
{
	MainScreen->SetActive();
	gui->print_gui();
}

void Gui::SwitchMenuScreen(void)
{
	MenuScreen->SetActive();
	gui->print_gui();
}

void Gui::SwitchTopeniScreen()
{
	TopeniScreen->SetActive();
	gui->print_gui();
}

void Gui::SwitchVodaScreen()
{
	VodaScreen->SetActive();
	gui->print_gui();
}

void pica(void * data)
{
	Gui * cha = (Gui *) data;
	if (cha->gui->ButtonScan())
	{
		cha->del_returnMain->ResetDelay();
	}
}

void ReturnMain(void * data)
{
	Gui * cha = (Gui *) data;

	if (!cha->IsScreenMainActive())
	{
		cha->SwitchMainScreen();
	}
}
