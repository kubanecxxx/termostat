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

	enum Program
	{
		PROGRAM_VYPNOUT = 0, PROGRAM_VODA, PROGRAM_TOPENI, PROGRAM_MANUAL
	};

	typedef enum
	{
		TOPIT = 1, NETOPIT = 0
	} logika_KotelStateTypedef;

	typedef struct logika_ItemTypedef
	{
		const int16_t * CasH;
		const int16_t * CasM;
		const int16_t * Teplota;
	} logika_ItemTypedef;

	typedef struct logika_TopeniTypedef
	{
		logika_ItemTypedef PoPa[4];
		logika_ItemTypedef SoNe[2];
	} logika_TopeniTypedef;

	typedef struct logika_ItemsTypedef
	{
		logika_TopeniTypedef TopeniSetting;
	} logika_ItemsTypedef;

	void logika_Connect(const logika_ItemsTypedef * logika_Items);
	logika_KotelStateTypedef logika_GetKotelState(void);
	void logika_refresh(void * data);
	static logika_ItemsTypedef * logika_Items;

private:
	logika_KotelStateTypedef logika_GetKotelVodaState(void);
	logika_KotelStateTypedef logika_GetKotelTopeniState(int16_t * teplota);
	logika_KotelStateTypedef logika_GetKotelManualState(void);
	logika_KotelStateTypedef logika_KrucialniPodminka(int16_t Cas,
			int16_t CasStart, int16_t CasKonec);

	static logika_ItemsTypedef logika_ItemsReal;

};

#endif /* LOGIKA_H_ */
