#include "MPU6050.h"
#include "Delay.h"
#include "SPI_OLED.h"
#include "Sysclock.h"
/*
MPU_SDA=PA1;
MPU_SCL=PA2;
*/
#define MPU6050_SDA_APB_GPIO	RCC_APB2Periph_GPIOB
#define MPU_SDA_Pin        		GPIO_Pin_9
#define MPU_SDA_GPIO       		GPIOB

#define MPU6050_SCL_APB_GPIO	RCC_APB2Periph_GPIOB
#define MPU_SCL_Pin        		GPIO_Pin_8                                                                                                           
#define MPU_SCL_GPIO       		GPIOB


#define MPU_SDA_HIGH() 				GPIO_SetBits(MPU_SDA_GPIO,MPU_SDA_Pin)			//SDA置位
#define MPU_SDA_LOW() 				GPIO_ResetBits(MPU_SDA_GPIO,MPU_SDA_Pin)		//SDA清0
#define MPU_SCL_HIGH() 				GPIO_SetBits(MPU_SCL_GPIO,MPU_SCL_Pin)			//SCL置位
#define MPU_SCL_LOW() 				GPIO_ResetBits(MPU_SCL_GPIO,MPU_SCL_Pin)		//SCL清0


#define IIC_Delay() Delayxus(8)
void MPU6050_IOInit(void)											//初始化LED端口为推挽输出模式
{
	GPIO_InitTypeDef GPIO_InitStructure;							//定义GPIO结构体	
	RCC_APB2PeriphClockCmd(MPU6050_SDA_APB_GPIO,ENABLE);				//开启MPU_GPIO模块的时钟
	RCC_APB2PeriphClockCmd(MPU6050_SCL_APB_GPIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=MPU_SDA_Pin;						//配置MPU_SDA端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;					//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;					//配置端口模式为推挽输出模式
	GPIO_Init(MPU_SDA_GPIO,&GPIO_InitStructure);					//对端口进行初始化	
	
	GPIO_InitStructure.GPIO_Pin=MPU_SCL_Pin;						//配置MPU_SCL端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;					//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;					//配置端口模式为推挽输出模式
	GPIO_Init(MPU_SCL_GPIO,&GPIO_InitStructure);					//对端口进行初始化	

}

void MPU_SDA_OUT(void)//设置引脚的模式为输出
{
	GPIO_InitTypeDef GPIO_InitStructure;								//定义GPIO结构体	
	GPIO_InitStructure.GPIO_Pin=MPU_SDA_Pin;							//配置SDA端口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;						//配置端口的速度	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;						//配置端口模式为推挽输出模式
	GPIO_Init(MPU_SDA_GPIO,&GPIO_InitStructure);							//对端口进行初始化	
}
void MPU_SDA_IN(void)//设置引脚的模式为输入
{
	GPIO_InitTypeDef GPIO_InitStructure;						//定义GPIO结构体	
	GPIO_InitStructure.GPIO_Pin=MPU_SDA_Pin;						//配置SDA端口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;;					//配置端口模式为上拉输出模式
	GPIO_Init(MPU_SDA_GPIO,&GPIO_InitStructure);					//对端口进行初始化	
}
unsigned char MPU_SDA_Read(void)//读取SDA引脚的状态
{
	return GPIO_ReadInputDataBit(MPU_SDA_GPIO,MPU_SDA_Pin);
}

void MPU6050_IIC_Start(void)//开始动作
{
	MPU_SDA_OUT();	//设定为输出模式
	MPU_SDA_HIGH();	//SDA置高
	MPU_SCL_HIGH();	//SCL置高
	IIC_Delay();
	MPU_SDA_LOW();	//SDA置低
	IIC_Delay();
	MPU_SCL_LOW();	//SCL置低	
}

void MPU6050_IIC_Stop(void)//停止动作
{
	MPU_SDA_OUT();	//设定为输出模式
	MPU_SCL_LOW();	//SCL置低
	MPU_SDA_LOW();	//SDA置低
	IIC_Delay();
	MPU_SCL_HIGH();	//SDA置低
	MPU_SDA_HIGH();	//SDA置高
	
}
unsigned char MPU6050_IIC_Wait_Ack(void)//等待应答信号
{
	unsigned char i=0;
	MPU_SDA_IN();				//设定为输入模式
	MPU_SCL_HIGH();			//SCL置高
	IIC_Delay();
	while(MPU_SDA_Read())
	{
		i++;
		if(i>250)
		{
			MPU6050_IIC_Stop();
			return 1;
		}
	}
	MPU_SCL_LOW();			//SCL置低
	return 0;
}
void MPU6050_IIC_Ack(void)//产生应答信号 MPU_SCL_HIGH() MPU_SCL_LOW(); MPU_SDA_HIGH()
{
	MPU_SCL_LOW();
	MPU_SDA_OUT();
	MPU_SDA_LOW();
	MPU_SCL_HIGH();
	MPU_SCL_LOW();
}
//不产生应答信号	    
void MPU6050_IIC_NAck(void)
{
	MPU_SCL_LOW();
	MPU_SDA_OUT();
	MPU_SDA_HIGH();
	MPU_SCL_HIGH();
	MPU_SCL_LOW();
}
void MPU6050_IIC_WriteByte(unsigned char dat)//写入一个字节的数据
{
	unsigned char i,temp,Even;
	MPU_SDA_OUT();				//设定为输出模式
	temp=dat;
	for(i=0;i<8;i++)
	{
		Even=temp&0x80;		
		temp=temp<<1;
		MPU_SCL_LOW();
		IIC_Delay();
		if(Even==0x80)
		{
			MPU_SDA_HIGH();	//SDA置高
			IIC_Delay();
		}
		else
		{
			MPU_SDA_LOW();	//SDA置低
			//IIC_Delay();			
		}
		MPU_SCL_HIGH();
		IIC_Delay();
	}
	MPU_SCL_LOW();
	IIC_Delay();
	MPU_SDA_HIGH();	//SDA置高
	IIC_Delay();	
}

unsigned char MPU6050_IIC_ReadByte(unsigned char ACK)//读出一个字节的数据
{
	unsigned char temp,i,Even;
	MPU_SCL_LOW();
	IIC_Delay();
	MPU_SDA_HIGH();	//SDA置高
	MPU_SDA_IN();//设置为输入
	for(i=0;i<8;i++)
	{
		MPU_SCL_HIGH();
		IIC_Delay();
		if(MPU_SDA_Read()==1)
		Even=1;
		else
		Even=0;
		temp=(temp<<1)|Even;
		MPU_SCL_LOW();
		IIC_Delay();
	}
	IIC_Delay();
	if(ACK)
	MPU6050_IIC_Ack();
	else
	MPU6050_IIC_NAck();	
	return temp;
}
/*----------------------------------------------------------------------
*名    称:unsigned char MPU6050_WriteAddr(unsigned char Addr,unsigned char dat)
*功    能:在特定的地址写入一个字节的数据
*入口参数:Addr:地址  dat：要写入的数据
*出口参数:0: 正常写入 1：异常
*说    明:	
*调用方法:无
----------------------------------------------------------------------*/
unsigned char MPU6050_WriteAddr(unsigned char Addr,unsigned char dat)
{
	MPU6050_IIC_Start();					//开始动作
	MPU6050_IIC_WriteByte((MPU_ADDR<<1)|0);	//写入器件地址 和写命令
	if(MPU6050_IIC_Wait_Ack())				//等待应答
	{
		MPU6050_IIC_Stop();	
		return 1;		
	}
	MPU6050_IIC_WriteByte(Addr);			//写入地址
	MPU6050_IIC_Wait_Ack();						//等待应答
	MPU6050_IIC_WriteByte(dat);				//写入数据
	if(MPU6050_IIC_Wait_Ack())				//等待应答
	{
		MPU6050_IIC_Stop();	
		return 1;	 	
	}
	MPU6050_IIC_Stop();						//停止动作	
	return 0;
}
/*----------------------------------------------------------------------
*名    称:unsigned char MPU6050_ReadAddr(unsigned char Addr)
*功    能:在特定的地址读取一个字节的数据
*入口参数:Addr:地址  
*出口参数:读出的数据
*说    明:	
*调用方法:无
----------------------------------------------------------------------*/
unsigned char MPU6050_ReadAddr(unsigned char Addr)
{
	unsigned char dat;
	MPU6050_IIC_Start();					//开始动作
	MPU6050_IIC_WriteByte((MPU_ADDR<<1)|0);	//发送器件地址+写命令	
	MPU6050_IIC_Wait_Ack();					//等待应答
	MPU6050_IIC_WriteByte(Addr);			//写入页面地址 
	MPU6050_IIC_Wait_Ack();					//等待应答
	MPU6050_IIC_Start();					//开始动作
	MPU6050_IIC_WriteByte((MPU_ADDR<<1)|1);	//发送器件地址+读命令	
	MPU6050_IIC_Wait_Ack();					//等待应答
	dat=MPU6050_IIC_ReadByte(0);			//读取数据,发送nACK 
	MPU6050_IIC_Stop();						//停止动作	
	return dat;
}
/*----------------------------------------------------------------------
*名    称:void MPU6050_WriteData(unsigned char Addr,unsigned char dat,unsigned char *buff)
*功    能:在特定的地址写入多个字节的数据
*入口参数:Addr:地址  num：要写入的数据 *buff：要写入的数据数组
*出口参数:0:正常写入 1：异常
*说    明:	
*调用方法:无
----------------------------------------------------------------------*/
unsigned char MPU6050_WriteData(unsigned char MPU_AD,unsigned char Addr,unsigned char num,unsigned char *buff)
{
	unsigned char i;
	MPU6050_IIC_Start();					//开始动作
	MPU6050_IIC_WriteByte((MPU_AD<<1)|0);	//写入器件地址 和写命令
	if(MPU6050_IIC_Wait_Ack())				//等待应答
	{
		MPU6050_IIC_Stop();
		return 1;		
	}
	MPU6050_IIC_WriteByte(Addr);			//写入地址
	MPU6050_IIC_Wait_Ack();						//等待应答
	for(i=0;i<num;i++)
	{
		MPU6050_IIC_WriteByte(buff[i]);		//写入数据
		if(MPU6050_IIC_Wait_Ack())				//等待应答
		{
			MPU6050_IIC_Stop();	
			return 1;			
		}
	}
	MPU6050_IIC_Stop();						//停止动作	
	return 0;
}
/*----------------------------------------------------------------------
*名    称:unsigned char MPU6050_ReadData(unsigned char Addr,unsigned char num,unsigned char *buff)
*功    能:在特定的地址读出多个字节的数据
*入口参数:Addr:地址  num：要读出的数据个数 *buff：要读出数据到数据数组
*出口参数:0:正常读出 1：异常
*说    明:	
*调用方法:无
----------------------------------------------------------------------*/
unsigned char MPU6050_ReadData(unsigned char MPU_AD,unsigned char Addr,unsigned char num,unsigned char *buff)
{
	MPU6050_IIC_Start();					//开始动作
	MPU6050_IIC_WriteByte((MPU_AD<<1)|0);	//写入器件地址 和写命令
	if(MPU6050_IIC_Wait_Ack())				//等待应答
	{
		MPU6050_IIC_Stop();
		return 1;		
	}
	MPU6050_IIC_WriteByte(Addr);			//写入地址
	MPU6050_IIC_Wait_Ack();						//等待应答
	MPU6050_IIC_Start();					//开始动作
	MPU6050_IIC_WriteByte((MPU_AD<<1)|1);//发送器件地址+读命令
	MPU6050_IIC_Wait_Ack();						//等待应答
	while(num)
	{
		if(num==1) *buff=MPU6050_IIC_ReadByte(0);
		else *buff=MPU6050_IIC_ReadByte(1);
		num--;
		buff++;
	}
	MPU6050_IIC_Stop();						//停止动作	
	return 0;
}
/*----------------------------------------------------------------------
*名    称:void MPU6050_SetGyroFsr(unsigned char fsr)
*功    能:设置MPU6050陀螺仪传感器满量程范围
*入口参数:fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
*出口参数:无 
*说    明:	
*调用方法:无
----------------------------------------------------------------------*/
void MPU6050_SetGyroFsr(unsigned char fsr)
{
	 MPU6050_WriteAddr(MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
}

/*----------------------------------------------------------------------
*名    称:void MPU6050_SetAccelFsr(unsigned char fsr)
*功    能:设置MPU6050加速度传感器满量程范围
*入口参数:fsr:0,±2g;1,±4g;2,±8g;3,±16g
*出口参数:无 
*说    明:	
*调用方法:无
----------------------------------------------------------------------*/
void MPU6050_SetAccelFsr(unsigned char fsr)
{
	 MPU6050_WriteAddr(MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
}
/*----------------------------------------------------------------------
*名    称:unsigned char MPU6050_SetLPF(unsigned char lpf)
*功    能:设置MPU6050的数字低通滤波器
*入口参数:fsr:0,±2g;1,±4g;2,±8g;3,±16g
*出口参数:0,设置成功   其他,设置失败 
*说    明:	
*调用方法:无
----------------------------------------------------------------------*/
unsigned char MPU6050_SetLPF(unsigned char lpf)
{
	unsigned char data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU6050_WriteAddr(MPU_CFG_REG,data);//设置数字低通滤波器  
}
/*----------------------------------------------------------------------
*名    称:unsigned char MPU6050_SetRate(unsigned int rate)
*功    能:设置MPU6050的采样率(假定陀螺仪的输出频率Fs=1KHz)
*入口参数:rate:4~1000(Hz)
*出口参数:0,设置成功   其他,设置失败 
*说    明:	
*调用方法:无
----------------------------------------------------------------------*/
unsigned char MPU6050_SetRate(unsigned int rate)
{
	unsigned char data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	MPU6050_WriteAddr(MPU_SAMPLE_RATE_REG,data);	//设置MPU6050的采样率
 	return MPU6050_SetLPF(rate/2);					//自动设置数字低通滤波器LPF为采样率的一半
}
/*----------------------------------------------------------------------
*名    称:short MPU6050_GetTemperature(void)
*功    能:得到温度值
*入口参数:无
*出口参数:返回值:温度值(扩大了100倍)
*说    明:	
*调用方法:无
----------------------------------------------------------------------*/
short MPU6050_GetTemperature(void)
{
    unsigned char buf[2]; 
    short raw;
	float temp;
	MPU6050_ReadData(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;
}
/*----------------------------------------------------------------------
*名    称:unsigned char MPU6050_GetGyroscope(short *gx,short *gy,short *gz)
*功    能:得到陀螺仪值(原始值)
*入口参数:gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
*出口参数:0,成功  其他,错误代码
*说    明:	
*调用方法:无
----------------------------------------------------------------------*/
unsigned char MPU6050_GetGyroscope(short *gx,short *gy,short *gz)
{
    unsigned char buf[6],res;  
	res=MPU6050_ReadData(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
/*----------------------------------------------------------------------
*名    称:unsigned char MPU6050_GetAccelerometer(short *ax,short *ay,short *az)
*功    能:得到加速度值(原始值)
*入口参数:gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
*出口参数:0,成功  其他,错误代码
*说    明:	
*调用方法:无
----------------------------------------------------------------------*/
unsigned char MPU6050_GetAccelerometer(short *ax,short *ay,short *az)
{
    unsigned char buf[6],res;  
	res=MPU6050_ReadData(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}





unsigned char MPU6050_Init(void)
{
	unsigned char res;
	MPU6050_IOInit();//IO初始化
	MPU6050_WriteAddr(MPU_PWR_MGMT1_REG,0X80);	//复位MPU6050
	MPU6050_WriteAddr(MPU_PWR_MGMT1_REG,0X00);	//唤醒MPU6050
	MPU6050_SetGyroFsr(3);						//陀螺仪传感器,±2000dps
	MPU6050_SetAccelFsr(0);						//加速度传感器,±2g
	MPU6050_SetRate(50);						//设置采样率50Hz
	MPU6050_WriteAddr(MPU_INT_EN_REG,0X00);		//关闭所有中断
	MPU6050_WriteAddr(MPU_USER_CTRL_REG,0X00);	//I2C主模式关闭
	MPU6050_WriteAddr(MPU_FIFO_EN_REG,0X00);	//关闭FIFO
	MPU6050_WriteAddr(MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
	res=MPU6050_ReadAddr(MPU_DEVICE_ID_REG);	//读取器件的ID
//	OLED12864_Format2(0,0,0,res);
	
	if(res==MPU_ADDR)//器件ID正确
	{
		MPU6050_WriteAddr(MPU_PWR_MGMT1_REG,0X01);	//设置CLKSEL,PLL X轴为参考
		MPU6050_WriteAddr(MPU_PWR_MGMT2_REG,0X00);	//加速度与陀螺仪都工作
		MPU6050_SetRate(50);						//设置采样率为50Hz
 	}
	else return 1;
	return 0;
}










