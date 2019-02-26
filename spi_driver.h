/*
 * spi_driver.h
 *
 * Created: 11/20/2018 2:57:30 PM
 *  Author: Alex
 *
 * This file implements a driver to use the USI interface as
 * a SPI slave device.
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>

/* this typedef is matched in the main MCU's driver */
typedef enum {
	CMD_EMPTY = 0x00,
	RD_TIMER_HI = 0x01,
	RD_TIMER_LO = 0x02,
	WR_TIMER_HI = 0x03,
	WR_TIMER_LO = 0x04,
	WR_TIMER_EEPROM = 0x05,
} SPI_Command_t;

extern volatile bool update_eeprom;

void init_spi_slave(void);

/* only for reboot update from EEPROM */
void set_timer(uint16_t timer);

uint16_t read_timer(void);
bool decrement_timer(void);

#endif /* SPI_DRIVER_H_ */