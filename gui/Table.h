/**
 * @file Table.h
 * @author kubanec
 * @date 24.1.2013
 *
 */

#ifndef TABLE_H_
#define TABLE_H_

namespace GUI
{

class Table
{
public:
	static const Table * FlashBase;
	void Save();

	typedef struct
	{
		int16_t min;
		int16_t hour;
	} time_t;

	typedef struct
	{
		time_t time;
		int16_t temperature;
	} time_temp_t;

	//main screen
	int16_t Program;
	int16_t ManualTemp;

	//voda screen
	int16_t WaterWatchEnable;
	int16_t WaterTemperature;

	typedef struct
	{
		time_t WaterStart;
		time_t WaterStop;
	} water_time_t;

	water_time_t vody[2];

	//topeni screen
	//po-pa
	time_temp_t PoPa[4];
	//so-ne
	time_temp_t SoNe[2];

private:

};

} /* namespace GUI */
#endif /* TABLE_H_ */
