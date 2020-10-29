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
	SET_OUTPUT(DHT11_PORT, DHT11_PIN);
	SET_BIT(DHT11_PORT, DHT11_PIN);
}

void DHT11_ReadRaw()
{
	CLR_BIT(DHT11_PORT, DHT11_PIN);	
	_delay_ms(19);
	SET_INPUT(DHT11_PORT, DHT11_PIN);
	SET_BIT(DHT11_PORT, DHT11_PIN); //Activate internal pull up resistor 
}