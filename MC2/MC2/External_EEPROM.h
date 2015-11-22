
/* M24Cxx External EEPROM*/

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#define ERROR 0
#define SUCCESS 1

#include "i2c.h"

void EEPROM_Init(void);
unsigned char EEPROM_Write_Byte(unsigned short u16addr, unsigned char u8data);
unsigned char EEPROM_Read_Byte(unsigned short u16addr, unsigned char *u8data);
 
#endif /* EXTERNAL_EEPROM_H_ */
