/*
 * timer.h
 *
 * Created: 9/22/2015 2:25:10 PM
 *  Author: Yahia
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <avr/interrupt.h>
#include "std_types.h"
#include "common_macros.h"

void Timer0_NormalModeInit(void);
void Timer0_NormalModeDisable(void);
void TimerDelayInSecond(uint8 value);



#endif /* TIMER_H_ */