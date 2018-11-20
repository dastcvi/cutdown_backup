/*
 * spi_driver.c
 *
 * Created: 11/20/2018 2:57:48 PM
 *  Author: Alex
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void init_spi_slave(void)
{
	/* set DO to output */
	_SFR_BYTE(DDRB) |= 1 << DDB1;     /* Configure PB1 (DO) as output */
	_SFR_BYTE(PORTB) &= ~(1 << PB3);  /* Write DO low */
	
	/* set to 3-wire mode */
	_SFR_BYTE(USICR) |= 1 << USIWM0;
	_SFR_BYTE(USICR) &= ~(1 << USIWM1);
	
	/* set to external clock (ie. slave) */
	_SFR_BYTE(USICR) |= 1 << USICS1;
	_SFR_BYTE(USICR) &= ~(1 << USICS0);
	_SFR_BYTE(USICR) &= ~(1 << USICLK);
	
	/* enable the counter overflow interrupt (general interrupts enabled in main) */
	_SFR_BYTE(USICR) |= 1 << USIOIE;
	
	/* clear the counter */
	_SFR_BYTE(USISR) |= 1 << USIOIF;
}

ISR (USI_OVF_vect)
{
	/* clear the counter */
	_SFR_BYTE(USISR) |= 1 << USIOIF;
	
	_SFR_BYTE(USIDR) = 0;
}

/* ISR for counter overflow
 *
 * clear/reset counter, clear interrupt condition
 * read data register
 * switch (data register)
 * case, known command
 *    _critical(write result to data register)
 * default
 *    write 0 to data register
 */