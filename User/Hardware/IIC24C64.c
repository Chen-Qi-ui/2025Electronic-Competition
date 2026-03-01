#include "IIC24C64.h"

/*
SDA=PC5
SCL=PC4
24C64共8K*8bit=64bit容量 即8K byte  一共8*1024=8192个字节
*/
#define IIC24C64_APB_GPIO		RCC_APB2Periph_GPIOC
#define SDA_Pin        			GPIO_Pin_5
#define SDA_GPIO       			GPIOC
#define SCL_Pin        			GPIO_Pin_4
#define SCL_GPIO       			GPIOC


#define SDA_HIGH() 				GPIO_SetBits(SDA_GPIO,SDA_Pin)			//SDA置位
#define SDA_LOW() 				GPIO_ResetBits(SDA_GPIO,SDA_Pin)		//SDA清0
#define SCL_HIGH() 				GPIO_SetBits(SCL_GPIO,SCL_Pin)			//SCL置位
#define SCL_LOW() 				GPIO_ResetBits(SCL_GPIO,SCL_Pin)		//SCL清0

void IIC24C64_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//定义GPIO结构体	
	RCC_APB2PeriphClockCmd(IIC24C64_APB_GPIO,ENABLE);		//开启IIC GPIO模块的时钟
	GPIO_InitStructure.GPIO_Pin=SDA_Pin;					//配置SDA端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;			//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;			//配置端口模式为推挽输出模式
	GPIO_Init(SDA_GPIO,&GPIO_InitStructure);				//对端口进行初始化	
	
	GPIO_InitStructure.GPIO_Pin=SCL_Pin;					//配置SCL端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;			//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;			//配置端口模式为推挽输出模式
	GPIO_Init(SCL_GPIO ,&GPIO_InitStructure);				//对端口进行初始化	
	
	GPIO_SetBits(SDA_GPIO,SDA_Pin);											//SDA置高
	GPIO_SetBits(SCL_GPIO,SCL_Pin);											//SCL置高
}
void SDA_OUT(void)//设置引脚的模式为输出
{
	GPIO_InitTypeDef GPIO_InitStructure;								//定义GPIO结构体	
	GPIO_InitStructure.GPIO_Pin=SDA_Pin;								//配置SDA端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;			//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;			//配置端口模式为推挽输出模式
	GPIO_Init(SDA_GPIO,&GPIO_InitStructure);						//对端口进行初始化	
}
void SDA_IN(void)//设置引脚的模式为输入
{
	GPIO_InitTypeDef GPIO_InitStructure;						//定义GPIO结构体	
	GPIO_InitStructure.GPIO_Pin=SDA_Pin;						//配置SDA端口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;					//配置端口模式为上拉输出模式
	GPIO_Init(SDA_GPIO,&GPIO_InitStructure);					//对端口进行初始化	
}
unsigned char SDA_Read(void)//读取SDA引脚的状态
{
	return GPIO_ReadInputDataBit(SDA_GPIO, SDA_Pin);
}

void IIC24C64_Start(void)//开始动作
{
	SDA_OUT();	//设定为输出模式
	SDA_HIGH();	//SDA置高
	SCL_HIGH();	//SCL置高
	//Delayxus(4);
	SDA_LOW();	//SDA置低
	//Delayxus(4);
	SCL_LOW();	//SCL置低	
}

void IIC24C64_Stop(void)//停止动作
{
	SDA_OUT();	//设定为输出模式
	SCL_LOW();	//SCL置低
	SDA_LOW();	//SDA置低
	//Delayxus(4);
	SCL_HIGH();	//SDA置高
	SDA_HIGH();	//SDA置高	
}
void IIC24C64_Ack(void)//读取应答信号
{
	unsigned char i=0;
	SDA_IN();				//设定为输入模式
	SCL_HIGH();				//SCL置高
	Delayxus(4);
	while((SDA_Read()==1)&&(i>255))
		i++;
	SCL_LOW();			//SCL置低
}
void IIC24C64_WriteByte(unsigned char dat)//写入一个字节的数据
{
	unsigned char i,temp,Even;
	SDA_OUT();				//设定为输出模式
	temp=dat;
	for(i=0;i<8;i++)
	{
		Even=temp&0x80;		
		temp=temp<<1;
		SCL_LOW();
		//Delayxus(4);
		if(Even==0x80)
		{
			SDA_HIGH();	//SDA置高
			//Delayxus(4);
		}
		else
		{
			SDA_LOW();	//SDA置低
			//Delayxus(4);			
		}
		SCL_HIGH();
		//Delayxus(4);
	}
	SCL_LOW();
	//Delayxus(4);
	SDA_HIGH();	//SDA置高
	//Delayxus(4);	
}

unsigned char IIC24C64_ReadByte(void)//读出一个字节的数据
{
	unsigned char temp1,i,Even;
	SCL_LOW();
	Delayxus(4);
	SDA_HIGH();	//SDA置高
	SDA_IN();//设置为输入
	for(i=0;i<8;i++)
	{
		SCL_HIGH();
		Delayxus(4);
		if(SDA_Read()==1)
		Even=1;
		else
		Even=0;
		temp1=(temp1<<1)|Even;
		SCL_LOW();
		//Delayxus(4);
	}
	//Delayxus(4);
	return temp1;
}
/*----------------------------------------------------------------------
** 功能：在特定的地址写入一个字节的数据  
** 参数： Addr:地址 0~8191 dat：要写入的数据 		   
** 返回值：无 	
-----------------------------------------------------------------------*/
void IIC24C64_WriteAddr(unsigned int Addr,unsigned char dat)
{
	IIC24C64_Start();//开始动作
	IIC24C64_WriteByte(0xa0);//写入器件地址1010 0000
	IIC24C64_Ack();//等待应答
	IIC24C64_WriteByte(Addr>>8);//写入页面地址 高8位
	IIC24C64_Ack();//等待应答
	IIC24C64_WriteByte(Addr%256);//写入页面地址 低8位
	IIC24C64_Ack();//等待应答
	IIC24C64_WriteByte(dat);//写入数据
	IIC24C64_Ack();//等待应答
	IIC24C64_Stop();//停止动作	
}
/*----------------------------------------------------------------------
** 功能：在特定的地址读取一个字节的数据  
** 参数： Addr:地址 0~4095 	   
** 返回值：读出的数据 	
-----------------------------------------------------------------------*/
unsigned char IIC24C64_ReadAddr(unsigned int Addr)
{
	unsigned char dat;
	IIC24C64_Start();//开始动作
	IIC24C64_WriteByte(0xa0);//写入器件地址1010 0000
	IIC24C64_Ack();//等待应答
	IIC24C64_WriteByte(Addr>>8);//写入页面地址 高8位
	IIC24C64_Ack();//等待应答
	IIC24C64_WriteByte(Addr%256);//写入页面地址 低8位
	IIC24C64_Ack();//等待应答
	IIC24C64_Start();//开始动作
	IIC24C64_WriteByte(0XA1);//写入读取命令
	IIC24C64_Ack();//等待应答
	dat=IIC24C64_ReadByte();//读出数据
	IIC24C64_Stop();//停止动作	
	return dat;
}
/*----------------------------------------------------------------------
** 功能：在特定的地址写入多个字节的数据  
** 参数： Addr:地址 0~8191 *dat：要写入的数据数值 len：要写入的字节个数		   
** 返回值：无 	
-----------------------------------------------------------------------*/
void IIC24C64_Write(unsigned int Addr,unsigned char *dat,unsigned char len)
{
	unsigned char i;
	for(i=0;i<len;i++)
	{
		IIC24C64_WriteAddr(Addr+i,*dat);
		dat++;
		Delayxus(2000);		
	}
}
/*----------------------------------------------------------------------
** 功能：在特定的地址写入多个字节的数据  
** 参数： Addr:地址 0~8191 *dat：要写入的数据数值 len：要写入的字节个数		   
** 返回值：无 	
-----------------------------------------------------------------------*/
void IIC24C64_Read(unsigned int Addr,unsigned char *dat,unsigned char len)
{
	unsigned char i;
	for(i=0;i<len;i++)
	{
		*dat=IIC24C64_ReadAddr(Addr+i);
		dat++;
	}
}
