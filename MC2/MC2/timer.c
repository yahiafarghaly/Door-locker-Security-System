/*
 * timer.c
 *
 * Created: 9/22/2015 2:24:56 PM
 *  Author: Yahia
 */ 

#include "timer.h"

volatile uint8 g_NumverOfSecond=0;

ISR(TIMER1_COMPA_vect)
{

	g_NumverOfSecond++;
}

void Timer1_CTCModeInit(void)
{
	sei();
	TCNT1=0;
	TCCR1A|=(1<<FOC1A);
	TCCR1B|=(1<<WGM12)|(1<<CS12)|(1<<CS10);
	TIMSK=(1<<OCIE1A);
	OCR1A=0x1E83;	
	g_NumverOfSecond=0;
	/*It overflowS every one second ,so i take this chance in counting*/
	/* Resolution for one tick = (1024/8*10^6)
	 total time for making one overflow = MaxCounterRegIset * Resolution
	 let this total time =1 second
	 then MaxCounterRegIset = 1 second / Resolution = 7812.5 =0x1E83 In OCR1A */
}

void Timer1_CTCModeDisable(void)
{
	CLEAR_BIT(TIMSK,OCIE1A);
	cli();
}


void TimerDelayInSecond(uint8 value)
{
	Timer1_CTCModeInit();
	while(1){
		
		if(g_NumverOfSecond >= value)
				break;	
	}
  Timer1_CTCModeDisable();
}
