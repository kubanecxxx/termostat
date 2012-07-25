/*
 * Gui.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUI_H_
#define GUI_H_

#include "framework_cpp/guiGuiBase.h"
#include "delay/delayclass.h"
#include "MainScreenClass.h"
#include "MenuScreenClass.h"
#include "TopeniScreenClass.h"
#include "VodaScreenClass.h"

class Gui: public delay_new //because new override
{
public:
	Gui();
	~Gui();

	MainScreenClass * ScreenMain;
	MenuScreenClass * ScreenMenu;
	TopeniScreenClass * ScreenTopeni;
	TopeniScreenClass * ScreenTopeniVikend;
	VodaScreenClass * ScreenVoda;

	delay_class * del_returnMain;

	void SwitchMenuScreen(void);
	void SwitchMainScreen(void);
	void SwitchVodaScreen(void);
	void SwitchTopeniScreen(void);
	void SwitchTopeniVikendScreen(void)
	{
		TopeniVikendScreen->SetActive();
		gui->print_gui();
	}
	bool IsScreenMainActive()
	{
		return MainScreen->IsActive();
	}

	gui_GuiBase * gui;

	enum Program
	{
		PROGRAM_VYPNOUT = 0, PROGRAM_VODA, PROGRAM_TOPENI, PROGRAM_MANUAL
	};

private:
	delay_class * delej;
	delay_class * del_rtcRefresh;
	delay_class * del_logicRefresh;
	delay_class * del_jenom;
	MainScreenClass cha;
	MenuScreenClass che;
	TopeniScreenClass chi;
	TopeniScreenClass ne;
	VodaScreenClass pi;

	gui_Screen * MainScreen;
	gui_Screen * MenuScreen;
	gui_Screen * TopeniScreen;
	gui_Screen * VodaScreen;
	gui_Screen * TopeniVikendScreen;

};

#endif /* GUI_H_ */
