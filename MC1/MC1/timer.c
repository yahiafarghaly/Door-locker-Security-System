/*
 * timer.c
 *
 * Created: 9/22/2015 2:24:56 PM
 *  Author: Yahia
 */ 

#include "timer.h"

uint8 g_NumberOfoverflow=0;
uint8 g_NumverOfSeconds=0;

ISR(TIMER0_OVF_vect)
{
	g_NumberOfoverflow++;
	if(g_NumberOfoverflow == 30)
		g_NumverOfSeconds++;
}

void Timer0_NormalModeInit(void)
{
	TCNT0=0;
	TCCR0=(1<FOC0)|(1<<CS02)|(1<<CS00); /*prescaler of 1024*/
	TIMSK=(1<<TOIE0); /*Interrupt module enabled*/
	sei();
}

void Timer0_NormalModeDisable(void)
{
	CLEAR_BIT(TIMSK,TOIE0);
	cli();
}


void TimerDelayInSecond(uint8 value)
{
	Timer0_NormalModeInit();
	while(g_NumverOfSeconds <= value){};
	Timer0_NormalModeDisable();	
	g_NumberOfoverflow=0;
	g_NumverOfSeconds=0;
}
