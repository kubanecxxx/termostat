/*
 * logika.c
 *
 *  Created on: 28.5.2012
 *      Author: kubanec
 */

#include "guiInclude.h"
#include "logika.h"

extern GUI::Gui * ui;

Logic::logika_ItemsTypedef Logic::logika_ItemsReal;
Logic::logika_ItemsTypedef * Logic::logika_Items = &logika_ItemsReal;

void Logic::logika_refresh(void * data)
{
	(void) data;
	logika_GetKotelState();
}

Logic::logika_KotelStateTypedef Logic::logika_GetKotelState(void)
{

	Program program = (Program) ui->ScreenMain->Program->GetValue();
	logika_KotelStateTypedef temp;
	int16_t teplota;

	static logika_KotelStateTypedef prev_topit;
	static int16_t prev_teplota;
	static uint8_t prev_show, prev_show2;

	ui->ScreenMain->TeplotaChtena->SetShownGlobal(false);
	ui->ScreenMain->TeplotaManual->SetShownGlobal(false);

	//to bude super obří obludná podmínka s casema a milionem ifů
	switch (program)
	{
	case PROGRAM_VYPNOUT:
		temp = NETOPIT;
		break;
	case PROGRAM_VODA:
		temp = logika_GetKotelVodaState();
		break;
	case PROGRAM_TOPENI:
		temp = logika_GetKotelTopeniState(&teplota);
		ui->ScreenMain->TeplotaChtena->SetValue(teplota);
		ui->ScreenMain->TeplotaChtena->SetShownGlobal(true);
		break;
	case PROGRAM_MANUAL:
		temp = logika_GetKotelManualState();
		ui->ScreenMain->TeplotaManual->SetShownGlobal(true);
		break;
	default:
		temp = NETOPIT;
		break;
	}

	if (prev_topit != temp)
	{
		prev_topit = temp;
		ui->ScreenMain->Topi->SetValue(temp);
		ui->ScreenMain->Topi->printItem();
	}

	if (prev_show != ui->ScreenMain->TeplotaManual->IsShownGlobal())
	{
		prev_show = ui->ScreenMain->TeplotaManual->IsShownGlobal();
		ui->ScreenMain->TeplotaManual->printItem();
	}

	if (prev_teplota != ui->ScreenMain->TeplotaChtena->GetValue()
			|| prev_show2 != ui->ScreenMain->TeplotaChtena->IsShownGlobal())
	{
		prev_teplota = ui->ScreenMain->TeplotaChtena->GetValue();
		prev_show2 = ui->ScreenMain->TeplotaChtena->IsShownGlobal();
		ui->ScreenMain->TeplotaChtena->printItem();
	}

	return temp;
}

Logic::logika_KotelStateTypedef Logic::logika_GetKotelVodaState(void)
{
	int16_t teplota = ui->ScreenMain->TeplotaDole->GetValue();
	int16_t Cas = ui->ScreenMain->Hodiny->GetValue() * 60
			+ ui->ScreenMain->Minuty->GetValue();
	int16_t teplotaChtena = ui->ScreenVoda->Teplota->GetValue();
	int16_t HlidatTeplotu = ui->ScreenVoda->HlidatTeplotu->GetValue();
	int16_t casZapnout = (ui->ScreenVoda->HodinyZacit->GetValue() * 60)
			+ ui->ScreenVoda->MinutyZacit->GetValue();
	int16_t casVypnout = (ui->ScreenVoda->HodinyKonec->GetValue() * 60)
			+ ui->ScreenVoda->MinutyKonec->GetValue();

	logika_KotelStateTypedef kotel = NETOPIT;

	if (logika_KrucialniPodminka(Cas, casZapnout, casVypnout) == TOPIT)
	{
		if (HlidatTeplotu == 0)
			kotel = TOPIT;
		else
		{
			if (teplota < teplotaChtena)
				kotel = TOPIT;
		}
	}
	else
	{
		kotel = NETOPIT;
	}

	return kotel;
}

Logic::logika_KotelStateTypedef Logic::logika_GetKotelTopeniState(
		int16_t * teplota)
{
	int16_t Teplota = ui->ScreenMain->TeplotaDole->GetValue();
	int16_t Den = ui->ScreenMain->Den->GetValue();
	int16_t Cas = ui->ScreenMain->Hodiny->GetValue() * 60
			+ ui->ScreenMain->Minuty->GetValue();
	int16_t Cas_temp, Cas_temp2, Teplota_temp = 0;
	uint16_t i;

	logika_KotelStateTypedef kotel = NETOPIT;
	//dny jsou 1-7 Po,Ut
	if (Den == 6 || Den == 7)
	{
		//sobota neděle
		for (i = 0; i < 2; i++)
		{
			Cas_temp = *(logika_Items->TopeniSetting.SoNe[i].CasH) * 60
					+ *(logika_Items->TopeniSetting.SoNe[i].CasM);
			Cas_temp2 = *(logika_Items->TopeniSetting.SoNe[(i + 1) % 2].CasH)
					* 60
					+ *(logika_Items->TopeniSetting.SoNe[(i + 1) % 2].CasM);
			Teplota_temp = *(logika_Items->TopeniSetting.SoNe[i].Teplota);

			if (logika_KrucialniPodminka(Cas, Cas_temp, Cas_temp2) == TOPIT)
			{
				*teplota = Teplota_temp;
				if (Teplota < Teplota_temp)
				{
					return TOPIT;
				}
			}
		}
	}
	else
	//přes tyden
	{
		for (i = 0; i < 4; i++)
		{
			Cas_temp = *(logika_Items->TopeniSetting.PoPa[i].CasH) * 60
					+ *(logika_Items->TopeniSetting.PoPa[i].CasM);
			Cas_temp2 = *(logika_Items->TopeniSetting.PoPa[(i + 1) % 4].CasH)
					* 60
					+ *(logika_Items->TopeniSetting.PoPa[(i + 1) % 4].CasM);
			Teplota_temp = *(logika_Items->TopeniSetting.PoPa[i].Teplota);

			if (logika_KrucialniPodminka(Cas, Cas_temp, Cas_temp2) == TOPIT)
			{
				*teplota = Teplota_temp;
				if (Teplota < Teplota_temp)
				{
					return TOPIT;
				}
			}
		}
	}

	return kotel;
}

Logic::logika_KotelStateTypedef Logic::logika_KrucialniPodminka(int16_t Cas,
		int16_t CasStart, int16_t CasKonec)
{
	if (CasStart < CasKonec && Cas >= CasStart && Cas < CasKonec)
		return TOPIT;

	if (CasStart > CasKonec)
	{
		if (Cas > CasKonec && Cas < CasStart)
			return NETOPIT;
		else
			return TOPIT;
	}

	return NETOPIT;
}

Logic::logika_KotelStateTypedef Logic::logika_GetKotelManualState(void)
{
	int16_t teplota = ui->ScreenMain->TeplotaDoma->GetValue();
	int16_t teplotaManual = ui->ScreenMain->TeplotaManual->GetValue();

	if (teplota < teplotaManual)
		return TOPIT;
	else
		return NETOPIT;
}
