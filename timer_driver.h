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

extern volatile bool system_armed;
extern volatile bool timer_expired;

void init_timer(void);

void arm_timer(void);
void disarm_timer(void);
bool arm_status(void);

#endif /* TIMER_DRIVER_H_ */