/*
 * eeprom_driver.c
 *
 * Created: 2/26/2019 11:18:53 AM
 *  Author: Alex
 */ 

#include "eeprom_driver.h"

void init_eeprom()
{
	/* initialize address to 0 */
	_SFR_WORD(EEAR) = 0;
	
	/* erase and write in one (atomic) operation, disable interrupt */
	_SFR_BYTE(EECR) &= ~((1 << EEPM0) | (1 << EEPM1) | (1 <<EERIE));
}

void write_eeprom(EEPROM_Address_t addr, uint8_t data)
{
	/* ensure no ongoing write */
	while ((_SFR_BYTE(EECR) & (1 << EEPE)) != 0);
	
	/* disable programming */
	_SFR_BYTE(EECR) &= ~((1 << EEMPE) | (1 << EEPE));
	
	/* set up the write address (enforce 9 bits) and data */
	_SFR_WORD(EEAR) = (uint16_t) addr & 0x1FF;
	_SFR_BYTE(EEDR) = data;
	
	/* enable programming */
	_SFR_BYTE(EECR) |= (1 << EEMPE);
	
	/* begin programming */
	_SFR_BYTE(EECR) |= (1 << EEPE);
	
	/* wait for programming to conclude */
	while ((_SFR_BYTE(EECR) & (1 << EEPE)) != 0);
}

uint8_t read_eeprom(EEPROM_Address_t addr)
{
	/* ensure no ongoing write */
	while ((_SFR_BYTE(EECR) & (1 << EEPE)) != 0);
	
	/* set up the read address (enforce 9 bits) */
	_SFR_WORD(EEAR) = (uint16_t) addr & 0x1FF;
	
	/* perform the read */
	_SFR_BYTE(EECR) |= (1 << EERE);
	
	/* return the byte in the data register */
	return (_SFR_BYTE(EEDR));
}

void write_eeprom_remaining_timer(uint16_t timer)
{
	write_eeprom(REMAIN_TIMER_H_ADDR, (uint8_t) (timer >> 8));
	write_eeprom(REMAIN_TIMER_L_ADDR, (uint8_t) (timer & 0xFF));
}

uint16_t read_eeprom_remaining_timer(void)
{
	uint16_t timer = 0;
	
	timer |= ((uint16_t) read_eeprom(REMAIN_TIMER_H_ADDR)) << 8;
	timer |= (uint16_t) read_eeprom(REMAIN_TIMER_L_ADDR);
	
	return timer;
}

void write_eeprom_total_timer(uint16_t timer)
{
	write_eeprom(TOTAL_TIMER_H_ADDR, (uint8_t) (timer >> 8));
	write_eeprom(TOTAL_TIMER_L_ADDR, (uint8_t) (timer & 0xFF));
}

uint16_t read_eeprom_total_timer(void)
{
	uint16_t timer = 0;
	
	timer |= ((uint16_t) read_eeprom(TOTAL_TIMER_H_ADDR)) << 8;
	timer |= (uint16_t) read_eeprom(TOTAL_TIMER_L_ADDR);
	
	return timer;
}