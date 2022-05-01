#include "reg51.h"

sbit S7 = P3^0;
sbit S6 = P3^1;
sbit S5 = P3^2;

typedef unsigned char u8;
typedef unsigned int u16;
u8 code yang[17] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e, 0xbf};
u8 code yin[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40};
u8 code com[8]={0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
u8 ms = 0, s = 0, min = 0, hour = 0;

void Cls_P()
{
	P2 = (P2 & 0x1f | 0xa0);
	P0 = 0x00;
	P2 &= 0x00;
	P2 = (P2 & 0x1f | 0x80); 
	P0 = 0xff; 
	P2 &= 0x00;
}
/*****************************************
void Delay_ms(u16 num)
{
	u16 i;
	while(num--)
		for(i = 0; i < 628; i++);
}
*****************************************/
void Delay(u16 num)
{
	u16 i;
	while(num--)
		for(i = 0; i < 200; i++);
}
void InitTimer0()
{
	TMOD = 0x01;
	TH0 = (65535-10000)/256;
	TL0 = (65535-10000)%256;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void ServiceTimer0() interrupt 1
{
	TH0 = (65535-10000)/256;
	TL0 = (65535-10000)%256;
	if((ms++) == 100) {s++; ms = 0;}
	if(s == 60) {min++; s = 0;}
	if(min == 60) {hour++; min = 0;}
	if(hour == 24) hour = 0;
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

void Cls_Shadow()
{
	Delay(1);
	P0 = 0xff;
	Delay(3);
}

void Display_Time()
{
	DisplaySWM_Bit(yang[ms%10], 7);
	Cls_Shadow();
	DisplaySWM_Bit(yang[ms/10], 6);
	Cls_Shadow();
	DisplaySWM_Bit(yang[16], 5);
	Cls_Shadow();
	DisplaySWM_Bit(yang[s%10], 4);
	Cls_Shadow();
	DisplaySWM_Bit(yang[s/10], 3);
	Cls_Shadow();
	DisplaySWM_Bit(yang[16], 2);
	Cls_Shadow();
	DisplaySWM_Bit(yang[min%10], 1);
	Cls_Shadow();
	DisplaySWM_Bit(yang[min/10], 0);
	Cls_Shadow();
}

void key()
{
	if(S5 == 0)
	{
		u8 j = 5;
		while(--j);
		if(S5 == 0)
		{
			ET0 =~ ET0;
			while(S5 == 0)
				Display_Time();
		}
	}
	if(S6 == 0)
	{
		u8 j = 5;
		while(--j);
		if(S6 == 0)
		{
			ms = s = min = 0;
			while(S6 == 0)
				Display_Time();
		}
	}
}

void main(void)
{
	Cls_P();
	InitTimer0();
	while(1)
	{
		Display_Time();
		key();
	}
}
