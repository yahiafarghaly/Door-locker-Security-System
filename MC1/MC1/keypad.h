

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include <util/delay.h>
#define N_col 4
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_DIR DDRA 
/*Note on Connecting the keypad :
	PX7 is connect to the last pin to right in keypad,then go backward
	PX3 is connect to the last pin to down in keypad,then go up
*/
/*
 * Function responsible for getting the pressed keypad key
 */
uint8 KeyPad_getPressedKey(void);
/*
 * Responsible for returning a number of 4 bytes range of length "NumberOfPressing"
 * i.e. : if you clicked 1,5,9 respectively on keypad,you will get 159 as return
 * a delay from one press and another is equal to 300 ms(Approx to the Normal human Press)
 * return -1 on fail
 * Press non number value will give you a wrong input
 */
uint32 KeyPad_getSeriesOfPressedNumbers(uint8 NumberOfPressing);
/*
 * Function responsible for mapping the switch number in the keypad to 
 * its corresponding functional number in the proteus for 4x3 keypad 
 */
uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number); /*C code may be configurable*/

/*
 * Function responsible for mapping the switch number in the keypad to 
 * its corresponding functional number in the proteus for 4x4 keypad  
 */
uint8 KeyPad_4x4_adjustKeyNumber(uint8 button_number); /*C code may be configurable*/
#endif /* KEYPAD_H_ */
