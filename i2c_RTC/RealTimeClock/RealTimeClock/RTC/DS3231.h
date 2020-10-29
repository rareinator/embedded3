/*
 * DS3231.h
 *
 * Created: 28-Oct-20 12:17:36 PM
 *  Author: jpf
 */ 


#include "avr/io.h"
#include "../I2C/i2c_master.h"

  /**
  * @brief This is a driver specifically for the DS3231 and controlled with I2C.    
  */

typedef enum ErrorCode
{
   Success,
   Failure,
   StartError,
   WriteError   
} ErrorCode;

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}rtc;

#define DS3231_ReadMode         0xD1 // Device + Read bit
#define DS3231_WriteMode        0xD0 // Device + Write bit
#define DS3231_START_REGISTER   0x00 // RAM address Seconds (00H)

/**
* @brief Before this driver works works, this init function must be called.
*/
void DS3231_Init(void);

/**
* @brief Requests the driver, to set the DS3231 RTC clock.
* @param *rtc - RTC clock data are stored here. 
* @return - Returns an error code of the operation.
*/
ErrorCode DS3231_SetDateTime(rtc *rtc);

/**
* @brief Requests the driver, to get the date time in the DS3231 module.
* @param *rtc - RTC clock data are stored here. 
* @return - Returns an error code of the operation.
*/
ErrorCode DS3231_GetDateTime(rtc *rtc);

/**
* @brief Provides a default configuration for the DS3231.
* @param *rtc - RTC default clock data are stored here when the operation is complete.
*/
void DS3231_GetDefaultConfig(rtc *rtc);


/**
* @brief Prints the date time to the console.
* @param *rtc - RTC clock data are stored here, for print.
*/
void DS3231_PrintDateTime(rtc *rtc);

