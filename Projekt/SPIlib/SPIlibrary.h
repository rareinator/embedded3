#ifndef SPILIBRARY_H_
#define SPILIBRARY_H_

#define F_CPU 16000000UL
#define BAUD 9600
#define BAUD_TOL 2
#define SS_ENABLE PORTB &= ~(1<<PB0)
#define SS_DISABLE PORTB |= (1<<PB0)

#include <stdbool.h>


void SPI_Init(bool isMaster);
char SPI_Read();
void SPI_Write(char data);
void SPI_WriteData(char address, char data);



#endif /* SPILIBRARY_H_ */