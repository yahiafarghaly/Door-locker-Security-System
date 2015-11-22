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
#include "lcd.h"
#include "uart.h"

/*This is used to Set your peripherals initializations functions */
inline void InitPeripherals(void) 
{
	/*Don't Forget to include the Peripherals header files above*/
	UART_init();
	LCD_init();	
}

/*This is used to Set Ports initializations*/
inline void InitPorts(void)
{

}


#endif /* INITIALIZATION_H_ */