/*
 * RTC.h
 *
 * Created: 11/2/2020 10:25:15 AM
 *  Author: rare
 */ 


#ifndef RTC_H_
#define RTC_H_


typedef struct  {
	uint8_t Year;
	uint8_t Month;
	uint8_t Day;
	uint8_t Date;
	uint8_t Hour;
	uint8_t Minute;
	uint8_t Second;
} DateTime;

// Slave address for i2c
#define SLAVE_ADDRESS 0xD0

// RTC data registers
#define SECONDS 0x00

void DS3231_setDateTime(DateTime *time);
void DS3231_getDateTime(DateTime *now);




#endif /* RTC_H_ */