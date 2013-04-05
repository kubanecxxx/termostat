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

	typedef struct
	{
		GuiFramework::gui_Item * ZacitH;
		GuiFramework::gui_Item * ZacitM;
		GuiFramework::gui_Item * KonecH;
		GuiFramework::gui_Item * KonecM;
	} cas_t;

	GuiFramework::gui_Item * Teplota;
	GuiFramework::gui_Item * HlidatTeplotu;

	cas_t casy[2];

private:
	static void conv_onoff(char * data, int16_t value);
	static GuiFramework::gui_Screen * screen;

	void CreateHalf();
	void CreateCas(uint16_t pixels, cas_t & cas , uint8_t table);
	void CreateBack();

};

}
#endif /* VODASCREENCLASS_H_ */
