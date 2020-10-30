/*
 * DHT11.c
 *
 * Created: 10/29/2020 10:50:30 AM
 *  Author: rare
 */ 
#define F_CPU 16000000UL
#include "DHT11.h"
#include <util/delay.h>
#include <avr/sfr_defs.h>


bool DHT11_Wait(int maxWaitTime, bool waitForHigh)
{
	int waitTime = 0;
	if (waitForHigh)
	{
		while(bit_is_clear(DHT11_PIN, DHT11_BIT))
		{
			_delay_us(2);
			waitTime += 2;
			if (waitTime >= maxWaitTime) {
				return false;
			}
		}			
		
	} else
	{
		while(bit_is_set(DHT11_PIN, DHT11_BIT))
		{
			_delay_us(2);
			waitTime += 2;
			if (waitTime >= maxWaitTime) {
				return false;
			}
		}
	}
	return true;
}

void DHT11_init() {
	SET_BIT(DHT11_DDR, DHT11_BIT);
	SET_BIT(DHT11_PORT, DHT11_BIT);
}

void DHT11_ReadRaw()
{
	CLR_BIT(DHT11_PORT, DHT11_BIT);	// Set to logic 0
	_delay_ms(19);
	CLR_BIT(DHT11_DDR, DHT11_BIT);
	if (!DHT11_Wait(60, false)) // Wait for a max of 60 us
	{
		//Do timeout stuff
	}
	
	
	if (!DHT11_Wait(100, true))
	{
		//timeout
	}
	
	if (!DHT11_Wait(100, false))
	{
		// timeout
	}
	
	char data[5][8];
	int i, j;
	
	for (i = 0; i < 5; i++) {
		// byte loop
		for (j = 0; j < 8; j++) {
			// bit loop
		}
	}
	
	
	
}