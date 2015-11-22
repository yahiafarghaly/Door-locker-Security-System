/*
 * user_interface.c
 *
 * Created: 9/22/2015 9:29:37 AM
 *  Author: Yahia
 */ 

#include "user_interface.h"

uint16 g_PasswardAddress=0x1f;
uint8 NewPassword[5];

void ShowMainMenu(void)
{
	LCD_clearScreen();
	LCD_displayString("*:Open Door");
	LCD_goToRowColumn(1,0);
	LCD_displayString("#:change password");
}


void SetNewPassword(void){

	uint8 RepeatedPassword[5]={0};
	bool NonMatchingFlag=false;
	uint8 LoopingIndex=0;
	
	while(1){	
				
				LCD_clearScreen();
				LCD_displayString("Enter new pass:");
				LCD_goToRowColumn(1,0);
						
				_delay_ms(300);
				LoopingIndex=0;
				while((NewPassword[LoopingIndex]=KeyPad_getPressedKey()) != EnterKey)
						{
							LCD_displayString("*");
							_delay_ms(300);
							LoopingIndex++;
						}
				
				_delay_ms(250);
				LCD_clearScreen();
				LCD_displayString("Renter the Pass:");
				LCD_goToRowColumn(1,0);
				LoopingIndex=0;
				while((RepeatedPassword[LoopingIndex]=KeyPad_getPressedKey()) != EnterKey)
						{
							LCD_displayString("*");
							_delay_ms(300);
							LoopingIndex++;
						}
						
				if(LoopingIndex > 5 || LoopingIndex<5)
					{
						LCD_clearScreen();
						LCD_displayString("Password Must ");
						LCD_goToRowColumn(1,0);
						LCD_displayString("Be 5 Digits!");
						_delay_ms(1000);
						continue;
					}
						
				LCD_clearScreen();
				for(LoopingIndex=0; LoopingIndex<5;LoopingIndex++)
					{
						if(NewPassword[LoopingIndex] != RepeatedPassword[LoopingIndex])
							{									
								NonMatchingFlag=true;
								break;
							}	
					}/*Here may Lie a bug that happens in simulation ! */
					if(NonMatchingFlag){
						LCD_clearScreen();
						LCD_displayString("Password doesn't");
						LCD_goToRowColumn(1,0);
						LCD_displayString("match");
						_delay_ms(1000);
						 continue;
					}						 
					else break;					
						
		}					
	
}

bool EnterPassword(){
	uint8 TempArrForCheckPassword[5];
	uint8 loopingIndex=0;
	uint8 MismatchFlag=0;
	uint8 MisMatchCounter=0;
	while(1){
		
		LCD_clearScreen();
		LCD_displayString("Enter Password");
		LCD_goToRowColumn(1,0);
		loopingIndex=0;
		while((TempArrForCheckPassword[loopingIndex]= KeyPad_getPressedKey()) != EnterKey)
			{
				loopingIndex++;
				LCD_displayString("*");
				_delay_ms(300);	
			}
			
		UART_sendByte(GetPassword);
		while(UART_recieveByte() != EndOfOperation){}/*M2 is ready to get data*/
			
		for(loopingIndex=0;loopingIndex<5;loopingIndex++)
				UART_sendByte(TempArrForCheckPassword[loopingIndex]);
					
		while(UART_recieveByte() != EndOfOperation){}/*wait until comparsion is done*/
		MismatchFlag=UART_recieveByte();
		if(MismatchFlag == Mismatch){
			MisMatchCounter++;
				if(MisMatchCounter == 3){ 
						LCD_clearScreen();
						LCD_displayString("Access is");
						LCD_displayStringRowColumn(1,0,"Denied");
						return false;
						}
				else {
						LCD_clearScreen();
						LCD_displayString("Wrong Pass");
						LCD_displayStringRowColumn(1,0,"Enter another");
						_delay_ms(1000);
						
					}
		}
		else return true;
		
	}

}


bool EnterOldPassword()
{
	uint8 TempArrForCheckPassword[5];
	uint8 loopingIndex=0;
	uint8 MismatchFlag=0;

		LCD_clearScreen();
		LCD_displayString("Old Password:");
		LCD_goToRowColumn(1,0);
		loopingIndex=0;
		while((TempArrForCheckPassword[loopingIndex]= KeyPad_getPressedKey()) != EnterKey)
		{
			loopingIndex++;
			LCD_displayString("*");
			_delay_ms(300);
		}
		
		UART_sendByte(NewPass);
		
	while(UART_recieveByte() != EndOfOperation){}/*M2 is ready to get data*/
	
	for(loopingIndex=0;loopingIndex<5;loopingIndex++)
			UART_sendByte(TempArrForCheckPassword[loopingIndex]);
	
	while(UART_recieveByte() != EndOfOperation){}/*wait until comparsion is done*/
		MismatchFlag=UART_recieveByte();
		
		if(MismatchFlag == Mismatch){
			LCD_clearScreen();
			LCD_displayString("Not Match !");
			_delay_ms(1000);
			return false;
		}
		else{		
			SetNewPassword();
			return true;
		}
		
}
