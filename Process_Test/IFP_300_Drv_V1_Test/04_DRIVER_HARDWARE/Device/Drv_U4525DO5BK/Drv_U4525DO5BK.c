/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——U4525DO5BK压力检测模块

  -------------------------------------------------------
   文 件 名   : Drv_U4525DO5BK.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2020年04月22日
   功能描述   : 定义U4525DO5BK压力检测模块的驱动。
   使用方法   ：
   依赖于     : 
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/

#include "Drv_U4525DO5BK.h"

DRV_U4525DO5BK_TYPE* _gp_U4525DO5BKUnits[U4525DO5BK_BUTT] = {0};	/*压力检测模块的注册表*/

/* 接口函数
 ********************************************************/

/* 初始化U4525DO5BK模块
  -----------------------------
  入口：U4525DO5BK模块的ID号，IO端口
  返回值：初始化好的U4525DO5BK模块结构体
*/
DRV_U4525DO5BK_TYPE* Drv_U4525DO5BKInit(DRV_U4525DO5BK_ENUM id, \
												uint8_t addr, \
												uint8_t range, \
												BSP_PORT_ENUM sda_port_number, BSP_PIN_ENUM sda_pin_number, \
												BSP_PORT_ENUM scl_port_number, BSP_PIN_ENUM scl_pin_number, \
												BSP_PORT_ENUM int_port_number, BSP_PIN_ENUM int_pin_number)
{	
	DRV_U4525DO5BK_TYPE* p_unit = (DRV_U4525DO5BK_TYPE*)calloc(1, sizeof(DRV_U4525DO5BK_TYPE));	/*申请内存*/

	/*分配失败返回NULL*/
	if(p_unit == NULL)
	{
		return NULL;
	}
		
	/*id错误返回NULL*/
	if(id >= U4525DO5BK_BUTT)
	{
		free(p_unit); 
		return NULL;
	}
	
	/*如果当前模块存在，取消分配新存储区*/
	if(_gp_U4525DO5BKUnits[id] != NULL)
	{
		free(p_unit);
		p_unit = _gp_U4525DO5BKUnits[id];
	}
	else
	{
		_gp_U4525DO5BKUnits[id] = p_unit;
	}
	
	/*初始化*/
	
	/*-------------------------------常量*/
	p_unit->id          	= id;						/*模块id*/
	p_unit->addr   			= addr;						/*时钟速度参数*/
	p_unit->range			= range;					/*量程*/
	p_unit->iic_port		= SimulateIicInit((DRV_SIMULATE_IIC_ENUM)id, 2, sda_port_number, sda_pin_number, scl_port_number, scl_pin_number);		/*IIC端口*/
	p_unit->int_port_number = int_port_number;			/*引脚端口号*/
	p_unit->int_pin_number  = int_pin_number;			/*引脚序号*/
	BSP_Init_Pin(scl_port_number, scl_pin_number, _IN_FLOATING_);	/*初始化硬件*/
	
	/*-------------------------------变量*/
	p_unit->status = U4525DO5BK_STANDBY;
	p_unit->pressure = 0;								/*压力值*/
	
	return p_unit;
}

/*
  启动测量
  ----------------------------
*/
void Drv_U4525DO5BKReadMr(DRV_U4525DO5BK_TYPE* p_unit) 
{
	Drv_SimulateIicStart(p_unit->iic_port);
	Drv_SimulateIicSendByte(p_unit->iic_port, (p_unit->addr << 1) | U4525DO5BK_READ);
	if(Drv_SimulateIicWaitAck(p_unit->iic_port) == false)
	{
		Drv_SimulateIicStop(p_unit->iic_port);
		return;
	}
	Drv_SimulateIicStop(p_unit->iic_port);
}

/*
  读压力值
  ----------------------------
*/
Data_Fetch_2 Drv_U4525DO5BKReadDF2(DRV_U4525DO5BK_TYPE* p_unit) 
{
	Data_Fetch_2 data = {0};
	
	Drv_SimulateIicStart(p_unit->iic_port);
	Drv_SimulateIicSendByte(p_unit->iic_port, (p_unit->addr << 1) | U4525DO5BK_READ);
	if(Drv_SimulateIicWaitAck(p_unit->iic_port) == false)
	{
		Drv_SimulateIicStop(p_unit->iic_port);
		return data;
	}
	data.pressure = Drv_SimulateIicReadByte(p_unit->iic_port);
	data.pressure <<= 8;
	Drv_SimulateIicAck(p_unit->iic_port);
	data.pressure |= Drv_SimulateIicReadByte(p_unit->iic_port);
	Drv_SimulateIicNack(p_unit->iic_port);
	Drv_SimulateIicStop(p_unit->iic_port);
	
	return data;
}

/*
  读压力值和8位温度值
  ----------------------------
*/
Data_Fetch_3 Drv_U4525DO5BKReadDF3(DRV_U4525DO5BK_TYPE* p_unit)
{
	Data_Fetch_3 data = {0};
	
	Drv_SimulateIicStart(p_unit->iic_port);
	Drv_SimulateIicSendByte(p_unit->iic_port, (p_unit->addr << 1) | U4525DO5BK_READ);
	if(Drv_SimulateIicWaitAck(p_unit->iic_port) == false)
	{
		Drv_SimulateIicStop(p_unit->iic_port);
		return data;
	}
	data.pressure = Drv_SimulateIicReadByte(p_unit->iic_port);
	data.pressure <<= 8;
	Drv_SimulateIicAck(p_unit->iic_port);
	data.pressure |= Drv_SimulateIicReadByte(p_unit->iic_port);
	Drv_SimulateIicAck(p_unit->iic_port);
	data.temperature = Drv_SimulateIicReadByte(p_unit->iic_port);
	Drv_SimulateIicNack(p_unit->iic_port);
	Drv_SimulateIicStop(p_unit->iic_port);
	
	return data;
}

/*
  读压力值和11位温度值
  ----------------------------
*/
Data_Fetch_4 Drv_U4525DO5BKReadDF4(DRV_U4525DO5BK_TYPE* p_unit) 
{
	Data_Fetch_4 data = {0};
	
	Drv_SimulateIicStart(p_unit->iic_port);
	Drv_SimulateIicSendByte(p_unit->iic_port, (p_unit->addr << 1) | U4525DO5BK_READ);
	if(Drv_SimulateIicWaitAck(p_unit->iic_port) == false)
	{
		Drv_SimulateIicStop(p_unit->iic_port);
		return data;
	}
	data.pressure = Drv_SimulateIicReadByte(p_unit->iic_port);
	data.pressure <<= 8;
	Drv_SimulateIicAck(p_unit->iic_port);
	data.pressure |= Drv_SimulateIicReadByte(p_unit->iic_port);
	Drv_SimulateIicAck(p_unit->iic_port);
	data.temperature = Drv_SimulateIicReadByte(p_unit->iic_port);
	data.temperature <<= 8;
	Drv_SimulateIicAck(p_unit->iic_port);
	data.temperature |= Drv_SimulateIicReadByte(p_unit->iic_port);
	data.temperature >>= 5;
	Drv_SimulateIicNack(p_unit->iic_port);
	Drv_SimulateIicStop(p_unit->iic_port);
	
	return data;
}

/*
  读转换状态
  ----------------------------
*/
bool Drv_U4525DO5BKGetState(DRV_U4525DO5BK_TYPE* p_unit)
{
	bool state = 0;
	
	state = BSP_ReadPin(p_unit->int_port_number, p_unit->int_pin_number);
	
	return state;
}
