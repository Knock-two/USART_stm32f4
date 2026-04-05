#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

#define MAX_SIZE_USART_PRINTF 256

void usart_Init(void);
void usart_SendByte(char ch);
void usart_SendString(char str[]);

int fputc(int ch,FILE *f);
void usart_Printf(char *format,...);

#endif

