#include <STC15F2K60S2.H>

#include "onewire.h"
typedef unsigned char u8;
typedef unsigned int u16;
void Display_Time_TEMP(u8 num7, u8 num6, u8 num5);
void Read_Temperature(void);


u16 temperature;

u8 SMGDot_CA[10]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
u8 SMGNoDot_CA[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x90,0x90};

void Delay(u16 t)
{
	while(t--)
	{
		Display_Time_TEMP(SMGNoDot_CA[temperature%10], 
											SMGDot_CA[(temperature%100)/10], 
											SMGNoDot_CA[temperature/100]);
	}
}
void Cls_P(void)
{
	P2 = ((P2 & 0x1f) | 0x80); 
	P0 = 0xff;
	P2 &= 0x1f;
	P2 = ((P2 & 0x1f) | 0xa0);
	P0 = 0x00;
	P2 &= 0x1f;
	P2 = ((P2 & 0x1f) | 0xc0);
	P0 = 0x00;
	P2 &= 0x1f;
}

void Delay_SMG(u16 num)
{
	u16 i;
	while(num--)
		for(i = 0; i < 200; i++);
}
void SelectHC575(u8 channal)
{
	switch(channal)
	{
		case 4:
			P2 = ((P2 & 0x1f) | 0x80);
		break;
		case 5:
			P2 = ((P2 & 0x1f) | 0xa0);
		break;
		case 6:
			P2 = ((P2 & 0x1f) | 0xc0);
		break;
		case 7:
			P2 = ((P2 & 0x1f) | 0xe0);
		break;
	}
}

void DisplaySWM_Bit(u8 value, u8 pos)
{
	SelectHC575(6);
	P0 = 0x01 << pos;
	SelectHC575(7);
	P0 = value;
}

void Cls_Shadow(void)
{
	Delay_SMG(1);
	P0 = 0xff;
	Delay_SMG(3);
}
//Display_Time_TEMP(SMGNoDot_CA[temperature%10], SMGNoDot_CA[temperature/10], 0xff);
//Display_Time_TEMP(SMGNoDot_CA[temperature%10], SMGDot_CA[(temperature%100)/10], SMGNoDot_CA[temperature/100]);														]);
void Display_Time_TEMP(u8 num7, u8 num6, u8 num5)
{
	DisplaySWM_Bit(num7, 7);
	Cls_Shadow();
	DisplaySWM_Bit(num6, 6);
	Cls_Shadow();
	DisplaySWM_Bit(num5, 5);
	Cls_Shadow();
	DisplaySWM_Bit(0xff, 4);
	Cls_Shadow();
	DisplaySWM_Bit(0xff, 3);
	Cls_Shadow();
	DisplaySWM_Bit(0xff, 2);
	Cls_Shadow();
	DisplaySWM_Bit(0xff, 1);
	Cls_Shadow();
	DisplaySWM_Bit(0xff, 0);
	Cls_Shadow();
}
void Read_Temperature(void)
{
    unsigned int temp;
    unsigned char LSB,MSB;
  
  	init_ds18b20();
  	Write_DS18B20(0xCC);
  	Write_DS18B20(0x44); //启动温度转换
  	Delay(10);

  	init_ds18b20();
  	Write_DS18B20(0xCC);
  	Write_DS18B20(0xBE); //读取寄存器
		EA = 0;
  	LSB = Read_DS18B20(); //低字节
  	MSB = Read_DS18B20(); //高字节
	/* INT CHOOSE 1 */
//		temp = MSB;
//		temp <<= 8;
//		temp=temp|LSB;
//		temp>>=4;
	
	// /* INT CHOOSE 2 */
 	// temp = (MSB & 0x0f);
	// temp <<= 8;
	// temp |= LSB;
	// temp=temp*0.0625;

	// /* FLOAT CHOOSE */
	 temp = (((unsigned int)MSB << 8) + LSB)*0.625;
  	temperature = temp;
}

void main(void)
{
	Cls_P();
	while(1)
	{
		Read_Temperature();
		Display_Time_TEMP(SMGNoDot_CA[temperature%10], 
											SMGDot_CA[(temperature%100)/10], 
											SMGNoDot_CA[temperature/100]);	
	}
}