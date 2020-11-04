/**
 @file
 @defgroup RTClib RTC Library
 @code #include <RTClibrary.h> @endcode
  
 @brief RTC Library

 Basic routines for communicating with an RTC device over i2c,
 this library uses the I2CLib from peter fleury. So be sure,
 to have that included in the project you wish to use this library from.

	Connect the RTC using given pins

	// include picture here

 @author Morten Nissen, Nicolai De Jong Bjerg & Kevin Pike Darmer
 @copyright (C) 2020 Morten Nissen, Nicolai De Jung Berg & Kevin Pike Darmer, GNU General Public License Version 3

*/

/**@{*/

#ifndef RTCLIBRARY_H_
#define RTCLIBRARY_H_


/** 
 @brief Structure used to save and get datetime from the RTC device.
	Day is what day of the week it is, and date is the date of the year.
 */
typedef struct  {
	uint8_t Year;
	uint8_t Month;
	uint8_t Day;
	uint8_t Date;
	uint8_t Hour;
	uint8_t Minute;
	uint8_t Second;
} DateTime;

/** 
 @brief The slave address of the RTC device
 */
#define SLAVE_ADDRESS 0xD0 // RTC DS3231 Slave address: Page 16 - Figure 3

/** 
 @brief The address register of the seconds
 */
#define SECONDS 0x00

/** 
 @brief Sets the time in the RTC device
  
 @param  DateTime struct with the time, you wish to set the device to
 */
void DS3231_setDateTime(DateTime *time);

/** 
 @brief Gets the date from the RTC device and saves it in the given struct
  
 @param  DateTime pointer where the data should be put into
 */
void DS3231_getDateTime(DateTime *now);

#endif /* RTCLIBRARY_H_ */