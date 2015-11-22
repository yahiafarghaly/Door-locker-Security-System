/*Include the necessary libraries to start working*/


#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_


#ifndef F_CPU
#define F_CPU 8000000UL //8MHz Clock frequency
#endif  

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

enum ComProtocals{SuccessAccess=0x25,FailureAccess=0x88
	,EndOfOperation=0x77,DoorLock=0x40,DoorUnlock=0x98,GetPassword=0x14,Mismatch=0x18,NewPass=0x41};

#endif /* MICRO_CONFIG_H_ */