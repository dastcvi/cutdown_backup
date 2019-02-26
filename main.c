/*
 * cutdown_backup.c
 *
 * Created: 11/19/2018 4:47:28 PM
 * Author : Alex
 */


#include "cutdown_pinout_revB.h"
#include "spi_driver.h"
#include "timer_driver.h"
#include "eeprom_driver.h"
#include <stdint.h>
#include <stdbool.h>


typedef enum {
	ST_UNARMED,
	ST_ARMED,
	ST_FIRE,
	ST_FINISHED
} States_t;


volatile States_t system_state = ST_UNARMED;


void unarmed(void)
{
	if (check_arm_status()) {
		/* set the timer from EEPROM stored total */
		set_timer(read_eeprom_total_timer());
		write_eeprom_remaining_timer(read_timer());
		
		system_state = ST_ARMED;
	}
	
	/* if we've received a new timer value over SPI, write it to EEPROM */
	if (update_eeprom) {
		update_eeprom = false;
		write_eeprom_total_timer(read_timer());
		write_eeprom_remaining_timer(read_timer());
	}
}

void armed(void)
{
	uint16_t last_eeprom_write = read_timer();
	uint16_t curr_timer = 0;
	
	arm_timer();
	
	/* wait for the timer to expire */
	while (!timer_expired) {
		/* ensure still armed */
		if (!check_arm_status()) {
			disarm_timer();
			set_timer(read_eeprom_total_timer());
			write_eeprom_remaining_timer(read_timer());
			system_state = ST_UNARMED;
			return;
		}
		
		/* update the timer in EEPROM once per minute (to limit write cycles) */
		curr_timer = read_timer();
		if ((last_eeprom_write - curr_timer) >= 60) {
			last_eeprom_write = curr_timer;
			write_eeprom_remaining_timer(curr_timer);
		}
	}
	
	system_state = ST_FIRE;
}

void fire(void)
{
	/* check if the primary MCU has fired a squib before firing the backup */
	if (check_arm_status()) {
		fire_squib();
	}
	
	system_state = ST_FINISHED;
}

void finished(void)
{
	write_eeprom_remaining_timer(read_timer());
	
	/* nothing to do */
	while(1);
}

int main(void)
{
	init_gpio();
	init_spi_slave();
	init_timer();
	init_eeprom();
	
	/* enable interrupts */
	sei();
	
	if (check_arm_status()) {
		/* if armed, go straight to armed and don't update the remaining timer */
		set_timer(read_eeprom_remaining_timer());
		if (read_timer() == 0) {
			system_state = ST_FINISHED;
		} else {
			system_state = ST_ARMED;
		}
	} else {
		/* if not armed, use the stored total timer as remaining and go unarmed */
		write_eeprom_remaining_timer(read_eeprom_total_timer());
		system_state = ST_UNARMED;
	}
	
	while (1) {
		switch (system_state) {
		case ST_UNARMED:
			unarmed();
			break;
		case ST_ARMED:
			armed();
			break;
		case ST_FIRE:
			fire();
			break;
		case ST_FINISHED:
			finished();
			break;
		default:
			unarmed();
			break;
		}
	}
}