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

uint8_t reg;
uint8_t val;

ISR(PCINT0_vect)
{
	reg = SPI_Read();
	/*
	reg = SPI_Read();
	val = SPI_Read();
	if(reg == 0x00){
		switch (val){
			case 0X00:
			Stop_Fan();
			break;
			
			case 0X01:
			Start_Fan();
			break;
		}
		Start_Fan();
	}
	else if(reg == 0x01){
		Set_Speed(val);
	}
	*/
}

Slave_Init(){
	PCICR |= (1<<PCIE0);	// Pin Change Interrupt Enable 0, Datasheet 17.2.4
	PCMSK0 |= (1<<PCINT2);	// Pin Change Mask Register 0, Datasheet 17.2.8
	sei();
}

int main(void)
{
	Slave_Init();
	DCMotor_init();
	SPI_Init(false);
	Set_Speed(0xFF);
	while (1)
	{
		if (reg == 0x01)
		{
			Start_Fan();
		}
		
	}
}


