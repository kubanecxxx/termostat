/*
 * MainScreenClass.h
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#ifndef MAINSCREENCLASS_H_
#define MAINSCREENCLASS_H_

#include "framework_cpp/guiGuiBase.h"
void conv_dummy(char * data, int16_t value);
void conv_hours_minutes(char * data, int16_t value);
void SwitchToMenu(void * item);

class MainScreenClass
{
public:
	MainScreenClass();
	~MainScreenClass();
	void Init(gui_Screen * screen,void  * parent);

	gui_Item * Minuty;
	gui_Item * Hodiny;
	gui_Item * Den;
	gui_Item * Program;
	gui_Item * TeplotaManual;
	gui_Item * TeplotaChtena;
	gui_Item * Menu;
	gui_Item * Topi;
	gui_Item * TeplotaDoma;
	gui_Item * TeplotaDole;

private:

};

#endif /* MAINSCREENCLASS_H_ */
