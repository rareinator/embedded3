/*
 * DHT11.h
 *
 * Created: 10/29/2020 10:50:09 AM
 *  Author: rare
 */ 

#ifndef DHT11_H_
#define DHT11_H_

#include <avr/io.h>

typedef struct {
	uint8_t Temperatur;
	uint8_t Humidity;		
}DHT11;

#define SET_BIT(port, bit) ((port) |= (1<<bit))
#define CLR_BIT(port, bit) ((port) &= ~((1<<bit)))

#define DHT11_DDR DDRB
#define DHT11_PORT PORTB
#define DHT11_PIN PINB
#define DHT11_BIT PB3

void DHT11_init();
void DHT11_ReadRaw(DHT11 *result);
uint8_t DHT11_ReadTemp();
uint8_t DHT11_ReadHumid();

#endif /* DHT11_H_ */