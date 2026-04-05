#include "stm32f4xx.h"
#include "usart.h"
#include <stdio.h>

int main()
{
		usart_Init();
		
		printf("你好呀，wow~ ⊙o⊙\n");
		usart_Printf("温度：%d℃，电压：%.2fV\n", 1, 3.3);
	
		while(1)
		{
				
		}

}



