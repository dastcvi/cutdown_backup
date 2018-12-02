/*
 * cutdown_backup.c
 *
 * Created: 11/19/2018 4:47:28 PM
 * Author : Alex
 */

#include "spi_driver.h"
#include "timer_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint16_t iter = 0;

int main(void)
{
	_SFR_BYTE(DDRB) |= 1 << DDB4; /* Configure PB4 (squib gate) as output */
	_SFR_BYTE(PORTB) &= ~(1 << PB4); /* Write squib gate low */
	
	_SFR_BYTE(PORTB) |= (1 << PB3); /* Set PB3 (primary squib fired) as input */
	
	init_spi_slave();
	init_timer();
	
	/* enable interrupts */
	sei();
	
    while (!timer_expired);
	
	/* check if the primary MCU has fired a squib before firing the backup */
	if (((_SFR_BYTE(PINB) >> PB3) & 1) == 0) {
		_SFR_BYTE(PORTB) |= (1 << PB4); /* Write squib gate high */
	
		for (iter = 0; iter < 40000; iter++);
	
		_SFR_BYTE(PORTB) &= ~(1 << PB4); /* Write squib gate low */
	}
	
	while(1);
}

