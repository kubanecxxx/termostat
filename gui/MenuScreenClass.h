/*
 * MenuScreenClass.h
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#ifndef MENUSCREENCLASS_H_
#define MENUSCREENCLASS_H_

namespace GUI
{

class MenuScreenClass: public GuiFramework::gui_New, public ConversionsClass
{
public:
	MenuScreenClass();
	~MenuScreenClass();
	static void MakeActiveCB(void * item);

private:
	GuiFramework::gui_Item * Voda;
	GuiFramework::gui_Item * Topeni;
	GuiFramework::gui_Item * Zpet;

	static GuiFramework::gui_Screen * screen;

};
}
#endif /* MENUSCREENCLASS_H_ */
