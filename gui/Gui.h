/*
 * Gui.h
 *
 *  Created on: 4.7.2012
 *      Author: kubanec
 */

#ifndef GUI_H_
#define GUI_H_

namespace GUI
{

class Gui
{
public:

	Gui();

	MainScreenClass * ScreenMain;
	MenuScreenClass * ScreenMenu;
	TopeniScreenClass * ScreenTopeni;
	TopeniScreenClass * ScreenTopeniVikend;
	VodaScreenClass * ScreenVoda;

	delay_class * del_returnMain;

private:


	static void pica(void * data);
	static void ReturnMain(void * data);
};
}

#endif /* GUI_H_ */
