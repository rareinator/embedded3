#define F_CPU 16000000UL
#include <stdio.h>
#include "stdio_setup.h"

#include <util/delay.h>

#include "DHT11.h"

int main(void)
{
	UartInit();
	DHT11_init();
	_delay_ms(1000);
	
	while(1) {
		DHT11_ReadRaw();
	}
}