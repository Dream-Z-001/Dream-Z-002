#ifndef __BTN_H_
#define __BTN_H_

#include <STC15F2K60S2.H>
typedef unsigned char u8;
typedef unsigned int u16;
#define Delay_BTN(u16 num) {/
	u16 i;/
	while(num--)/
		for(i=0; i<628; i++);/
}
sbit S7 = P3^0;
void control(void)
#endif