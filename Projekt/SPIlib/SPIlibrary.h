/**
 @file
 @defgroup SPIlib SPI Library
 @code #include <SPIlibrary.h> @endcode
  
 @brief SPI Library

 This library is made to setup SPI(Serial Peripheral Interface) both on the Master and Slave device.
 After setup the library can be used to both write and read from Master to Slave and vice versa.
 


 @author Morten Nissen, Nicolai De Jong Bjerg & Kevin Pike Darmer
 @copyright (C) 2020 Morten Nissen, Nicolai De Jung Berg & Kevin Pike Darmer, GNU General Public License Version 3

*/

/**@{*/
#ifndef SPILIBRARY_H_
#define SPILIBRARY_H_

#define F_CPU 16000000UL
#define BAUD 9600
#define BAUD_TOL 2
#define SS_ENABLE PORTB &= ~(1<<PB0)
#define SS_DISABLE PORTB |= (1<<PB0)

#include <stdbool.h>


/** 
 @brief SPI_Init is the function to initiate the SPI connection. It should be called once at the start of the running program.
 This function sets all necessary pins to setup the MOSI, SCK and SS as output pins, MISO as input pin, SS pin high, Enables SPI master or slave mode, CPOL to 1 CPHA to 1 and disables Speed double.
 Takes a bool isMaster so if true the device setup will be master and if false the device will be slave.
 */
void SPI_Init(bool isMaster);

/** 
 @brief SPI_Read reads the byte send by the connected device and translate it to a char.
 */
char SPI_Read();

/** 
 @brief SPI_Write writes a byte and sends it to the connected device. Takes a char and translates it to byte.
 */
void SPI_Write(char data);

/** 
 @brief SPI_WriteData a function that sends 2 sets of data with delay to the connected device.
 */
void SPI_WriteData(char address, char data);



#endif /* SPILIBRARY_H_ */