#include <STC15F2K60S2.H>
#include "i2c.h"
#include "adc.h"

int Read_AINx(unsigned char addr)
{
	unsigned char dat;
	i2c_start();
	i2c_sendbyte(0x90);
	i2c_waitack();
	i2c_sendbyte(addr);
	i2c_waitack();
	i2c_stop();
	
	i2c_start();
	i2c_sendbyte(0x91);
	i2c_waitack();
	dat = i2c_receivebyte();
	i2c_sendack(1);
	i2c_stop();
	return dat;
}

void Write_AINx(unsigned char addr, unsigned  char dat)
{
	EA = 0;
	i2c_start();
	i2c_sendbyte(0x90);
	i2c_waitack();
	i2c_sendbyte(addr);
	i2c_waitack();
	i2c_sendbyte(dat);
	i2c_waitack();
	i2c_stop();
	EA = 1;
}

