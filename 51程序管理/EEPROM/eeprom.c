#include "eeprom.h"
#include "i2c.h"
unsigned char EEPROM_Read(unsigned char addr)
{
	unsigned char dat_Read;
	i2c_start();
	i2c_sendbyte(0xa0);
	i2c_waitack();
	i2c_sendbyte(addr);
	i2c_waitack();
	i2c_start();
	i2c_sendbyte(0xa1);
	i2c_waitack();
	dat_Read = i2c_receivebyte();
	i2c_sendack(1);
	i2c_stop();
	
	return dat_Read;
}

void EEPROM_Write(unsigned char addr, unsigned char dat)
{
	i2c_start();
	i2c_sendbyte(0xa0);
	i2c_waitack();
	i2c_sendbyte(addr);
	i2c_waitack();
	i2c_sendbyte(dat);
	i2c_waitack();
	i2c_stop();
}