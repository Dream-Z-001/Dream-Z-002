#include "btn.h"

void control(void)
{
	if(S7 == 0)
	{
		Delay_BTN(20);
		if(S7 == 0)
		{
			/* USER CODE BEGIN 1 */


            /* USER CODE END 1 */
			while(S7 == 0);
		}
	}
}