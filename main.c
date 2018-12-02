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
	_SFR_BYTE(DDRB) |= 1 << DDB4; /* Configure PB4 as output */
	_SFR_BYTE(PORTB) &= ~(1 << PB4); /* Write PB4 low */
	
	init_spi_slave();
	init_timer();
	
	/* enable interrupts */
	sei();
	
    while (!timer_expired);
	
	_SFR_BYTE(PORTB) |= (1 << PB4); /* Write PB4 high */
	
	for (iter = 0; iter < 40000; iter++);
	
	_SFR_BYTE(PORTB) &= ~(1 << PB4); /* Write PB4 low */
	
	while(1);
}

