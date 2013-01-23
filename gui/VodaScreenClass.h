/*
 * VodaScreenClass.h
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#ifndef VODASCREENCLASS_H_
#define VODASCREENCLASS_H_

namespace GUI
{

class VodaScreenClass: public ConversionsClass
{
public:
	VodaScreenClass();
	~VodaScreenClass();
	static void MakeActiveCB(void * item);

	GuiFramework::gui_Item * Teplota;
	GuiFramework::gui_Item * HodinyZacit;
	GuiFramework::gui_Item * MinutyZacit;
	GuiFramework::gui_Item * HodinyKonec;
	GuiFramework::gui_Item * MinutyKonec;
	GuiFramework::gui_Item * HlidatTeplotu;

private:
	static void conv_onoff(char * data, int16_t value);
	static GuiFramework::gui_Screen * screen;

	void CreateHalf();
	void CreateRest();

};

}
#endif /* VODASCREENCLASS_H_ */
