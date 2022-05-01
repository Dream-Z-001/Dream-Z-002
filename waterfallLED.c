
void delay(void)		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 9;
	j = 104;
	k = 139;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void waterfallLED(void)
{
	unsigned int i;
	P0 = 0xff;
	for(i = 0; i < 8; i++)
	{
		P2 = ((P2 & 0x1f) | 0x80);
		P0 = 0x01<<i;
		P0 =~ P0;
		P2 &= 0x1f;
		delay();
	}
}