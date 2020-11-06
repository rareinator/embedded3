/**	
	@file
	@defgroup DHT11 library
	@code #include <DHT11library.h> @endcode
  
	@brief DHT11 library
	
	The library can be used to connect and read data from a DHT11.

	@author Morten Nissen, Nicolai De Jong Bjerg & Kevin Pike Darmer
	@copyright (C) 2020 Morten Nissen, Nicolai De Jung Berg & Kevin Pike Darmer, GNU General Public License Version 3

*/

/**@{*/

#ifndef DHT11library_H_
#define DHT11library_H_

#define F_CPU 16000000UL

#include <avr/io.h>

/** 
 @brief DHT11 is the struct that contains both the temperature and humidity
 */
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

/** 
 @brief DHT11_init is the function that should be called once in the beginning of the program.
 This is done to prepare everything for communication.
 */
void DHT11_init();

/** 
 @brief DHT11_ReadRaw is the function that reads the data from the DHT11.

 @param DHT11  *result  is the structure that returns the data from the DHT11
 */
void DHT11_ReadRaw(DHT11 *result);

/** 
 @brief DHT11_ReadTemp only reads the temperature, it does this by calling the ReadRaw
 and then returning the temperature

 @return uint8_t the temperature
 */
uint8_t DHT11_ReadTemp();

/** 
 @brief DHT11_ReadHumid only reads the humidity, it does this by calling the ReadRaw
 and then returning the humidity

 @return uint8_t the humidity
 */
uint8_t DHT11_ReadHumid();



#endif /* DHT11library_H_ */