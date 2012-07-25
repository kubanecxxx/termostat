//#include <__cross_studio_io.h>
#include <stm32f4xx.h>
#include "delay/delayclass.h"
#include "gui/Gui.h"
#ifdef TOUCH
#include "ssd1289_lld/ssd1289_lld.h"
#endif

#ifndef TOUCH
#warning pak si hoď zpátky rychlos na 48
#endif

void blik(void * data);
Gui * ui;

int main(void)
{
	GPIO_InitTypeDef GPIO_Struct;
	SystemCoreClockUpdate();
	if (SysTick_Config(SystemCoreClock / 1000))
	{
		while (1)
			;
	}

#ifndef TOUCH
	lcdInit();
#else
	tft_InitLCD();
	tft_ClearScreen(LCD_BLUE);
#endif

	delay_process virtual_timer;
	ui = new Gui();
	delay_class nic(blik, 0, 1000);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_Struct.GPIO_Pin =
			GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_Struct);
#ifdef TOUCH
	tft_InitLCD();
#endif

	while (1)
	{
		virtual_timer.Play();
	}

	return 1;
}

void blik(void * data)
{
	(void) data;

	GPIOD ->ODR ^= GPIO_Pin_13 | GPIO_Pin_14;
}
