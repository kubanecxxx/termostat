/*
 * MainScreenClass.h
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#ifndef MAINSCREENCLASS_H_
#define MAINSCREENCLASS_H_

namespace GUI
{

class MainScreenClass:
		public ConversionsClass,
		public Temperature
{
public:
	MainScreenClass();
	static void MakeActiveCB(void * item = NULL);
	static bool IsActive();

	GuiFramework::gui_Item * Minuty;
	GuiFramework::gui_Item * Hodiny;
	GuiFramework::gui_Item * Den;
	GuiFramework::gui_Item * Program;
	GuiFramework::gui_Item * TeplotaManual;
	GuiFramework::gui_Item * TeplotaChtena;
	GuiFramework::gui_Item * Menu;
	GuiFramework::gui_Item * Topi;
	GuiFramework::gui_Item * TeplotaDoma;
	GuiFramework::gui_Item * TeplotaDole;

private:
	static GuiFramework::gui_Screen * screen;
	static void conv_days(char* data, int16_t value);
	static void conv_program(char* data, int16_t value);
	static void conv_topit(char * data, int16_t value);
	static void RefreshTemp(void * data);

	void CreateHours(void);
	void CreateTemps(void);
	void CreateRest(void);
};
}

#endif /* MAINSCREENCLASS_H_ */
