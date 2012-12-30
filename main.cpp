#include "ch.hpp"
#include "hal.h"

#include "delayclass.h"
#include "guiInclude.h"
#include "logika.h"
#include "rfmIncludeCpp.h"
#include "Wireless.h"

void* operator new(size_t sz)
{
	return chCoreAlloc(sz);
}

void operator delete(void* m)
{
	(void) m;
}

GUI::Gui * ui;

int main(void)
{
	chibios_rt::System::Init();
	halInit();
	delay_process virtual_timer;
	ui = new GUI::Gui;
	new Wireless;
	chThdSetPriority(NORMALPRIO -1 );
	delay_class refresh_logic(Logic::logika_refresh, ui, 3000);

	//leds
	palSetGroupMode(GPIOD, 0b1111, 12, PAL_MODE_OUTPUT_PUSHPULL);

	while (TRUE)
	{
		virtual_timer.Play();
		chThdSleepMilliseconds(1);
	}

	return 1;
}


