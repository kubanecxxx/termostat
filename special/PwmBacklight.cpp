/**
 * @file PwmBacklight.cpp
 * @author kubanec
 * @date 23.1.2013
 *
 */

#include "ch.h"
#include "hal.h"
#include "PwmBacklight.h"

const PWMConfig PwmBacklight::pwmconfig =
{ 50000, 1000, pwmcb,
{
{ PWM_OUTPUT_ACTIVE_HIGH, NULL },
{ PWM_OUTPUT_DISABLED, NULL },
{ PWM_OUTPUT_DISABLED, NULL },
{ PWM_OUTPUT_DISABLED, NULL } }, 0 };

uint16_t PwmBacklight::BCurrent = 0;
uint16_t PwmBacklight::BFinish = 100;
PwmBacklight::Direction_t PwmBacklight::BDirection = B_UP;

void PwmBacklight::Init()
{
	palSetPadMode(GPIOB, 6, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	pwmStart(&PWMD4, &pwmconfig);

	FadeIn();
}

void PwmBacklight::pwmcb(PWMDriver * pwm)
{
	if (BCurrent == BFinish)
		return;

	if (BDirection == B_UP)
	{
		BCurrent++;
	}
	else
	{
		BCurrent--;
	}

	pwmEnableChannelI(pwm,0,BCurrent * 10);
}

void PwmBacklight::FadeIn()
{
	BFinish = 100;
	BDirection = B_UP;
}

void PwmBacklight::FadeOut()
{
	BFinish = 2;
	BDirection = B_DOWN;
}
