#include "ch.hpp"
#include "hal.h"

#include "delayclass.h"
#include "guiInclude.h"
#include "logika.h"

static void blik(void * data);
GUI::Gui * ui;

/*
 class mojeVlakno: public chibios_rt::EnhancedThread<100>
 {
 protected:
 msg_t Main(void)
 {
 while (TRUE)
 {
 blik(NULL);
 chThdSleepMilliseconds(500);
 }
 return 0;
 }
 public:
 mojeVlakno(void) :
 EnhancedThread("test")
 {
 }
 };
 */

int main(void)
{
	chibios_rt::System::Init();
	halInit();

	delay_process virtual_timer;

	ui = new GUI::Gui;

	delay_class refresh_logic(Logic::logika_refresh, ui, 1000);
	delay_class nic(blik, 0, 300);

	//leds
	palSetGroupMode(GPIOD, 0b1111, 12, PAL_MODE_OUTPUT_PUSHPULL);

	palSetPadMode(GPIOE, 4, PAL_MODE_OUTPUT_PUSHPULL);

	//mojeVlakno cha;

	while (TRUE)
	{
		virtual_timer.Play();
		chThdSleepMilliseconds(1);
	}

	return 1;
}

static void blik(void * data)
{
	(void) data;
//led blinking
	palTogglePort(GPIOD, 1 << 13 | 1 << 14);
}

