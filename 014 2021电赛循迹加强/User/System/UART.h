#ifndef __UART_H__
#define __UART_H__
#include "stm32f10x.h"
void USART1_Configuration(unsigned char State);
void USART2_Configuration(unsigned char State);
void USART3_Configuration(unsigned char State);
void USART4_Configuration(void);
void USART5_Configuration(void);
void USART_SendByte(USART_TypeDef* USARTx,unsigned char dat);
void USART_SendString(USART_TypeDef* USARTx, unsigned char *str);
void USART_SendBuf(USART_TypeDef* USARTx,unsigned char *buf,unsigned int len);
#endif
