/*
 * eeprom_driver.h
 *
 * Created: 2/26/2019 11:18:40 AM
 *  Author: Alex
 */ 


#ifndef EEPROM_DRIVER_H
#define EEPROM_DRIVER_H


#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum {
	REMAIN_TIMER_H_ADDR = 0,
	REMAIN_TIMER_L_ADDR = 1,
	TOTAL_TIMER_H_ADDR = 2,
	TOTAL_TIMER_L_ADDR = 3,
} EEPROM_Address_t;


void init_eeprom();

void write_eeprom(EEPROM_Address_t addr, uint8_t data);
uint8_t read_eeprom(EEPROM_Address_t addr);

void write_eeprom_remaining_timer(uint16_t timer);
uint16_t read_eeprom_remaining_timer(void);

void write_eeprom_total_timer(uint16_t timer);
uint16_t read_eeprom_total_timer(void);


#endif /* EEPROM_DRIVER_H */