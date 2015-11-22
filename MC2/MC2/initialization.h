/*
 * initialization.h
 *
 * Created: 9/15/2015 11:22:11 PM
 *  Author: Yahia
 */ 
#ifndef INITIALIZATION_H_
#define INITIALIZATION_H_

#include "micro_config.h"
#include "common_macros.h"
#include "uart.h"
#include "External_EEPROM.h"

/*This is used to Set your peripherals initializations functions */
inline void InitPeripherals(void) 
{
	/*Don't Forget to include the Peripherals header files above*/
	UART_init();
	EEPROM_Init();
	
	
}

/*This is used to Set Ports initializations*/
inline void InitPorts(void)
{
	SET_BIT(DDRD,PD5);
	SET_BIT(DDRD,PD6);
	SET_BIT(DDRD,PD7);
	SET_BIT(DDRC,PC2);
	PORTD=0;	
	/*for test*/
	SET_BIT(DDRA,PA0);
	CLEAR_BIT(PORTA,PA0);
}


#endif /* INITIALIZATION_H_ */