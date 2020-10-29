#define F_CPU 16000000UL
#include <stdio.h>
#include "stdio_setup.h"

#include <util/delay.h>

#include "DHT11.h"

int main(void)
{
	UartInit();
	DHT11_init();
	DHT11_ReadRaw();

	while(1) {
		_delay_ms(500);
		
		
	}
}