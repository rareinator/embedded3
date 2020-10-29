#define F_CPU 16000000UL
#define BAUD 9600
#define BAUD_TOL 2

#include <avr/io.h>
#include <util/setbaud.h>
#include <ctype.h>
#include "i2cLib/i2cmaster.h"
#include <util/delay.h>
#include <stdio.h>
#include "stdio_setup.h"

#define SLAVE_ADDRESS 0xD0

#define SECONDS 0x00

typedef struct  {
	uint8_t Year;
	uint8_t Month;
	uint8_t Day;
	uint8_t Date;
	uint8_t Hour;
	uint8_t Minute;
	uint8_t Second;
} DateTime;

void DS3231_setDateTime(DateTime *time)
{
	i2c_start(SLAVE_ADDRESS+I2C_WRITE); //Address 00H
	i2c_write(SECONDS);
	//i2c_write(0x00); // seconds to 0
	//i2c_write(0x00); // minutes
	//i2c_write(0x12); // hours 00 01 0010
	//i2c_write(0x05); // day 0000 0101 fredag
	//i2c_write(0x30); // date 0011 0000 den 30
	//i2c_write(0x10); // month 0001 0000 den 10
	//i2c_write(0x20); // year 0010 0000
	i2c_write(time->Second); // seconds to 0
	i2c_write(time->Minute); // minutes
	i2c_write(time->Hour); // hours 00 01 0010
	i2c_write(time->Day); // day 0000 0101 fredag
	i2c_write(time->Date); // date 0011 0000 den 30
	i2c_write(time->Month); // month 0001 0000 den 10
	i2c_write(time->Year); // year 0010 0000
	i2c_stop();				
}

void DS3231_getDateTime(DateTime *now)
{
	i2c_start(SLAVE_ADDRESS+I2C_WRITE);
	i2c_write(SECONDS);
	i2c_stop();
	
	i2c_start(SLAVE_ADDRESS+I2C_READ);
	now->Second = i2c_read(1);
	now->Minute = i2c_read(1);
	now->Hour = i2c_read(1);
	now->Day = i2c_read(1);
	now->Date = i2c_read(1);
	now->Month = i2c_read(1);
	now->Year = i2c_read(0);
	i2c_stop();
};


int main(void)
{	
	UartInit();
	i2c_init(); // init I2C lib
	DateTime start;
	start.Year = 20;
	start.Month = 10;
	start.Day = 5;
	start.Date = 28;
	start.Hour = 12;
	start.Minute = 30;
	start.Second = 00;
	DS3231_setDateTime(&start);
	
	while(1) {
		_delay_ms(1000);
		DateTime now;
		DS3231_getDateTime(&now);
		printf("Time: %d:%d:%d on %d:%d:20%d \n", now.Hour, now.Minute, now.Second, now.Date, now.Month, now.Year);
	}
}