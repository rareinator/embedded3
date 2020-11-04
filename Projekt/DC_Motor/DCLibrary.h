#ifndef MOTOR_H_
#define MOTOR_H_
/*
 * motor.h
 *
 * Created: 03-11-2020 08:59:36
 *  Author: Kevin Pike Darmer	
 */ 

#include <avr/io.h>


//Sets the Duty Cycle to 100%
#define Fan_Start OCR0A = 255;

//Sets the Duty Cycle to 0%
#define Fan_Stop OCR0A = 0;

//////////////////////////////////////////////////////////////////////////
//Initializes the motor by:
// Setting the Compare output mode
// Setting the Waveform Generation Mode
// Setting the Clock Select Bit
// Setting the port to output
//////////////////////////////////////////////////////////////////////////
extern void motor_init();
//Starts the Fan
extern void Start_Fan();
//Stops the Fan
extern void Stop_Fan();

#endif /* MOTOR_H_ */