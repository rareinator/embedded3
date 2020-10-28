#include <avr/io.h>
#include <util/twi.h>
#include <stdio.h>
#include "stdio_setup.h"

#define F_CPU 16000000UL
#define F_SCL 100000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)


void i2c_init(void)
{
	TWBR = (uint8_t)TWBR_val;
}

uint8_t i2c_start(uint8_t address)
{
	// reset TWI control register
	TWCR = 0;
	// transmit START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); //clears interrupt bit, start bit, enable bit
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) ); // Creates a mask and waits until the interrupt bit has been set to 0
	
	// check if the start condition was successfully transmitted
	if((TWSR & 0xF8) != TW_START){ return 1; } //11111000
	
	// load slave address into data register
	TWDR = address;
	// start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN); // Clears interrupt bit and enables the operation
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) ); // Creates a mask and waits until the interrupt bit has been set to 0
	
	// check if the device has acknowledged the READ / WRITE mode
	uint8_t TWST = TW_STATUS & 0xF8; //11111000
	if ( (TWST != TW_MT_SLA_ACK) && (TWST != TW_MR_SLA_ACK) ) return 1;
	
	return 0;
}

int main(void)
{
	i2c_init();
	i2c_start(0);

	while(1) 
	{
	}
}