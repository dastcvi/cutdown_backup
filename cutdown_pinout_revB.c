/*
 * cutdown_pinout_revB.c
 *
 * Created: 2/26/2019 10:43:52 AM
 *  Author: Alex
 */ 

#include "cutdown_pinout_revB.h"


void init_gpio()
{
	_SFR_BYTE(DDRB) |= 1 << DDB4; /* Configure PB4 (squib gate) as output */
	_SFR_BYTE(PORTB) &= ~(1 << SQUIB_PIN); /* Write squib gate low */
	
	_SFR_BYTE(PORTB) |= (1 << SYSTEM_ARM_PIN); /* Set PB3 (nSYSTEM_ARM) as input */
}


bool check_arm_status(void)
{
	return (((_SFR_BYTE(PINB) >> PB3) & 1) == 0);
}


void fire_squib(void)
{
	volatile uint32_t iter = 0;
	
	/* write squib gate high */
	_SFR_BYTE(PORTB) |= (1 << PB4);
	
	/* wait for ~10s */
	for (iter = 0; iter < 400000; iter++);
	
	/* write squib gate low */
	_SFR_BYTE(PORTB) &= ~(1 << PB4);
}