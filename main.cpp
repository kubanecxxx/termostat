#include "ch.hpp"
#include "hal.h"

#include "delayclass.h"
#include "guiInclude.h"
#include "logika.h"
#include "rfmIncludeCpp.h"

/*
 * external interrupt system config
 */
static const EXTConfig extcfg =
{
{
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ FFIT_EXTI },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL } } };

static void blik(void * data);
GUI::Gui * ui;

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

void test(void)
{
	uint8_t checksum = 0;

	rf_writecmd(0);
	rf_prepare();

	for (int i = 0; i < 15; i++)
	{
		rf_send(i);
		checksum += i;
	}
	rf_send(checksum);

	//dummy
	rf_send(0xAA);
	rf_send(0xAA);
	rf_send(0xAA);
}

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

	/*
	 rf_init();
	 rf_fifo_reset();
	 rf_writecmd(0);
	 rf_writecmd(0);
	 rf_writecmd(0);
	 rf_transmitter();
	 */
	//rfm::LinkLayer::Init(1);
	extStart(&EXTD1, &extcfg);
	while (TRUE)
	{
		virtual_timer.Play();
		chThdSleepMilliseconds(1);

		//test();
	}

	return 1;
}

static void blik(void * data)
{
	(void) data;
//led blinking
	palTogglePort(GPIOD, 1 << 13 | 1 << 14);
}

