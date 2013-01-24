/**
 * @file Table.cpp
 * @author kubanec
 * @date 24.1.2013
 *
 */

#include "guiInclude.h"
#include "Table.h"

namespace GUI
{

#define BASE (0x08000000 + 98 * 1024)
const Table * Table::FlashBase = (Table *) ( BASE);

void Table::Save()
{
	//vyzobat všecky hodnoty
	//vymazat stránku
	//nahrát ju

	//main screen
	Program = ui->ScreenMain->Program->GetValue();
	ManualTemp = ui->ScreenMain->TeplotaChtena->GetValue();

	//voda screen
	WaterWatchEnable = ui->ScreenVoda->HlidatTeplotu->GetValue();
	WaterTemperature = ui->ScreenVoda->Teplota->GetValue();
	WaterStart.hour = ui->ScreenVoda->HodinyZacit->GetValue();
	WaterStart.min = ui->ScreenVoda->MinutyZacit->GetValue();
	WaterStop.hour = ui->ScreenVoda->HodinyKonec->GetValue();
	WaterStop.min = ui->ScreenVoda->MinutyKonec->GetValue();

	//topeni screen
	for (int i = 0; i < 4; i++)
	{
		PoPa[i].temperature = ui->ScreenTopeni->Teploty[i]->GetValue();
		PoPa[i].time.min = ui->ScreenTopeni->Minuty[i]->GetValue();
		PoPa[i].time.hour = ui->ScreenTopeni->Hodiny[i]->GetValue();
	}

	for (int i = 0; i < 2; i++)
	{
		SoNe[i].temperature = ui->ScreenTopeniVikend->Teploty[i]->GetValue();
		SoNe[i].time.min = ui->ScreenTopeniVikend->Minuty[i]->GetValue();
		SoNe[i].time.hour = ui->ScreenTopeniVikend->Hodiny[i]->GetValue();
	}

	GuiFramework::port::Erase(BASE, BASE + 1023);
	GuiFramework::port::Write(this, sizeof(Table));
}

} /* namespace GUI */
