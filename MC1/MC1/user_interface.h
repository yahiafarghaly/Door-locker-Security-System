/*
 * user_interface.h
 *
 * Created: 9/22/2015 9:30:00 AM
 *  Author: Yahia
 */ 


#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"
#include "lcd.h"
#include "keypad.h"
#include "uart.h"

enum keys{EnterKey=13,StarKey='*',DailKey='+'};

void ShowMainMenu(void);
void SetNewPassword(void);
bool EnterPassword();
bool EnterOldPassword();



#endif /* USER_INTERFACE_H_ */