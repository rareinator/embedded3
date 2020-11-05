#define F_CPU 16000000UL

#include <avr/io.h>
#include "DClibrary.h"
#include "SPIlibrary.h"
#include <avr/interrupt.h>
#include <stdio.h>

uint8_t reg;
uint8_t val;

ISR(PCINT0_vect)
{
	reg = SPI_Read();
	val = SPI_Read();
	if (reg == 0x00)
	{
		if (val == 0x00)
		{
			Stop_Fan();
		}
		else if (val == 0x01)
		{
			Start_Fan();
		}
	}
	else if (reg == 0x01)
	{
		Set_Speed(val);
	}	
}

int main(void)
{
	DCMotor_init();
	SPI_Init(false);
	while (1)
	{
	}
}


