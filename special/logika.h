/*
 * logika.h
 *
 *  Created on: 28.5.2012
 *      Author: kubanec
 */

#ifndef LOGIKA_H_
#define LOGIKA_H_

class Logic
{
public:
	typedef enum
	{
		PROGRAM_VYPNOUT = 0, PROGRAM_VODA, PROGRAM_TOPENI, PROGRAM_MANUAL
	} Program_t;

	typedef enum
	{
		TOPIT = 1, NETOPIT = 0
	} logika_KotelStateTypedef;

	static logika_KotelStateTypedef logika_GetKotelState(void);
	static void logika_refresh(void * data);

private:
	static logika_KotelStateTypedef logika_GetKotelVodaState(void);
	static logika_KotelStateTypedef logika_GetKotelTopeniState(
			int16_t & teplota);
	static logika_KotelStateTypedef logika_GetKotelManualState(void);
	static logika_KotelStateTypedef logika_KrucialniPodminka(int16_t Cas,
			int16_t CasStart, int16_t CasKonec);

	static GUI::Gui * ui;
	static logika_KotelStateTypedef Kotel;
};

#endif /* LOGIKA_H_ */
