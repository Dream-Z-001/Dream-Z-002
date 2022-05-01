#include <stc15f2k60s2.h>
#include "intrins.h"

#define uchar unsigned char
#define uint unsigned int
	
sbit TX = P1^0;  //????
sbit RX = P1^1;  //????
uchar tab[] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff};
uchar dspbuf[] = {10,10,10,10,10,10,10,10};
uint distance,time = 0;
uchar s_flag = 0;

void display();
void load();
void Delay12us();
void send_wave();

void cls()
{
	P2 = (P2 & 0x1f) | 0x80;
	P0 = 0xff;
	P2 = 0x1f;
	
	P2 = (P2 & 0x1f) | 0xa0;
	P0 = 0x00;
	P2 = 0x1f;
}

void main(void)
{
  cls();
	AUXR = 0x80;
  TMOD = 0x10;  //?????????
  TH0 = 0xcd;
  TL0 = 0xd4;  
  TH1 = 0;
  TL1 = 0;  
  TR0 = 1;  //?????
  EA = 1;
  ET0 = 1;  //?????0??
  while(1)
  {
        /** 200???????? */
		if(s_flag)
    {
      s_flag = 0;
            /** ?????0??:????????????? */
// 			ET0 = 0;
      send_wave();  //??????
      TR1 = 1;  //????
			while((RX == 1) && (TF1 == 0));  //??????,??????
			TR1 = 0;  //????

			//????
			if(TF1 == 1)
			{
				TF1 = 0;
				distance = 999;  //???
			}
			else
			{
				/**  ????  */
				time=TH1*256+TL1;
				distance = (unsigned int)(time*0.017);  //????				
			}
			TH1 = 0;
			TL1 = 0;
    }
	}
}

//???0??????
void time0()  interrupt 1  //??????? 1
{
  static unsigned int intr = 0;
	if(++intr == 100){s_flag = 1;intr = 0;}
	
	display();
}

void load()
{
	dspbuf[5] = distance/100;
	dspbuf[6] = distance%100/10;
	dspbuf[7] = distance%10; 
}

void Delay12us()//@11.0592MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	_nop_();
	i = 30;
	while (--i);
}

void send_wave()//???????(40Khz)
{
	unsigned char i = 8;
	
	while(i --)
	{
		TX = 1;
		Delay12us();
		TX = 0;
		Delay12us();
	}
}

void display()
{
	static unsigned char dspcom = 0;
	
	load();
	
	P2 = (P2 & 0x1f) | 0xe0;
	P0 = 0xff;
	P2 = 0x1f;
	
	P2 = (P2 & 0x1f) | 0xc0;
	P0 = 1 << dspcom;
	P2 = 0x1f;
	
	P2 = (P2 & 0x1f) | 0xe0;
	P0 = tab[dspbuf[dspcom]];
	P2 = 0x1f;
	
	if(++dspcom == 8) dspcom = 0;
}
