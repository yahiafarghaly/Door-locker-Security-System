/*
 * MC1.c
 *
 * Created: 9/22/2015 8:55:50 AM
 *  Author: Yahia
 */ 

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "initialization.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "user_interface.h"
#include "timer.h"

#define M1_ID 0x01
#define M2_ID 0x02
#define FirstLaunchValue  0x39

	
extern uint8 NewPassword[5];
uint8 g_NewStart;

int main(void)
{
	SET_BIT(DDRB,0);
	uint8 PressedKey;
	InitPeripherals();
	UART_sendByte(M1_ID); /*M1 is ready*/

	g_NewStart =UART_recieveByte();
	if (g_NewStart != FirstLaunchValue)
	{
		SetNewPassword();
		UART_sendByte(M1_ID);
		for(uint8 index=0;index<5;index++)
				UART_sendByte(NewPassword[index]);		
	}
	
    while(1)
    {
		ShowMainMenu();
		
		PressedKey=KeyPad_getPressedKey();
		_delay_ms(250);
			if(PressedKey==StarKey)
				{
						if(true == EnterPassword())
						{
							UART_sendByte(SuccessAccess);/*I am sending you*/
						
							while(UART_recieveByte() != DoorUnlock){}
								LCD_clearScreen();
								LCD_displayString("Door is");
								LCD_displayStringRowColumn(1,0,"unlocking");
							while(UART_recieveByte()!= DoorLock){}	
								LCD_clearScreen();
								LCD_displayString("Door is");
								LCD_displayStringRowColumn(1,0,"locking");
							
							while(UART_recieveByte() != EndOfOperation){};
					
						}
						else
						{
							UART_sendByte(FailureAccess);
							while(UART_recieveByte() != EndOfOperation){};
						}				
				}
			else if(PressedKey == DailKey)	
				{
					if(true == EnterOldPassword()){
						/*Successfully set,let's send it now*/
						UART_sendByte(M1_ID);
						for(uint8 index=0;index<5;index++)
								UART_sendByte(NewPassword[index]);
					}
				}
			else{
				LCD_clearScreen();
				LCD_displayString("Please Write");
				LCD_displayStringRowColumn(1,0,"a valid key");
				_delay_ms(1000);
				}
        
    }
}