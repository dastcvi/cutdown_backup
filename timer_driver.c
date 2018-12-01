/*
 * timer_driver.c
 *
 * Created: 11/20/2018 4:44:38 PM
 *  Author: Alex
 */ 

#include "timer_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* note: the system clock is shipped with a default of the 8 MHz internal RC prescaled down to 1 MHz */

void timer_init(void)
{
	// 1 Mhz clock / 8 (prescale) / 125 (compare) = 1 ms interrupt
	/* set to clear timer on match with OCR1C register */
	_SFR_BYTE(TCCR1) |= 1 << CTC1;
	
	/* load OCR1A and OCR1C with 124 for 1 ms interrupt */
	_SFR_BYTE(OCR1A) = 124; /* for interrupt */
	_SFR_BYTE(OCR1C) = 124; /* for timer clear */
	
	/* enable interrupt on OCR1A match */
	_SFR_BYTE(TIMSK) |= 1 << OCIE1A;
	
	/* start clock */
	_SFR_BYTE(TCCR1) |= 1 << CS12; /* select CS1[3:0] = 1b0010 => CK/8 prescale */
}

// todo: interrupt handler