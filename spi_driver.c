/*
 * spi_driver.c
 *
 * Created: 11/20/2018 2:57:48 PM
 *  Author: Alex
 */ 

#include "spi_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>

bool write_timer_hi = false;
bool write_timer_lo = false;
uint16_t timer_value = 0x4281;

void init_spi_slave(void)
{
	/* set DO to output */
	_SFR_BYTE(DDRB) |= 1 << DDB1;     /* Configure PB1 (DO) as output */
	_SFR_BYTE(PORTB) &= ~(1 << PB1);  /* Write DO low */
	
	/* set to 3-wire mode */
	_SFR_BYTE(USICR) |= 1 << USIWM0;
	_SFR_BYTE(USICR) &= ~(1 << USIWM1);
	
	/* set to external clock (ie. slave) in SPI mode 0 */
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
	uint8_t command = 0;
	
	command = _SFR_BYTE(USIDR);
	
	if (write_timer_lo) {
		timer_value &= 0xFF00; /* clear lo */
		timer_value |= command;
		write_timer_lo = false;
	} else if (write_timer_hi) {
		timer_value &= 0x00FF; /* clear hi */
		timer_value |= ((uint16_t) command) << 8;
		write_timer_hi = false;
	} else {
		switch (command) {
		case CMD_EMPTY:
			_SFR_BYTE(USIDR) = 0;
			break;
		case RD_TIMER_HI:
			_SFR_BYTE(USIDR) = timer_value >> 8;
			break;
		case RD_TIMER_LO:
			_SFR_BYTE(USIDR) = timer_value & 0xff;
			break;
		case WR_TIMER_LO:
			write_timer_lo = true;
			_SFR_BYTE(USIDR) = 0;
			break;
		case WR_TIMER_HI:
			write_timer_hi = true;
			_SFR_BYTE(USIDR) = 0;
			break;
		default:
			_SFR_BYTE(USIDR) = 0;
			break;
		}
	}

	/* clear the counter */
	_SFR_BYTE(USISR) |= 1 << USIOIF;
}
