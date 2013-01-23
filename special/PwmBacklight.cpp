/**
 * @file PwmBacklight.cpp
 * @author kubanec
 * @date 23.1.2013
 *
 */

#include "PwmBacklight.h"
#include "ch.h"
#include "hal.h"

const PWMConfig pwmconfig =
{ 50000, 1000, NULL,
{
{ PWM_OUTPUT_ACTIVE_HIGH, NULL },
{ PWM_OUTPUT_DISABLED, NULL },
{ PWM_OUTPUT_DISABLED, NULL },
{ PWM_OUTPUT_DISABLED, NULL } }, 0 };

void PwmBacklight::Init()
{
	palSetPadMode(GPIOB, 6, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	pwmStart(&PWMD4, &pwmconfig);
	pwmEnableChannel(&PWMD4, 0, 20);

}

void PwmBacklight::FadeIn()
{

}

void PwmBacklight::FadeOut()
{

}
