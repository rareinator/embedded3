/*
 * Delay.c
 *
 * Created: 28-Oct-20 12:07:49 PM
 *  Author: jpf
 */ 

#include "Delay.h"

void Delay(void)
{
	volatile unsigned long count = 600000;

	while (count--);
}