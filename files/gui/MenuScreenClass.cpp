/*
 * MenuScreenClass.cpp
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#include "MenuScreenClass.h"

Gui * fot;
void SwitchToMain(void*);
void SwitchToVoda(void*);
void SwitchToTopeni(void*);

MenuScreenClass::MenuScreenClass()
{
	// TODO Auto-generated constructor stub

}

MenuScreenClass::~MenuScreenClass()
{
	// TODO Auto-generated destructor stub
}

void MenuScreenClass::Init(gui_Screen * screen, void * parent)
{
	gui_Item pole[3];
	gui_Item * nic;
	fot = (Gui *)parent;


	Voda = &pole[0];
	Topeni = &pole[1];
	Zpet = &pole[2];

	Voda->SetText("Ohrev vody");
	Voda->SetPrimaryX(10);
	Voda->SetPrimaryY(10);
	Voda->SetShownValue(false);
	Voda->SetConvFunction(conv_dummy);
	Voda->SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
			SwitchToVoda);

	Topeni->SetText("Topeni");
	Topeni->SetPrimaryX(10);
	Topeni->SetPrimaryY(25);
	Topeni->SetShownValue(false);
	Topeni->SetConvFunction(conv_dummy);
	Topeni->SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED,
			SwitchToTopeni);

	Zpet->SetText("Zpet");
	Zpet->SetPrimaryX(50);
	Zpet->SetPrimaryY(140);
	Zpet->SetShownValue(false);
	Zpet->SetConvFunction(conv_dummy);
	Zpet->SetCallback(gui_Item::BUTTON_ENTER, gui_Item::NOTCLICKED, SwitchToMain);

	nic = screen->AddItems(pole,3);

	Voda = &nic[0];
	Topeni = &nic[1];
	Zpet = &nic[2];

}

void SwitchToMain(void *data)
{
	fot->SwitchMainScreen();
}

void SwitchToVoda(void *data)
{
	fot->SwitchVodaScreen();
}

void SwitchToTopeni(void *data)
{
	fot->SwitchTopeniScreen();
}
