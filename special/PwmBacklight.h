/**
 * @file PwmBacklight.h
 * @author kubanec
 * @date 23.1.2013
 *
 */

#ifndef PWMBACKLIGHT_H_
#define PWMBACKLIGHT_H_

class PwmBacklight
{
public:
	static void Init(void);
	static void FadeIn(void);
	static void FadeOut(void);

private:
	static uint16_t BCurrent;
	static uint16_t BFinish;

	typedef enum {B_UP, B_DOWN} Direction_t;
	static Direction_t BDirection;

	static void pwmcb(PWMDriver * pwm);
	const static PWMConfig pwmconfig;
};

#endif /* PWMBACKLIGHT_H_ */
