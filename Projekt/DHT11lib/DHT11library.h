#ifndef DHT11library_H_
#define DHT11library_H_

#define F_CPU 16000000UL

#include <avr/io.h>

typedef struct {
	uint8_t Temperatur;
	uint8_t Humidity;
}DHT11;

#define SET_BIT(port, bit) ((port) |= (1<<bit))
#define CLR_BIT(port, bit) ((port) &= ~((1<<bit)))

#define DHT11_DDR DDRA
#define DHT11_PORT PORTA
#define DHT11_PIN PINA
#define DHT11_BIT PA0

void DHT11_init();
void DHT11_ReadRaw(DHT11 *result);
uint8_t DHT11_ReadTemp();
uint8_t DHT11_ReadHumid();



#endif /* DHT11library_H_ */