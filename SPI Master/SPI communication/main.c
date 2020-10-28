/*
 * SPI communication.c
 *
 * Created: 10/27/2020 10:41:56 AM
 * Author : rare
 */ 
#define F_CPU 16000000UL
#define BAUD 9600
#define BAUD_TOL 2

#define LED_TOOGLE PORTB ^= (1 << PB7)
#define SS_ENABLE PORTB &= ~(1<<PB0)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>
#include <ctype.h>

ISR(TIMER1_COMPA_vect)
{
	LED_TOOGLE;	
	SPI_Write('A');
}

void Timer_Init()
{
	TIMSK1 |= (1<<OCIE1A);
	TCCR1B |= (1<<WGM12);		
	TCCR1B |= (1<<CS12) | (1<<CS10);	
	OCR1A = 31249;
}

void SPI_Init()
{
	DDRB |= (1<<PB2) | (1<<PB1) | (1<<PB0); // Set MOSI, SCK and SS as output pins
	DDRB &= ~(1<<PB3); // Set MISO as input pin
	
	PORTB |= (1<<PB0); //Set SS pin high
	
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0); // Enable SPI i master mode 21.2.1 with a frequency of fosc/16
	SPCR &= ~(1<<CPOL);
	SPCR &= ~(1<<CPHA);
	SPSR &= ~(1<<SPI2X); // Disable speed double 21.2.2
}

void USART_Transmit(unsigned char data)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;	
	
}

char SPI_Read()
{
	SPDR = 0xFF;
	while (!(SPSR & (1<<SPIF)));
	return SPDR;
}

void SPI_Write(char data)
{
	SPDR = data;
	while (!(SPSR & (1<<SPIF))); // Waits for transmission to complete
}

void USART_Init()
{
	UCSR0B = (1 << RXEN0 ) | (1 << TXEN0 ); // Turn on the transmission and reception circuitry 22.10.3
	UCSR0C = (1 << UCSZ00 ) | (1 << UCSZ01 ); // Use 8- bit character sizes 22.10.4

	UBRR0H = UBRRH_VALUE; // Sets baud rate to defined BAUD
	UBRR0L = UBRRL_VALUE ;

	UCSR0B |= (1 << RXCIE0 ); // Enable the USART Receive Complete interrupt ( USART0_RXC ) 22.10.3
}

int main(void)
{
	DDRB |= (1<<PB7); // Onboard LED to output
	
	USART_Init();
	SPI_Init();
	//Timer_Init();
	sei();
	SS_ENABLE;
	
    while (1) {
		//USART_Transmit(SPI_Read());
	} // Loops program forever
}

ISR ( USART0_RX_vect )
{
	char Message ;
	Message = UDR0 ; // Fetch the received byte value
	LED_TOOGLE;
	SPI_Write(Message) ; // Write the message over the SPI pins to the slave
}

