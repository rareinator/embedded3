#define F_CPU 16000000UL


#include <avr/io.h>
#include <stdbool.h>
#include "DHT11library.h"
#include "ESP8266.h"
#include "SPIlibrary.h"


int main(void)
{
	SPI_Init(true);
	
	SS_ENABLE;
	SPI_Write(1); // Function Register: Register 0 = Turn On/Off - Register 1 = Fan speed
	SS_DISABLE;
	_delay_ms(500);
	SS_ENABLE;
	SPI_Write(255); // Register Value: If register 0 value = 0 or 1 = Off or On - If 1 value = 0-255 for dutycycle
	SS_DISABLE;
	
	_delay_ms(500);
	
	SS_ENABLE;			
	SPI_Write(0); // Function Register: Register 0 = Turn On/Off - Register 1 = Fan speed
	SS_DISABLE;
	_delay_ms(500);
	SS_ENABLE;
	SPI_Write(1); // Register Value: If register 0 value = 0 or 1 = Off or On - If 1 value = 0-255 for dutycycle
	SS_DISABLE;
	
	while(1)
	{
	}
}

