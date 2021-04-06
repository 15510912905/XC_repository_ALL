/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——ADS1210U 24位模数转换模块

  -------------------------------------------------------
   文 件 名   : Drv_ADS1210U.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2020年2月14日
   功能描述   : 定义ADS1210U模数转换器的驱动。
   使用方法   ：上层模块通过调用Ads1210uInit获得一个ADS1210U
				的指针。
   依赖于     : BSP_Spi V1.0.0.0
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/

#include "Drv_ADS1210U.h"

DRV_ADS1210U_TYPE* _gp_Ads1210uUnits[ADS1210U_BUTT] = {0};	/*ADS1210U模数转换模块的注册表*/

/* 接口函数
 ********************************************************/

/* 初始化ADS1210U模块
  -----------------------------
  入口：ADS1210U模块的ID号，SPI端口编号，引脚端口号
  返回值：初始化好的ADS1210U模块结构体
*/
DRV_ADS1210U_TYPE* Drv_Ads1210uInit(DRV_ADS1210U_ENUM id, \
										BSP_PORT_ENUM sclk_port_number, BSP_PIN_ENUM sclk_pin_number, \
										BSP_PORT_ENUM sdout_port_number, BSP_PIN_ENUM sdout_pin_number, \
										BSP_PORT_ENUM sdio_port_number, BSP_PIN_ENUM sdio_pin_number, \
										BSP_PORT_ENUM drdy_port_number, BSP_PIN_ENUM drdy_pin_number)
{	
	DRV_ADS1210U_TYPE* p_unit = (DRV_ADS1210U_TYPE*)calloc(1, sizeof(DRV_ADS1210U_TYPE));	/*申请内存*/

	/*分配失败返回NULL*/
	if(p_unit == NULL)
	{
		return NULL;
	}
		
	/*id错误返回NULL*/
	if(id >= ADS1210U_BUTT)
	{
		free(p_unit); 
		return NULL;
	}
	
	/*如果当前模块存在，取消分配新存储区*/
	if(_gp_Ads1210uUnits[id] != NULL)
	{
		free(p_unit);
		p_unit = _gp_Ads1210uUnits[id];
	}
	else
	{
		_gp_Ads1210uUnits[id] = p_unit;
	}
	
	/*初始化*/
	
	/*-------------------------------常量*/
	p_unit->id         = id;				/*模块id*/
	p_unit->spi_port   = SoftwareSpiInit((DRV_SOFTWARE_SPI_ENUM)id, 1, \
										sdout_port_number, sdout_pin_number, \
										sdio_port_number, sdio_pin_number, \
										sclk_port_number, sclk_pin_number, \
										_PORT_BUTT_, _PIN_BUTT_);
	p_unit->drdy_port_number = drdy_port_number;
	p_unit->drdy_pin_number = drdy_pin_number;
	BSP_Init_Pin(drdy_port_number, drdy_pin_number, _IN_IPU_);		/*初始化硬件*/

	/*-------------------------------变量*/
	p_unit->status     = ADS1210U_READY;
	p_unit->rx_buffer  = 0;
	p_unit->drdy_buffer  = 0;
		
	return p_unit;
}

/* ADS1210U启动
  -----------------------------
  入口：ADS1210U模块结构体指针
  返回值：true 成功，false 失败
*/
bool Ads1210uStart(DRV_ADS1210U_TYPE* p_unit)
{
	p_unit->spi_port->sck_pin_buffer = 0;
	BSP_WritePin(p_unit->spi_port->sck_port_number, p_unit->spi_port->sck_pin_number, p_unit->spi_port->sck_pin_buffer);
	p_unit->spi_port->sck_pin_buffer = 1;
	BSP_WritePin(p_unit->spi_port->sck_port_number, p_unit->spi_port->sck_pin_number, p_unit->spi_port->sck_pin_buffer);
	_SoftwareSpiDelayUs(p_unit->spi_port, 80);		/*延时25.6~40us*/
	p_unit->spi_port->sck_pin_buffer = 0;
	BSP_WritePin(p_unit->spi_port->sck_port_number, p_unit->spi_port->sck_pin_number, p_unit->spi_port->sck_pin_buffer);
	_SoftwareSpiDelayUs(p_unit->spi_port, 1);		/*延时>0.5us*/
	p_unit->spi_port->sck_pin_buffer = 1;
	BSP_WritePin(p_unit->spi_port->sck_port_number, p_unit->spi_port->sck_pin_number, p_unit->spi_port->sck_pin_buffer);
	_SoftwareSpiDelayUs(p_unit->spi_port, 160);		/*延时51.2~90us*/
	p_unit->spi_port->sck_pin_buffer = 0;
	BSP_WritePin(p_unit->spi_port->sck_port_number, p_unit->spi_port->sck_pin_number, p_unit->spi_port->sck_pin_buffer);
	_SoftwareSpiDelayUs(p_unit->spi_port, 1);		/*延时>0.5us*/
	p_unit->spi_port->sck_pin_buffer = 1;
	BSP_WritePin(p_unit->spi_port->sck_port_number, p_unit->spi_port->sck_pin_number, p_unit->spi_port->sck_pin_buffer);
	_SoftwareSpiDelayUs(p_unit->spi_port, 250);		/*延时102.4~120us*/
	p_unit->spi_port->sck_pin_buffer = 0;
	BSP_WritePin(p_unit->spi_port->sck_port_number, p_unit->spi_port->sck_pin_number, p_unit->spi_port->sck_pin_buffer);
	
	_Ads1210uWait(p_unit);
	SoftwareSpiWriteByte(p_unit->spi_port, 0x64);		/*写入INSR命令,RW=0 写，MB=11 4Byte，A=0100 控制寄存器*/
	_SoftwareSpiDelayUs(p_unit->spi_port, 2);			/*延时2us*/
	SoftwareSpiWriteByte(p_unit->spi_port, 0x72);		/*写CMR命令，BIAS=0 Vbias引脚输出状态,REFO=1 REFout引脚输出状态,DF=1 二进制补码偏移,UB=1 输出范围限制,MSByte=0 高字节在前,MSB=0 高位在前,SDL=1 SDOUT为数据输出,DRDY只读*/
	SoftwareSpiWriteByte(p_unit->spi_port, 0x20);		/*MD=001 自校准模式，G=001 GAIN=1，CH=0 通道1*/
	SoftwareSpiWriteByte(p_unit->spi_port, 0x9F);		/*SF=100 TMR=16，DR=1 0011 1000 0111 抽取率4999*/
	SoftwareSpiWriteByte(p_unit->spi_port, 0xFF);		/*数据输出率38.15HZ，抽取率8191*/
	_SoftwareSpiDelayUs(p_unit->spi_port, 2);			/*延时2us*/
	
	return true;
}

/* ADS1210U模块完成一次采样
  -----------------------------
  入口：ADS1210U模块结构体指针
  返回值：读到的值
*/
uint32_t Ads1210uOneAcq(DRV_ADS1210U_TYPE* p_unit)
{    
//    if(Ads1210uStart(p_unit) == false)
//		return 0;
    if(_Ads1210uWait(p_unit) == false)
		return 0;
    p_unit->rx_buffer = _Ads1210uReadData(p_unit) ;
	
    return p_unit->rx_buffer;
}

/* 内部函数
 ********************************************************/

/* ADS1210U等待转换
  -----------------------------
  入口：ADS1210U模块结构体指针
  返回值：true 成功，false 失败
*/
static bool _Ads1210uWait(DRV_ADS1210U_TYPE* p_unit)
{
	while(1)
	{
		p_unit->drdy_buffer = BSP_ReadPin(p_unit->drdy_port_number, p_unit->drdy_pin_number);	/*读取DRDY引脚状态*/
		if(p_unit->drdy_buffer == 1)	/*高电平表示开始转换*/
		{
			break;
		}
	}
	while(1)
	{
		p_unit->drdy_buffer = BSP_ReadPin(p_unit->drdy_port_number, p_unit->drdy_pin_number);	/*读取DRDY引脚状态*/
		if(p_unit->drdy_buffer == 0)	/*低电平表示转换完成*/
		{
			break;
		}
	}
	_Ads1210uDelayUs(p_unit, 1);
	
	return true;
} 

/* ADS1210U模块延时n微秒
  -----------------------------
  入口：ADS1210U模块结构体指针、延时时间
  返回值：true 成功，false 失败
*/
static bool _Ads1210uDelayUs(DRV_ADS1210U_TYPE* p_unit, uint32_t time)
{    
   return _SoftwareSpiDelayUs(p_unit->spi_port, time);
}

/* ADS1210U模块读取AD值
  -----------------------------
  入口：ADS1210U模块结构体指针
  返回值：true 成功，false 失败
*/
static uint32_t _Ads1210uReadData(DRV_ADS1210U_TYPE* p_unit)
{
	uint32_t data_out = 0;
	
	SoftwareSpiWriteByte(p_unit->spi_port, 0xC0);		/*发送读取命令*/
	_SoftwareSpiDelayUs(p_unit->spi_port, 1);			/*延时2us*/
	data_out = SoftwareSpiReadByte(p_unit->spi_port);					/*读取高字节*/
	data_out = (data_out << 8) | SoftwareSpiReadByte(p_unit->spi_port);	/*读取中字节*/
	data_out = (data_out << 8) | SoftwareSpiReadByte(p_unit->spi_port);	/*读取低字节*/
	_SoftwareSpiDelayUs(p_unit->spi_port, 2);			/*延时2us*/
	
	return data_out;
}
