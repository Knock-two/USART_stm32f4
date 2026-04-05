#include "usart.h"

void usart_Init(void)
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOAEN,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2ENR_USART1EN,ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_StructInit(&GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9| GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		USART_InitTypeDef USART_InitStructure;
		USART_StructInit(&USART_InitStructure);

		USART_InitStructure.USART_BaudRate = 115200;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1,&USART_InitStructure);
		
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
		
		USART_Cmd(USART1, ENABLE);
}

void usart_SendByte(char ch)
{
				USART_SendData(USART1,ch);
				while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
}

void usart_SendString(char str[])
{
		int len=strlen(str);
		for(uint8_t i=0;i<len;i++)
		{
				USART_SendData(USART1,str[i]);
				while(!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
		}
}

int fputc(int ch,FILE *f)
{
		usart_SendByte(ch);
		return ch;
}

void usart_Printf(char *format,...)
{
		char String[MAX_SIZE_USART_PRINTF];
		
		va_list args;
		va_start(args,format);
		vsnprintf(String,MAX_SIZE_USART_PRINTF,format,args);
		va_end(args);
		usart_SendString(String);
}

