#define F_CPU 16000000UL
#define BAUD 9600
#define BAUD_TOL 2

#include <avr/io.h>
#include <util/setbaud.h>
#include <ctype.h>
#include <i2cLib/i2cmaster.h>

unsigned char USART_Receive(void)
{
	while (	!(UCSR0A & (1<<RXC0)));	// Wait for data to be received
	char recivedChar = UDR0;
	
	return toupper(recivedChar); // Get and return received data from buffer
}

void USART_Transmit(unsigned char data)
{
	while (	!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;  // Put data into buffer, sends the data
}

void USART_Init()
{
	UBRR0H = UBRRH_VALUE; // set UART0 baud rate
	UBRR0L = UBRRL_VALUE;

	UCSR0B = (1<<RXEN0) | (1<<TXEN0); // Enable Receiver and Transmitter, 22.10.3	
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); // Set frame format: 8 bit data, 1 stop bit, 22.10.4
}

int main(void)
{	
	USART_Init();
	i2c_init();
		

	while(1) {
	}
}