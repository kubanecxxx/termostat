/*
 * logika.h
 *
 *  Created on: 28.5.2012
 *      Author: kubanec
 */

#ifndef LOGIKA_H_
#define LOGIKA_H_

#include "port/framework_port.h"

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

typedef struct logika_VodaTypedef
{
	const int16_t * TeplotaVodyChtena;
	const int16_t * CasH_Start;
	const int16_t * CasM_Start;
	const int16_t * CasH_Stop;
	const int16_t * CasM_Stop;
	const int16_t * HlidatTeplotu;
} logika_VodaTypedef;

typedef struct logika_ItemsTypedef
{
	logika_TopeniTypedef TopeniSetting;
	logika_VodaTypedef VodaSetting;
} logika_ItemsTypedef;

void logika_Connect(const logika_ItemsTypedef * logika_Items);
logika_KotelStateTypedef logika_GetKotelState(void);
void logika_refresh(void * data);

#endif /* LOGIKA_H_ */
