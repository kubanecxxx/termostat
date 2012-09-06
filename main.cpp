#include "ch.h"
#include "hal.h"

#include "delayclass.h"
#include "guiInclude.h"
#include "st7735_2.h"

void blik(void * data);
GUI::Gui * ui;

void HardFaultVector(void)
{
}

int main(void)
{
	chSysInit();
	halInit();

	lcdInit();
	lcdDrawPixel(10, 10, 0x1111);
	while (1)
	{
		lcdDrawPixel(10, 10, 0x1111);
	};

	delay_process virtual_timer;

	ui = new GUI::Gui;
	delay_class nic(blik, 0, 1000);

	//leds
	palSetGroupMode(GPIOD, 0b1111, 12, PAL_MODE_OUTPUT_PUSHPULL);

	palSetPadMode(GPIOE, 4, PAL_MODE_OUTPUT_PUSHPULL);

	while (TRUE)
	{
		virtual_timer.Play();
	}

	return 1;
}

void blik(void * data)
{
	(void) data;
//led blinking
	palTogglePort(GPIOD, 1 << 13 | 1 << 14);
}

