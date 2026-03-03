#ifndef __IIC24C64_H__
#define __IIC24C64_H__
#include "stm32f10x.h"
#include "Delay.h"
void IIC24C64_Init(void);
void IIC24C64_WriteAddr(unsigned int Addr,unsigned char dat);
unsigned char IIC24C64_ReadAddr(unsigned int Addr);
void IIC24C64_Write(unsigned int Addr,unsigned char *dat,unsigned char len);
void IIC24C64_Read(unsigned int Addr,unsigned char *dat,unsigned char len);
#endif

