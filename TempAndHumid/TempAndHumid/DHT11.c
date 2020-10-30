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

void DHT11_init()
{
	SET_BIT(DHT11_DDR, DHT11_BIT);
	SET_BIT(DHT11_PORT, DHT11_BIT);
}

void DHT11_PrintDataBytes(char *data[5][8])
{
	int j;
	printf("Humid: \n\r");
	for (j = 0; j < 8; j++) {
		// bit loop
		printf("%c",data[0][j]);
	}
	printf("Temp: \n\r");
	for (j = 0; j < 8; j++) {
		// bit loop
		printf("%c", data[2][j]);
	}
	printf("\n\r");
}

int DHT11_ReadBit()
{
	if (!DHT11_Wait(80, true))
	{
		printf("Timeout");
	}
	
	int waitTime = 0;
	while (bit_is_set(DHT11_PIN, DHT11_BIT))
	{
		_delay_us(2);
		waitTime += 2;	
		//if (waitTime > 80)
		//{
			//printf("WaitTime over 80 \n \r");
		//}
	}
	
	if (waitTime > 40)
	{
		//printf("return 1");
		return 1;		
	} else
	{
		//printf("return 0");
		return 0;		
	}
			
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
	
	int data[5][8];
	int i, j;
	
	for (i = 0; i < 5; i++) {
		// byte loop
		for (j = 0; j < 8; j++) {
			// bit loop
			data[i][j] = DHT11_ReadBit();
		}
	}
	
	int k;
	printf("Humid: \n\r");
	for (k = 0; k < 8; k++) {
		// bit loop
		printf("%d",data[0][k]);
	}
	printf("Temp: \n\r");
	for (k = 0; k < 8; k++) {
		// bit loop
		printf("%d", data[2][k]);
	}
	printf("\n\r");
}