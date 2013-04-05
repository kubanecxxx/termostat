#include "ch.hpp"
#include "hal.h"

#include "delayclass.h"
#include "guiInclude.h"
#include "logika.h"
#include "rfmIncludeCpp.h"
#include "Wireless.h"

void* operator new(size_t sz)
{
	void * temp;
	temp = chCoreAlloc(sz);
	if (temp == NULL)
		asm ("bkpt");

	return temp;
}

void operator delete(void* m)
{
	(void) m;
}

GUI::Gui * ui;
delay_class * refresh_logic;

int main(void)
{
	halInit();
	chibios_rt::System::Init();
	chRegSetThreadName("Main");

	rccDisableAPB2(0b111 < 4, 1);
	ui = new GUI::Gui;
	new Wireless;

	chThdSetPriority(NORMALPRIO - 1);
	refresh_logic = new delay_class(Logic::logika_refresh, ui, 3000);

	while (TRUE)
	{
		delay_process::Play();
		chThdSleepMilliseconds(1);
	}
}

