/*
 * clock_and_timer.h
 *
 *  Created on: Mar 10, 2021
 *      Author: vishn
 */

#ifndef CLOCK_AND_TIMER_H_
#define CLOCK_AND_TIMER_H_

#include <stdint.h>

void CLK_Init(void);
void timer_init(int8_t duty_cycle);
void change_duty_cycle(int8_t duty_cycle);




#endif /* CLOCK_AND_TIMER_H_ */
