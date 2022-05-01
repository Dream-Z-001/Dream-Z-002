#include "smg.h"
void Delay_SMG(u16 num)
{
	u16 i;
	while (num--)
		for (i = 0; i < 200; i++);
}
void SelectHC575(u8 channal)
{
	switch (channal)
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

void Ass_Num(u8 num, u8 number[8])
{
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		number[i] = num % 10;
		num = num / 10;
	}
}

void Dispaly(u8 direction, u8 pos, u8 dat, u8 array[8], u8 number[8])
{
	int n = 0, i = 0, k = 0, y = 0;
	if (direction)
	{
		for (i = dat; i < 8; i++)
		{
			k = number[pos - 1 - i];
			if (y >= pos)
				DisplaySMG_Bit(0xff, i);
			else
				DisplaySMG_Bit(array[k], i);
			Cls_Shadow();
			y++;
		}
	}
	else
	{
		for (i = dat; i < 8; i++)
		{
			n = 7 - i;
			k = number[y];
			if (i >= pos)
				DisplaySMG_Bit(0xff, n);
			else
				DisplaySMG_Bit(array[k], n);
			Cls_Shadow();
			y++;
		}
	}
}