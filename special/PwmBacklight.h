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
};

#endif /* PWMBACKLIGHT_H_ */
