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

volatile uint16_t timer_value = 0;
volatile bool timer_enable = false;

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

void set_timer_hi(uint8_t value)
{
	cli();
	timer_value &= (uint16_t) 0x00ff;
	timer_value |= ((uint16_t) value) << 8;
	sei();
}

void set_timer_lo(uint8_t value)
{
	cli();
	timer_value &= (uint16_t) 0xff00;
	timer_value |= (uint16_t) value;
	sei();
}

uint16_t read_timer(void)
{
	uint16_t value = 0;
	
	cli();
	value = timer_value;
	sei();
	
	return value;
}

void enable_timer()
{
	cli();
	timer_enable = true;
	sei();
}

void disable_timer()
{
	cli();
	timer_enable = false;
	sei();
}

ISR (TIMER1_COMPA_vect)
{
	static bool gpio = false;
	
	cli();
	if (timer_enable) {
		if (timer_value > 0) {
			timer_value--;
		}
	}
	sei();
	
	if (gpio) {
		_SFR_BYTE(PORTB) &= ~(1 << PB4); /* Write PB4 low */
		gpio = false;
	} else {
		_SFR_BYTE(PORTB) |= 1 << PB4;
		gpio = true;
	}
}