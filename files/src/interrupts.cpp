//#include <__cross_studio_io.h>
#include <stm32f4xx.h>
#include "interrupts.h"

uint32_t TimeCounter = 0;

uint32_t GetTimeCounter()
{
	return TimeCounter;
}

void SysTick_Handler(void)
{
	static unsigned int count = 0;

	TimeCounter++;

	if (count++ == 500)
	{
		GPIOC->ODR ^= GPIO_Pin_8 | GPIO_Pin_9;
		count = 0;
	}
}

void HardFault_Handler(void)
{
	while (1)
		;
}

void MemManage_Handler(void)
{
}
void BusFault_Handler(void)
{
}
void UsageFault_Handler(void)
{
}
void SVC_Handler(void)
{
}

void out_of_memory(void)
{
	while (1)
		;
}

#ifdef  USE_FULL_ASSERT
void assert_failed(unsigned char * file, unsigned long line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/*
	 debug_printf("\n\r Wrong parameter value detected on\r\n");
	 debug_printf("\tfile  %s\r\n", file);
	 debug_printf("\tline  %d\r\n", line);
	 */
}
#endif
