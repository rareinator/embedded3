/**
 @file
 @defgroup DClib DC Motor Library
 @code #include <DClibrary.h> @endcode
  
 @brief DC Motor Library

 Basic library to control the speed(duty cycle) of a DC motor and turning it on or off. 
 
 Connect the DC Motor to the ATMega2560 using given pins

 ![Schematic](../../Datablade/DC Motor schematic.png)

 @author Morten Nissen, Nicolai De Jong Bjerg & Kevin Pike Darmer
 @copyright (C) 2020 Morten Nissen, Nicolai De Jung Berg & Kevin Pike Darmer, GNU General Public License Version 3

*/

/**@{*/
#ifndef DCLIBRARY_H_
#define DCLIBRARY_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdbool.h>

//Sets the Fan Duty Cycle register
#define Fan OCR0A

//Sets the Duty Cycle to 0%
#define Stop 0;

//Sets the Duty Cycle
uint8_t Speed;

/** 
 @brief DCMotor_init is the function to initiate the DC Motor. It should be called once at the start of the running program.
 This function sets all necessary pins to setup the Compare output mode, Waveform Generation mode, Clock select bit and sets the port to output.
 */
extern void DCMotor_init();

/** 
 @brief  Set_Speed takes a uint8_t as input (0-255) and sets it in to the speed variable.
 */
extern void Set_Speed(uint8_t speed);

/** 
 @brief  Start_Fan takes the speed(duty cycle) and shifts it into the port to turn the DC Motor on.
 */
extern void Start_Fan();

/** 
 @brief  Stop_Fan sets the speed(duty cycle) to 0 and by that stops the motor.
 */
extern void Stop_Fan();

#endif /* DCLIBRARY_H_ */