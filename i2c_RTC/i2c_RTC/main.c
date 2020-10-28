#define F_CPU 16000000UL
#define BAUD 9600
#define BAUD_TOL 2

#include <avr/io.h>
#include <util/setbaud.h>
#include <ctype.h>
#include <i2cLib/i2cmaster.h>
#include <util/delay.h>

#define SLAVE_ADDRESS 0x68

struct  DateTime {
	char Year;
	char Month;
	char Day;
	char Date;
	char Hour;
	char Minute;
	char Second;
};

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

void DS3231_init()
{
	
	
}

void DS3231_setDateTime(DateTime time)
{
	i2c_start(SLAVE_ADDRESS); //Addess 00H
	i2c_write(0x00) // seconds to 0
	i2c_write(0x00)// minutes
	i2c_write(0x12)// hours 00 01 0010
	i2c_write(0x05)// day 0000 0101 fredag
	i2c_write(0x30)// date 0011 0000 den 30
	i2c_write(0x10)// month 0001 0000 den 10
	i2c_write(0x20)// year 0010 0000
	i2c_stop();				
}

DateTime DS3231_getDateTime()
{
	i2c_start(SLAVE_ADDRESS);
	DateTime result;
	result.Second = i2c_read(1);
	result.Minute = i2c_read(1);
	result.Hour = i2c_read(1);
	result.Day = i2c_read(1);
	result.Date = i2c_read(1);
	result.Month = i2c_read(1);
	result.Year = i2c_read(0);
	i2c_stop();
	
	return result;
};


int main(void)
{	
	USART_Init();
	i2c_init(); // init I2C library
	DS3231_init();
	struct DateTime start;
	start.Year = 2020;
	start.Month = 10;
	start.Day = 28;
	start.Hour = 11;
	start.Minute = 30;
	start.Second = 00;
	DS3231_setDateTime(start)
	
	while(1) {
		_delay_ms(1000);
		DateTime now = DS3231_getDateTime();
		USART_Transmit(now.Second);
			
	}
}