/*
* DS3231.c
*
* Created: 28-Oct-20 12:19:22 PM
*  Author: jpf
*/

#include  "DS3231.h"
#include  "../I2C/i2c_master.h"

void DS3231_Init(void)
{
	// Initialize the I2c module.
	i2c_init();
}


ErrorCode DS3231_SetDateTime(rtc *rtc)
{
	// Start and set RAM address to 00H
	if(i2c_start(DS3231_WriteMode))
	{
		return StartError;
	}
	if(i2c_write(DS3231_START_REGISTER))
	{
		return WriteError;
	}

	// Set date time.
	// The DS3231 has auto increment, so we just start reading from 00H and stops at 06H.
	if (i2c_write(rtc->sec))
	{
		return WriteError;
	}
	
	if (i2c_write(rtc->min))
	{
		return WriteError;
	}
	
	if (i2c_write(rtc->hour))
	{
		return WriteError;
	}
	
	if (i2c_write(rtc->weekDay))
	{
		return WriteError;
	}
	
	if (i2c_write(rtc->date))
	{
		return WriteError;
	}
	
	if (i2c_write(rtc->month))
	{
		return WriteError;
	}
	
	if (i2c_write(rtc->year))
	{
		return WriteError;
	}
	
	i2c_stop();
	
	return Success;
}


ErrorCode DS3231_GetDateTime(rtc *rtc)
{
	// Start and set RAM address to 00H
	if(i2c_start(DS3231_WriteMode))
	{
		return StartError;
	}
	
	if(i2c_write(DS3231_START_REGISTER))
	{
		return WriteError;
	}
	
	i2c_stop();

	// Catch data from DS3231.
	if(i2c_start(DS3231_ReadMode))
	{
		return StartError;
	}
	
	rtc->sec = i2c_read_ack();
	rtc->min = i2c_read_ack();
	rtc->hour= i2c_read_ack();
	rtc->weekDay = i2c_read_ack();
	rtc->date= i2c_read_ack();
	rtc->month=i2c_read_ack();
	rtc->year =i2c_read_ack();
	
	i2c_stop();
	
	return Success;
}

void DS3231_GetDefaultConfig(rtc *rtc)
{
	// Right now it's dummy data
	
	// Default config.
	rtc->sec = 0x00; // 0
	rtc->min = 0x20; // 32
	rtc->hour = 0x14; // 20
	rtc->weekDay = 0x02; //
	rtc->date = 0x05; // 5
	rtc->month = 0x06; // 6
	rtc->year = 0x14; //20
}

void DS3231_PrintDateTime(rtc *rtc)
{
			printf("Sec: %d\r\n", rtc->sec);
			printf("Min: %d\r\n", rtc->min);
			printf("Hour: %d\r\n", rtc->hour);
			printf("Weekday: %d\r\n", rtc->weekDay);
			printf("Date: %d\r\n", rtc->date);
			printf("Month: %d\r\n", rtc->month);
			printf("Year: %d\r\n", rtc->year);	
}