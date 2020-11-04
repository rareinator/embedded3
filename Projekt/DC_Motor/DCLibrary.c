
/*
 * motor.c
 *
 * Created: 03-11-2020 08:59:25
 *  Author: Kevin Pike Darmer
 */
#include "DClibrary.h"

#define F_CPU 16000000UL


void motor_init(){
	
	// Compare Output Mode: Fast PWM Mode: Clear OC0A on Compare Match, set OC0A at BOTTOM, non-inverting mode (Table 16-3)
	TCCR0A |= (1<<COM0A1);					// datasheet 16.9.1
	
	//Waveform Generation Mode: Mode 3 Fast PWM: WGM0 = 1, WGM1 = 1 (Table 16-8)
	TCCR0A |= (1<<WGM00) | (1<<WGM01);
	
	// Clock Select Bit: clk/64 prescaling: CS = 011 : CS01 = 1, CS00 = 1 (Table 16-9), frekv. = 980Hz
	TCCR0B |= (1<<CS01) | (1<<CS00);		// datasheet 16.9.2
	
	// Set output to OC0A = PB7, see datasheet 16.9.4 and Arduino MEGA pin configuration: (pin 13), same as LED
	DDRB |= (1<<PB7);
}

void Start_Fan(){
	Fan_Start
}

void Stop_Fan(){
	Fan_Stop
}