#include <stdio.h>
#include "stdio_setup.h"
#include <avr/io.h>

#include "Delay/Delay.h"
#include "RTC/DS3231.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define  ON_BOARD_LED 0x80



int main(void)
{
	rtc rtcWrite;
	rtc rtcRead;
	
	UartInit();
	
	DS3231_Init();
	DS3231_GetDefaultConfig(&rtcWrite);
	
	printf("\r\nData TO RTC!\r\n");
	DS3231_PrintDateTime(&rtcWrite);
	
	
	ErrorCode rtcResult = DS3231_SetDateTime(&rtcWrite);
	if (rtcResult)
	{
		printf("\r\nSet date time: Error: %d\r\n", rtcResult);		
		return 1;
	}
	

	while(1) {
		
		// Get time.		
		rtcResult = DS3231_GetDateTime(&rtcRead);
		if (rtcResult)
		{
			printf("\r\nGet date time: Error: %d\r\n", rtcResult);			
			return 1;
		}
		
		// Print result.
		printf("\r\DATA FROM RTC!\r\n");
		DS3231_PrintDateTime(&rtcRead);
		
		
		// LED_TOGGLE;
		PINB = ON_BOARD_LED;
		
		Delay();
	}
}