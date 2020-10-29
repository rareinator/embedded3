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

#define SET_INPUT(port, bit) ((port) &= ~(1<<bit))
#define SET_OUTPUT(port, bit) ((port) |= (1<<bit))

#define DHT11_DDR DDRE
#define DHT11_PORT PORTE
#define DHT11_PIN PE4

void DHT11_init();
void DHT11_ReadRaw();
void DHT11_ReadTemp();
void DHT11_ReadHumid();
void DHT11_Read(DHT11 *data);


#endif /* DHT11_H_ */