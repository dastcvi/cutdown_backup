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
	_SFR_BYTE(DDRB) |= 1 << DDB3; /* Configure PB3 as output */
	_SFR_BYTE(PORTB) |= 1 << PB3; /* Write PB3 high */
	
	/* enable interrupts */
	sei();
	
	init_spi_slave();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

