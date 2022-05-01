#ifndef __EEPROM_H_
#define __EEPROM_H_
#include <STC15F2K60S2.H>
unsigned char EEPROM_Read(unsigned char addr);
void EEPROM_Write(unsigned char addr, unsigned char dat);
#endif