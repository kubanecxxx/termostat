/*
 * MenuScreenClass.h
 *
 *  Created on: 7.7.2012
 *      Author: kubanec
 */

#include "Gui.h"

#ifndef MENUSCREENCLASS_H_
#define MENUSCREENCLASS_H_

void SwitchToTopeni(void*);

class MenuScreenClass
{
public:
	MenuScreenClass();
	~MenuScreenClass();
	void Init(gui_Screen * screen, void * parent);

private:
	gui_Item * Voda;
	gui_Item * Topeni;
	gui_Item * Zpet;
};

#endif /* MENUSCREENCLASS_H_ */
