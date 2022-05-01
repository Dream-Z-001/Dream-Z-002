#include <STC15F2K60S2.H>

unsigned char urdat;

void delayms(int ms);
void sendbyte(unsigned char dat);
void uart_init();
void sendstring(unsigned char *str);
void working();

void main(){
	uart_init();
	delayms(10);
	sendstring("Hello,everyone\r\n");
	while(1){
		working();
	}
}

void delayms(int ms){
	int q,w;
	for(q=0;q<ms;q++)
		for(w=0;w<845;w++);
}

void uart_init(){
	TMOD=0x20;
	TH1=0XFD;
	TL1=0XFD;
	TR1=1;
	SCON=0X50;
	AUXR&=0X40;
	ES=1;
	EA=1;
}
void uart_service() interrupt 4{
	if(RI==1){
		RI=0;
		urdat=SBUF;
	}
}
void working(){
	if(urdat!=0){
		switch(urdat){
			case 0x01:
				sendstring("Hello\r\n");urdat=0x00;
				break;
			case 0x02:
				sendstring("Goodbye\r\n");urdat=0x00;
				break;
			case 0x03:
				sendstring("Happy\r\n");urdat=0x00;
				break;
		}
	}
}
void sendbyte(unsigned char dat){
	SBUF=dat;
	while(TI==0);
	TI=0;
}
void sendstring(unsigned char *str){
	while(*str !='\0'){
	sendbyte(*str++);
	}
}
