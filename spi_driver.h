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
	CMD_ARM = 0x05,		/* software workaround for hardware error (arming signal same as SCK, had initially intended UART, not SPI) */
	CMD_DISARM = 0x06,
} SPI_Command_t;

void init_spi_slave(void);

uint16_t read_timer(void);
bool decrement_timer(void);

#endif /* SPI_DRIVER_H_ */