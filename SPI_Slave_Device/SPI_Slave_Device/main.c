/*
 * ATmega32_SPI_Slave.c
 * http://www.electronicwings.com
 */ 


#define F_CPU 16000000UL			/* Define CPU Frequency 16MHz */
#define BAUD 9600
#define BAUD_TOL 2
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */
#include <stdio.h>			/* Include std. i/p o/p file */
#include <string.h>			/* Include string header file */
#include <util/setbaud.h>



void SPI_Init()					/* SPI Initialize function */
{
	DDRB &= ~((1<<PB2)|(1<<PB1)|(1<<PB0));  /* Make MOSI, SCK, SS as input pins */
	
	DDRB |= (1<<PB3);			/* Make MISO pin as output pin */
	
	SPCR = (1<<SPE);			/* Enable SPI in slave mode */
}

void USART_Init()
{
	UBRR0H = UBRRH_VALUE;					// set UART0 baud rate
	UBRR0L = UBRRL_VALUE;

	UCSR0B = (1<<RXEN0) | (1<<TXEN0);		// Enable Receiver and Transmitter, 24.12.3
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);		// Set frame format: 8 bit data, 1 stop bit, 24.12.4
}

char SPI_Receive()			/* SPI Receive data function */
{
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}

void SPI_Write(unsigned char data){
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	SPDR = data;
}

void USART_Transmit(unsigned char data)
{
	while (	!(UCSR0A & (1<<UDRE0)));
	UDR0 = toupper(data);							// Put data into buffer, sends the data
}

unsigned char USART_Receive(void)
{
	while (	!(UCSR0A & (1<<RXC0)));			// Wait for data to be received
	return UDR0;							// Get and return received data from buffer
}

int main(void)
{
	char message;
		
	SPI_Init();
	
	USART_Init();
	
	while (1)			/* Receive count continuous */
	{
		message = SPI_Receive();
		USART_Transmit(message);
		SPI_Write((USART_Receive()));
	}

}