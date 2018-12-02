/*
 * timer_driver.h
 *
 * Created: 11/20/2018 4:44:27 PM
 *  Author: Alex
 */ 


#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>

void init_timer(void);

void set_timer_hi(uint8_t value);
void set_timer_lo(uint8_t value);
uint16_t read_timer(void);

void enable_timer();
void disable_timer();

#endif /* TIMER_DRIVER_H_ */