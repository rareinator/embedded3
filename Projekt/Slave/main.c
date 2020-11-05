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
	printf("Interrupt /n");
	reg = SPI_Read();
	val = SPI_Read();
	if (reg == 0x00)
	{
		if (val == 0x00)
		{
			printf("Fan Stopped/n");
			Stop_Fan();
		}
		else if (val == 0x01)
		{
			printf("Fan Started/n");
			Start_Fan();
		}
	}
	else if (reg == 0x01)
	{
		printf("Speed Set/n");
		Set_Speed(val);
	}	
}

void Slave_Init()
{
	PCICR |= (1<<PCIE0);					// Pin Change Interrupt Enable 0, Datasheet 17.2.4
	PCMSK0 |= (1<<PCINT0);					// Pin Change Mask Register, Datasheet 17.2.8
	
	sei();
}

int main(void)
{
	DCMotor_init();
	SPI_Init(false);
	Slave_Init();
	UartInit();
	while (1)
	{
	}
}


