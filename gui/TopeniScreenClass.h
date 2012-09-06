/*
 * TopeniScreenClass.h
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#ifndef TOPENISCREENCLASS_H_
#define TOPENISCREENCLASS_H_

namespace GUI
{
class TopeniScreenClass: public ConversionsClass, public GuiFramework::gui_New
{
public:
	TopeniScreenClass(bool weekend = false);
	~TopeniScreenClass();
	static void MakeActivePoPaCB(void * item);

private:
	void SwitchToTopeniVikend(void * data);

	static GuiFramework::gui_Screen * screenPoPa;
	static GuiFramework::gui_Screen * screenSoNe;
	static void MakeActiveSoNeCB(void * item);

};
}

#endif /* TOPENISCREENCLASS_H_ */