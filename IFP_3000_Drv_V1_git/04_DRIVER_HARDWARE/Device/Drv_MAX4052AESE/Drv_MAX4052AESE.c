/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——MAX4052AESE多路开关模块

  -------------------------------------------------------
   文 件 名   : Drv_MAX4052AESE.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2020年2月14日
   功能描述   : 定义MAX4052AESE多路开关的驱动。
   使用方法   ：上层模块通过调用Max4052aeseInit获得一个Max4052aese
				的指针，通过调用Max4052aeseSet设置选通哪一路。
   依赖于     : BSP_Gpio V1.0.0.0
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/

#include "Drv_MAX4052AESE.h"

DRV_MAX4052AESE_TYPE* _gp_Max4052aeseUnits[MAX4052AESE_BUTT] = {0};	/*MAX4052AESE多路选择器模块的注册表*/

/* 接口函数
 ********************************************************/

/* 初始化MAX4052AESE模块
  -----------------------------
  入口：MAX4052AESE模块的ID号，引脚端口
  返回值：初始化好的MAX4052AESE模块结构体
*/
DRV_MAX4052AESE_TYPE* Max4052aeseInit(DRV_MAX4052AESE_ENUM id, \
											BSP_PORT_ENUM adda_port_number, BSP_PIN_ENUM adda_pin_number, \
											BSP_PORT_ENUM addb_port_number, BSP_PIN_ENUM addb_pin_number)
{	
	DRV_MAX4052AESE_TYPE* p_unit = (DRV_MAX4052AESE_TYPE*)calloc(1, sizeof(DRV_MAX4052AESE_TYPE));	/*申请内存*/

	/*分配失败返回NULL*/
	if(p_unit == NULL)
	{
		return NULL;
	}
		
	/*id错误返回NULL*/
	if(id >= MAX4052AESE_BUTT)
	{
		free(p_unit); 
		return NULL;
	}
	
	/*如果当前模块存在，取消分配新存储区*/
	if(_gp_Max4052aeseUnits[id] != NULL)
	{
		free(p_unit);
		p_unit = _gp_Max4052aeseUnits[id];
	}
	else
	{
		_gp_Max4052aeseUnits[id] = p_unit;
	}
	
	/*初始化*/
	
	/*-------------------------------常量*/
	p_unit->id             = id;				/*模块id*/
	p_unit->adda_port_number = adda_port_number;	/*引脚端口号*/
	p_unit->adda_pin_number  = adda_pin_number;		/*引脚序号*/
	BSP_Init_Pin(adda_port_number, adda_pin_number, _OUT_PP_);	/*初始化硬件*/
	p_unit->addb_port_number = addb_port_number;	/*引脚端口号*/
	p_unit->addb_pin_number  = addb_pin_number;		/*引脚序号*/
	BSP_Init_Pin(addb_port_number, addb_pin_number, _OUT_PP_);		/*初始化硬件*/
	
	/*-------------------------------变量*/
	p_unit->status = MAX4052AESE_READY;
	p_unit->adda_pin_buffer = 0;
	p_unit->addb_pin_buffer = 0;
	p_unit->choose = 0;
	
	Max4052aeseChoose(p_unit, 1);	/*初始化选择通道1*/
	
	return p_unit;
}

/* MAX4052AESE模块选择通道
  -----------------------------
  入口：MAX4052AESE模块的ID号，通道号
  返回值：true 成功，flase 失败
*/
bool Max4052aeseChoose(DRV_MAX4052AESE_TYPE* p_unit, uint8_t choose)
{
	if((choose > 4) || (choose < 1))
		return false;
	
	p_unit->choose = choose;
	switch(choose)
	{
		case 1:
			p_unit->adda_pin_buffer = 0;
			p_unit->addb_pin_buffer = 0;
			BSP_WritePin(p_unit->adda_port_number, p_unit->adda_pin_number, p_unit->adda_pin_buffer);
			BSP_WritePin(p_unit->addb_port_number, p_unit->addb_pin_number, p_unit->addb_pin_buffer);
			break;
		case 2:
			p_unit->adda_pin_buffer = 1;
			p_unit->addb_pin_buffer = 0;
			BSP_WritePin(p_unit->adda_port_number, p_unit->adda_pin_number, p_unit->adda_pin_buffer);
			BSP_WritePin(p_unit->addb_port_number, p_unit->addb_pin_number, p_unit->addb_pin_buffer);
			break;
		case 3:
			p_unit->adda_pin_buffer = 0;
			p_unit->addb_pin_buffer = 1;
			BSP_WritePin(p_unit->adda_port_number, p_unit->adda_pin_number, p_unit->adda_pin_buffer);
			BSP_WritePin(p_unit->addb_port_number, p_unit->addb_pin_number, p_unit->addb_pin_buffer);
			break;
		case 4:
			p_unit->adda_pin_buffer = 1;
			p_unit->addb_pin_buffer = 1;
			BSP_WritePin(p_unit->adda_port_number, p_unit->adda_pin_number, p_unit->adda_pin_buffer);
			BSP_WritePin(p_unit->addb_port_number, p_unit->addb_pin_number, p_unit->addb_pin_buffer);
			break;
	}
	return true;
}
