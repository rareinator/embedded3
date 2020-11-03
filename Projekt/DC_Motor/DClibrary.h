#ifndef DCLIBRARY_H_
#define DCLIBRARY_H_
/*
 * motor.h
 *
 * Created: 03-11-2020 08:59:36
 *  Author: Kevin Pike Darmer	
 */ 

#include <avr/io.h>



#define Fan_Start OCR0A = 255;
#define Fan_Stop OCR0A = 0;

extern void motor_init();

extern void Start_Fan();
extern void Stop_Fan();

#endif /* DCLIBARY_H_ */