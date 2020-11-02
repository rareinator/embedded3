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
#include <stdbool.h>

#include <stdio.h>
#include "stdio_setup.h"


bool DHT11_Wait(int maxWaitTime, bool waitForHigh)
{
	int waitTime = 0;
	if (waitForHigh)
	{
		while(bit_is_clear(DHT11_PIN, DHT11_BIT))
		{
			_delay_us(1);
			waitTime++;
			if (waitTime >= maxWaitTime) {
				return false;
			}
		}			
		
	} else
	{
		while(bit_is_set(DHT11_PIN, DHT11_BIT))
		{
			_delay_us(1);
			waitTime++;
			if (waitTime >= maxWaitTime) {
				return false;
			}
		}
	}
	return true;
}

void DHT11_init()
{
	SET_BIT(DHT11_DDR, DHT11_BIT);
	SET_BIT(DHT11_PORT, DHT11_BIT);
}

void DHT11_ReadRaw()
{
	uint8_t data[5] = {0, 0, 0, 0, 0};
	int i, j;
		
	CLR_BIT(DHT11_PORT, DHT11_BIT);	// Set to logic 0
	_delay_ms(19);
	CLR_BIT(DHT11_DDR, DHT11_BIT);
	if (!DHT11_Wait(60, false)) // Wait for a max of 60 us
	{
		//Do timeout stuff
		printf("timeout 1");
	}
	
	if (!DHT11_Wait(100, true)) // Wait for high pin
	{
		//timeout
		printf("timeout 2");
	}
	
	if (!DHT11_Wait(100, false)) // Wait for low pin
	{
		// timeout
		printf("timeout 3");
	}
	// beginning of the 50 ms are technically here
	
	DHT11_Wait(100, true); // Wait for high to try and cancel out the wrong 1 in the beginning of our data
	
	for (i = 0; i < 5; i++) {
		// byte loop
		for (j = 7; j >= 0; j--) {
			// bit loop
			if ((i == 0) && (j==7)) {
				// fuck you, you sadistic fucking fat retarded cunt!!!!!!!! of a 1
				printf("huh");
			} else {
				if (!DHT11_Wait(70, true))
				{
					printf("Timeout");
				}
							
				uint8_t waitTime = 0;
				while (bit_is_set(DHT11_PIN, DHT11_BIT))
				{
					_delay_us(2);
					waitTime += 2;
				}
							
				if (waitTime > 40)
				{
					SET_BIT(data[i], j);
					//printf("huh");
				} else
				{
					// Do nothing
				}
			}
		}
	}
	


	//printf("Temp: %i", data[2]);
	printf("hum: 0x%X", data[0]);
}