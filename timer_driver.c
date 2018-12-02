/*
 * timer_driver.c
 *
 * Created: 11/20/2018 4:44:38 PM
 *  Author: Alex
 */ 

#include "timer_driver.h"
#include "spi_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* note: the system clock is shipped with a default of the 8 MHz internal RC prescaled down to 1 MHz */

volatile bool system_armed = false;
volatile bool timer_expired = false;

void init_timer(void)
{
	// 1 Mhz clock / 8192 (prescale) / 122 (compare) = 0.9994 ms interrupt
	/* set to clear timer on match with OCR1C register */
	_SFR_BYTE(TCCR1) |= 1 << CTC1;
	
	/* load OCR1A and OCR1C with 121 for 1 s interrupt */
	_SFR_BYTE(OCR1A) = 121; /* for interrupt */
	_SFR_BYTE(OCR1C) = 121; /* for timer clear */
	
	/* enable interrupt on OCR1A match */
	_SFR_BYTE(TIMSK) |= 1 << OCIE1A;
	
	/* start clock */
	_SFR_BYTE(TCCR1) |= 0b1110; /* select CS1[3:0] = 0b1110 => CK/8192 prescale */
}

void arm_timer(void)
{
	system_armed = true;
}

void disarm_timer(void)
{
	system_armed = false;
}

bool arm_status(void)
{
	return system_armed;
}

ISR (TIMER1_COMPA_vect)
{	
	if (system_armed) {
		if (decrement_timer()) {
			timer_expired = true;
			system_armed = false;
		}
	}
}