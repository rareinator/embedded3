/*
 * DHT11.c
 *
 * Created: 10/29/2020 10:50:30 AM
 *  Author: rare
 */ 
#define F_CPU 16000000UL
#include "DHT11.h"
#include <util/delay.h>

void DHT11_init() {
	SET_BIT(DHT11_DDR, DHT11_BIT);
	SET_BIT(DHT11_PORT, DHT11_BIT);
}

void DHT11_ReadRaw()
{
	CLR_BIT(DHT11_PORT, DHT11_BIT);	// Set to logic 0
	_delay_ms(19);
	CLR_BIT(DHT11_DDR, DHT11_BIT);
}