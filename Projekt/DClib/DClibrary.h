#ifndef DCLIBRARY_H_
#define DCLIBRARY_H_
/*
 * motor.h
 *
 * Created: 03-11-2020 08:59:36
 *  Author: Kevin Pike Darmer	
 */ 

#include <avr/io.h>
#include <stdbool.h>

//Sets the Fan Duty Cycle register
#define Fan OCR0A

//Sets the Duty Cycle to 0%
#define Stop 0;

//Sets the Duty Cycle
uint8_t Speed;

//////////////////////////////////////////////////////////////////////////
//Initializes the motor by:
// Setting the Compare output mode
// Setting the Waveform Generation Mode
// Setting the Clock Select Bit
// Setting the port to output
//////////////////////////////////////////////////////////////////////////
extern void DCMotor_init();
extern void Set_Speed(uint8_t speed);
//Starts the Fan
extern void Start_Fan();
//Stops the Fan
extern void Stop_Fan();

#endif /* DCLIBRARY_H_ */