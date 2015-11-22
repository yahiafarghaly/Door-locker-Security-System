/*
 * MC2.c
 *
 * Created: 9/22/2015 8:56:26 AM
 *  Author: Yahia
 */ 


#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "External_EEPROM.h"
#include "uart.h"
#include "timer.h"
#include "initialization.h"

#define M1_ID 0x01
#define M2_ID 0x02
#define FirstLaunchValue  0x39
enum ComProtocals{SuccessAccess=0x25,FailureAccess=0x88
	,EndOfOperation=0x77,DoorLock=0x40,DoorUnlock=0x98,GetPassword=0x14,Mismatch=0x18,NewPass=0x41};

uint8 g_NewStart;/*Determine weather this is the first time to launch the program*/
uint16 g_PasswardAddress=0x13f;
uint16 g_FisrtTimeLaunchAddress=0x3ff;
uint8 g_Password[5];

int main(void)
{
	uint8 TempArr[5];
	uint8 LoopingIndex=0;
	uint8 RecievedFlag=0;
	
	InitPeripherals();
	InitPorts();
	//EEPROM_Write_Byte(g_FisrtTimeLaunchAddress,0); //for test
	EEPROM_Read_Byte(g_FisrtTimeLaunchAddress,&g_NewStart);
	while(UART_recieveByte() != M1_ID){};/*wait for M1 ready*/	
	UART_sendByte(g_NewStart);
	
		if(g_NewStart != FirstLaunchValue)
			{
			while(UART_recieveByte() != M1_ID); //Wait for user input
					for(uint8 index=0; index<5;index++)
							g_Password[index]=UART_recieveByte();
				
					for(uint8 index=0; index<5;index++){
							EEPROM_Write_Byte(g_PasswardAddress+index,g_Password[index]);
							_delay_ms(10);
							}
			EEPROM_Write_Byte(g_FisrtTimeLaunchAddress,FirstLaunchValue);/*Write Launch Value inside EEPROM*/													
			}else
			{
				for(LoopingIndex=0; LoopingIndex<5;LoopingIndex++)
					EEPROM_Read_Byte(g_PasswardAddress+LoopingIndex,&g_Password[LoopingIndex]);
			}
	
    while(1)
    {
		RecievedFlag=UART_recieveByte();
		
		if(RecievedFlag == GetPassword)
		{
			UART_sendByte(EndOfOperation);/*I receive you*/
			for(LoopingIndex=0; LoopingIndex<5;LoopingIndex++)
					TempArr[LoopingIndex]=UART_recieveByte();
			for(LoopingIndex=0;LoopingIndex<5;LoopingIndex++)
			{
					if(TempArr[LoopingIndex] != g_Password[LoopingIndex]) break;
			}
						
			UART_sendByte(EndOfOperation);
			if(LoopingIndex!=5) UART_sendByte(Mismatch);
			else UART_sendByte(EndOfOperation);			

		}
		
		else if(RecievedFlag == SuccessAccess)
		{
			/*Motor clockwise 10sec->displaying door is unlock
			motor anti clock wise 10 sec-> displaying door is lock*/
			SET_BIT(PORTD,PD7);
			CLEAR_BIT(PORTD,PD6);
			SET_BIT(PORTD,PD5);
			UART_sendByte(DoorUnlock);
			 TimerDelayInSecond(10);
			 CLEAR_BIT(PORTD,PD5);
			 SET_BIT(PORTD,PD6);
			 UART_sendByte(DoorLock);
			 TimerDelayInSecond(10);
				CLEAR_BIT(PORTD,PD5);
				CLEAR_BIT(PORTD,PD6);
			UART_sendByte(EndOfOperation);
		}
		
		else if(RecievedFlag == FailureAccess){
				/*Turn on Buzzer*/
				SET_BIT(PORTC,PC2);
				TimerDelayInSecond(1);
				CLEAR_BIT(PORTC,PC2);
				TimerDelayInSecond(59);/*JUST FOR TEST BUT CHANGE IT TO 60s*/
				SET_BIT(PORTC,PC2);
				UART_sendByte(EndOfOperation);
		}
		
		else if(RecievedFlag == NewPass)
		{
			
			UART_sendByte(EndOfOperation);/*I receive you*/
			for(LoopingIndex=0; LoopingIndex<5;LoopingIndex++)
						TempArr[LoopingIndex]=UART_recieveByte();
			for(LoopingIndex=0;LoopingIndex<5;LoopingIndex++)
			{
				if(TempArr[LoopingIndex] != g_Password[LoopingIndex]) break;
			}
			
			UART_sendByte(EndOfOperation);/*End Of The Comparsion*/
			if(LoopingIndex!=5) UART_sendByte(Mismatch);
			else {
				/*Successfully match*/
				UART_sendByte(EndOfOperation);
				while(UART_recieveByte() != M1_ID){};/*wait to be ready to send*/
					
				for(uint8 index=0; index<5;index++)
					  g_Password[index]=UART_recieveByte();
					
			    for(uint8 index=0; index<5;index++){
						EEPROM_Write_Byte(g_PasswardAddress+index,g_Password[index]);
						_delay_ms(10);
					}
			   EEPROM_Write_Byte(g_FisrtTimeLaunchAddress,FirstLaunchValue);/*Write Launch Value inside EEPROM*/
			}				
		
			
			
		}
							
		
					
    }
}