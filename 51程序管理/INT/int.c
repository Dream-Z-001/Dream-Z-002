#include "int.h"
typedef unsigned char u8;
typedef unsigned int u16;
void Init_INT0(void)
{
	INT0 = 1;
	IT0 = 0;
	EX0 = 1;
	EA = 1;
}

void ServiceINT0() interrupt 0
{
	/* USER CODE BEGIN */

    /* USER CODE END */
}