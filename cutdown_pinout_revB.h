/*
 * cutdown_pinout_revB.h
 *
 * Created: 2/26/2019 10:43:36 AM
 *  Author: Alex
 */ 


#ifndef CUTDOWN_PINOUT_REVB_H_
#define CUTDOWN_PINOUT_REVB_H_


#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>


#define SYSTEM_ARM_PIN  PB3
#define SQUIB_PIN       PB4


void init_gpio(void);

bool check_arm_status(void);

void fire_squib(void);


#endif /* CUTDOWN_PINOUT_REVB_H_ */