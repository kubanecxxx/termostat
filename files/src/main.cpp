//#include <__cross_studio_io.h>
#include <stm32f4xx.h>
#include "delayclass.h"
#include "gui/Gui.h"

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

	lcdInit();

	delay_process delej;
	Gui GUI;
	ui = &GUI;
	delay_class nic(blik, 0, 200);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_Struct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_15;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_Struct);

#ifdef DEBUG
	debug_printf("hello world\n");
#endif

	while (1)
	{
		delej.Play();
	}

	return 1;
}

void blik(void * data)
{
	(void) data;

	GPIOD->ODR ^= GPIO_Pin_13 | GPIO_Pin_14;
}
