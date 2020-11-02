#define F_CPU 16000000UL

#include <avr/io.h>
#include <ctype.h>
#include "I2Clibrary.h"

#define SLAVE_ADDRESS 0xD0 // RTC DS3231 Slave address: Page 16 - Figure 3 

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
	i2c_start(SLAVE_ADDRESS+I2C_WRITE); // 1101000 0 - Write Mode - Figure 3
	i2c_write(SECONDS); // Start position address 00H
	
	i2c_write(time->Minute);
	i2c_write(time->Hour);
	i2c_write(time->Day);
	i2c_write(time->Date);
	i2c_write(time->Month); 
	i2c_write(time->Year);
	i2c_stop();
}

void DS3231_getDateTime(DateTime *now)
{
	i2c_start(SLAVE_ADDRESS+I2C_WRITE); // 1101000 0 - Write Mode - Figure 3
	i2c_write(SECONDS); // Start position address 00H
	i2c_stop();
	
	i2c_start(SLAVE_ADDRESS+I2C_READ); // 1101000 1 - Read Mode - Figure 4
	now->Second = i2c_read(1);
	now->Minute = i2c_read(1);
	now->Hour = i2c_read(1);
	now->Day = i2c_read(1);
	now->Date = i2c_read(1);
	now->Month = i2c_read(1);
	now->Year = i2c_read(0);
	i2c_stop();
};