/*
 * cutdown_backup.c
 *
 * Created: 11/19/2018 4:47:28 PM
 * Author : Alex
 */ 

#include "spi_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

int main(void)
{
	_SFR_BYTE(DDRB) |= 1 << DDB4; /* Configure PB4 as output */
	_SFR_BYTE(PORTB) &= ~(1 << PB4); /* Write PB4 high */
	
	init_spi_slave();
	
	/* enable interrupts */
	sei();
	
    while (1);
}

