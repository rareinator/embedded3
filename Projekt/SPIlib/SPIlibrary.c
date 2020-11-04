#include <avr/io.h>
#include <stdbool.h>

void SPI_Init(bool isMaster)
{
	if (isMaster)
	{
		DDRB |= (1<<PB2) | (1<<PB1) | (1<<PB0); // Set MOSI, SCK and SS as output pins
		DDRB &= ~(1<<PB3); // Set MISO as input pin
		
		PORTB |= (1<<PB0); //Set SS pin high
		
		SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0); // Enable SPI i master mode 21.2.1 with a frequency of fosc/16
		SPCR &= ~(1<<CPOL);
		SPCR &= ~(1<<CPHA);
		SPSR &= ~(1<<SPI2X); // Disable speed double 21.2.2
	}
	else
	{
		DDRB &= ~((1<<PB2)|(1<<PB1)|(1<<PB0));  /* Make MOSI, SCK, SS as input pins */
		
		DDRB |= (1<<PB3);			/* Make MISO pin as output pin */
		
		SPCR = (1<<SPE);
	}
		
	
}

char SPI_Read()
{
	while (!(SPSR & (1<<SPIF)));
	return SPDR;
}


void SPI_Write(char data)
{
	SPDR = data;
	while (!(SPSR & (1<<SPIF))); // Waits for transmission to complete
}


