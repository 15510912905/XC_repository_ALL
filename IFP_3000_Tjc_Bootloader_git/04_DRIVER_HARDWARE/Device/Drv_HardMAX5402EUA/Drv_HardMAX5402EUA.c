/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——MAX5402EUA数字电位器模块

  -------------------------------------------------------
   文 件 名   : Drv_MAX5402EUA.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2019年10月14日
   功能描述   : 定义MAX5402EUA数字电位器的驱动。
   使用方法   ：上层模块通过调用MAX5402EUA_Init获得一个MAX5402EUA
				的指针，通过调用MAX5402EUASet设置增益值。
   依赖于     : Drv_Software_Spi V1.0.0.0
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/

#include "Drv_HardMAX5402EUA.h"

DRV_MAX5402EUA_HARD_TYPE* _gp_Max5402euaHardUnits[MAX5402EUA_BUTT] = {0};	/*MAX5402EUA数字电位器模块的注册表*/

/* 接口函数
 ********************************************************/

/* 初始化MAX5402EUA模块 软件SPI
  -----------------------------
  入口：MAX5402EUA模块的ID号，电阻值
  返回值：初始化好的MAX5402EUA模块结构体
*/
DRV_MAX5402EUA_HARD_TYPE* Max5402euaHardInit(DRV_MAX5402EUA_HARD_ENUM id, \
									         uint8_t gain, BSP_SPI_ENUM spi_number,uint32_t theta, \
									         BSP_PORT_ENUM miso_port_number, BSP_PIN_ENUM miso_pin_number, \
									         BSP_PORT_ENUM mosi_port_number, BSP_PIN_ENUM mosi_pin_number, \
									         BSP_PORT_ENUM sck_port_number, BSP_PIN_ENUM sck_pin_number, \
									         BSP_PORT_ENUM nss_port_number, BSP_PIN_ENUM nss_pin_number)
{	
	DRV_MAX5402EUA_HARD_TYPE* p_unit = (DRV_MAX5402EUA_HARD_TYPE*)calloc(1, sizeof(DRV_MAX5402EUA_HARD_TYPE));	/*申请内存*/

	/*分配失败返回NULL*/
	if(p_unit == NULL)
	{
		return NULL;
	}
		
	/*id错误返回NULL*/
	if(id >= SOFTWARE_SPI_BUTT)
	{
		free(p_unit); 
		return NULL;
	}
	
	/*如果当前模块存在，取消分配新存储区*/
	if(_gp_Max5402euaHardUnits[id] != NULL)
	{
		free(p_unit);
		p_unit = _gp_Max5402euaHardUnits[id];
	}
	else
	{
		_gp_Max5402euaHardUnits[id] = p_unit;
	}
	
	/*初始化*/
	
	/*-------------------------------常量*/
	p_unit->id              = id;						/*模块id*/
	p_unit->hardspi         = spi_number;
	p_unit->nss_port_number = nss_port_number;
	p_unit->nss_pin_number  = nss_pin_number;
	p_unit->theta           = theta;
	BSP_InitSpiMaster8Bit( spi_number, \
				           nss_port_number, nss_pin_number, \
				           sck_port_number, sck_pin_number, \
				           miso_port_number, miso_pin_number, \
				           mosi_port_number, mosi_pin_number );
	
	/*-------------------------------变量*/
	p_unit->status = MAX5402EUA_HARD_READY;
	if(gain < 10)
		gain = 10;
	p_unit->gain = gain;
	
	Max5402euaHardSet( p_unit,p_unit->gain );
	
	return p_unit;
}

/* 设置MAX5402EUA阻值
  -----------------------------
  入口：MAX5402EUA模块的ID号，电阻档数
  返回值：true 成功，false 失败
*/
bool Max5402euaHardSet(DRV_MAX5402EUA_HARD_TYPE* p_unit, uint8_t gain)
{
	if(gain < 10)
		gain = 10;		
	p_unit->gain = gain;
	
	_Max5402euaHardStart( p_unit );
	
	BSP_SpiSendData( p_unit->hardspi ,gain );
	
	_Max5402euaHardEnd( p_unit );
	return true;
}

/* 内部函数
 ********************************************************/

/* Max5402eua启动
  -----------------------------
  入口：Max5402eua模块结构体指针
  返回值：true 成功，false 失败
*/
static bool _Max5402euaHardStart(DRV_MAX5402EUA_HARD_TYPE* p_unit)
{
	BSP_SpiNssSet(p_unit->nss_port_number, p_unit->nss_pin_number, NSS_LOW);	/*CS拉低*/ 
	_Max5402euaHardDelayUs(p_unit, 1);
	
	return true;
}

/* Max5402eua结束
  -----------------------------
  入口：Max5402eua模块结构体指针
  返回值：true 成功，false 失败
*/
static bool _Max5402euaHardEnd(DRV_MAX5402EUA_HARD_TYPE* p_unit)
{
	BSP_SpiNssSet(p_unit->nss_port_number, p_unit->nss_pin_number, NSS_HIGH);	/*CS拉高*/ 
	_Max5402euaHardDelayUs(p_unit, 1);
	
	return true;
}

/*  Max5402eua模块延时n微秒
  -----------------------------
  入口：延时时间
  返回值：true 成功，false 失败
*/
static bool _Max5402euaHardDelayUs(DRV_MAX5402EUA_HARD_TYPE* p_unit, uint32_t time)
{    
   unsigned short i = 0; 
   
   while(time--)
   {
      i = p_unit->theta;
      while(i--);    
   }
   
   return true;
}

///* Max5402eua等待转换
//  -----------------------------
//  入口：Max5402eua模块结构体指针
//  返回值：true 成功，false 失败
//*/
//static bool _Max5402euaHardWait(DRV_MAX5402EUA_HARD_TYPE* p_unit)
//{
//	_Max5402euaHardDelayUs(p_unit, 5);	/*等待5us*/
//	return true;
//} 
