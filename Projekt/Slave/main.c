/*
* Slave.c
*
* Created: 04-11-2020 11:15:40
* Author : ASUS
*/

#include <avr/io.h>
#include "DClibrary.h"
#include "SPIlibrary.h"
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "stdio_setup.h"

uint8_t reg;
uint8_t val;

ISR(SPI_STC_vect)
{
	printf("Interrupt\n");
	/*
	if (bit_is_clear(PINB, PB0))
	{
		printf("Bit is clear\n");
		reg = SPI_Read();
		val = SPI_Read();
		if (reg == 0x00)
		{
			printf("Start/Stop Reg\n");
			if (val == 0x00)
			{
				Stop_Fan();
			}
			else if (val == 0x01)
			{
				printf("Start Fan\n");
				Start_Fan();
			}
		}
		else if (reg == 0x01)
		{
			printf("Speed Set\n");
			Set_Speed(val);
		}
	}
	else if (bit_is_set(PINB, PB0))
	{
		printf("Bit is set\n");
	}*/
	
	
	
}


int main(void)
{
	_delay_ms(3000);
	DCMotor_init();
	SPI_Init(false);
	UartInit();
	while (1)
	{
	}
}


