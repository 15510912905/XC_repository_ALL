/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——VersaPump6微量泵模块

  -------------------------------------------------------
   文 件 名   : Drv_VersaPump6.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2020年03月18日
   功能描述   : 定义VersaPump6微量泵模块的控制。
   使用方法   ：上层模块通过调用VersaPump6_Init获得一个
				VersaPump6模块的指针，通过调用VersaPump6_Sample
				进行吸样，通过调用VersaPump6_BlowOff排样，
				通过调用VersaPump6_Reset复位。
   依赖于     : BSP.h
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/
 
#include "Drv_VersaPump6.h"

DRV_VERSAPUMP6_TYPE* _gp_VersaPump6[VERSAPUMP6_BUTT] = {0};	/*微量泵模块的注册表*/

/* 接口函数
 ********************************************************/

/* 初始化扫码模块
  -----------------------------
  入口：扫码模块的ID号，最大步数，最大体积，波特率，TX、RX端口
  返回值：初始化好的扫码模块结构体
*/
DRV_VERSAPUMP6_TYPE* Drv_VersaPump6_Init(DRV_VERSAPUMP6_ENUM id, \
										uint16_t max_step, uint16_t max_distance, \
										BSP_USART_ENUM usart_number, uint32_t baud_rate, \
										BSP_PORT_ENUM tx_port_number, BSP_PIN_ENUM tx_pin_number, \
										BSP_PORT_ENUM rx_port_number, BSP_PIN_ENUM rx_pin_number)
{	
	uint8_t i = 0;
	DRV_VERSAPUMP6_TYPE* p_unit = (DRV_VERSAPUMP6_TYPE*)calloc(1, sizeof(DRV_VERSAPUMP6_TYPE));	/*申请内存*/
	
	/*分配失败返回NULL*/
	if(p_unit == NULL)
	{
		return NULL;
	}
		
	/*id错误返回NULL*/
	if(id >= VERSAPUMP6_BUTT)
	{
		free(p_unit); 
		return NULL;
	}
	
	/*如果当前模块存在，取消分配新存储区*/
	if(_gp_VersaPump6[id] != NULL)
	{
		free(p_unit);
		p_unit = _gp_VersaPump6[id];
	}
	else
	{
		_gp_VersaPump6[id] = p_unit;
	}
	
	/*初始化*/
	
	/*------------------------------常量*/
	p_unit->id = id;							/*串口模块编号*/
	p_unit->max_step = max_step;				/*总步数*/
	p_unit->max_distance = max_distance;		/*总行程*/
	p_unit->usart_number = usart_number;		/*串口模块编号*/
	p_unit->baud_rate = baud_rate;				/*波特率*/
	p_unit->tx_port_number = tx_port_number; 	/*TX引脚端口号*/
	p_unit->tx_pin_number = tx_pin_number;		/*TX引脚编号*/
	p_unit->rx_port_number = rx_port_number; 	/*RX引脚端口号*/
	p_unit->rx_pin_number = rx_pin_number;		/*RX引脚编号*/
	BSP_Init_UsartInterrupt(p_unit->usart_number, p_unit->baud_rate, \
							 p_unit->tx_port_number, p_unit->tx_pin_number, \
							 p_unit->rx_port_number, p_unit->rx_pin_number);
	
	p_unit->work_done_sem = OSSemCreate(0);				/*执行完成信号*/
	
	/*------------------------------变常*/
	
	/*------------------------------变量*/
	p_unit->status = VERSAPUMP6_READY;				/*该模块的状态*/
	for(i = 0; i < USART_RX_MAX_NUMBER; i++)
	{
		p_unit->rx_buffer[i] = 0;	/*接收缓存*/
	}
	p_unit->rx_push = 0;
	
//	Drv_VersaPump6_Reset(p_unit);
//	Drv_VersaPump6_ValueToggle(p_unit, VERSAPUMP6_VALUE_AB);
	
	p_unit->distance_now = 0;
	
	return p_unit;
}

/* 微量泵吸样
  -----------------------------
  总行程48000步，50uL
  /1A24000R<enter>
  2F3040030D0AFF
  入口：微量泵模块结构体，吸样体积
  返回值：true 成功，false 失败
*/
bool Drv_VersaPump6_Sample(DRV_VERSAPUMP6_TYPE* p_unit, double distance)
{
	uint8_t err = OS_ERR_NONE;
	
	uint16_t step = 0, step_temp = 0;
	uint8_t str[5] = {0}, cmd[12] = "/1P", i = 0, j = 0;
	
	step_temp = step = distance / (double)(p_unit->max_distance) * (double)(p_unit->max_step);
	for(i = 0; i < 5; i++)	/*转换为字符串*/
	{
		str[4 - i] = step_temp % 10 + '0';
		step_temp /= 10;
	}
	for(i = 0, j = 0; i < 5; i++)
	{
		if(str[i] != '0')
		{
			for(; i < 5; i++)
			{
				cmd[3 + j++] = str[i];
			}
		}			
	}
	cmd[3 + j++] = 'R';
	cmd[3 + j++] = '\r';
	cmd[3 + j++] = '\n';
	cmd[3 + j++] = '\0';
	
	_Drv_VersaPump6_SendCmd(p_unit, cmd);
	OSSemPend(p_unit->work_done_sem, 500, &err);
	if(err != OS_ERR_NONE)
	{
		return false;
	}
	else
	{
		while(1)
		{
			_Drv_VersaPump6_SendCmd(p_unit, "/1?\r\n");
			OSSemPend(p_unit->work_done_sem, 500, &err);
			if(err != OS_ERR_NONE)
			{
				return false;
			}
			else
			{
				if(_Drv_VersaPump6_Check(p_unit, step + p_unit->distance_now, _Drv_VersaPump6_GetDataStr(p_unit, p_unit->rx_buffer)) == false)	/*位置不对*/
				{
					OSTimeDlyHMSM(0, 0, 0, 100);
					i++;
					if(i > 20)	/*超时*/
					{
						return false;
					}
				}
				else
				{
					p_unit->distance_now += step;
					return true;
				}
			}
		}
	}
}

/* 微量泵排样
  -----------------------------
  /1D16000R<enter>
  2F3040030D0AFF
  入口：微量泵模块结构体，排样体积uL
  返回值：true 成功，false 失败
*/
bool Drv_VersaPump6_BlowOff(DRV_VERSAPUMP6_TYPE* p_unit, double distance)
{
	uint8_t err = OS_ERR_NONE;
	
	uint16_t step = 0, step_temp = 0;
	uint8_t str[5] = {0}, cmd[12] = "/1D", i = 0, j = 0;
	
	step_temp = step = distance / (double)(p_unit->max_distance) * (double)(p_unit->max_step);
	for(i = 0; i < 5; i++)	/*转换为字符串*/
	{
		str[4 - i] = step_temp % 10 + '0';
		step_temp /= 10;
	}
	for(i = 0, j = 0; i < 5; i++)
	{
		if(str[i] != '0')
		{
			for(; i < 5; i++)
			{
				cmd[3 + j++] = str[i];
			}
		}			
	}
	cmd[3 + j++] = 'R';
	cmd[3 + j++] = '\r';
	cmd[3 + j++] = '\n';
	cmd[3 + j++] = '\0';
	
	_Drv_VersaPump6_SendCmd(p_unit, cmd);
	OSSemPend(p_unit->work_done_sem, 500, &err);
	if(err != OS_ERR_NONE)
	{
		return false;
	}
	else
	{
		while(1)
		{
			_Drv_VersaPump6_SendCmd(p_unit, "/1?\r\n");
			OSSemPend(p_unit->work_done_sem, 500, &err);
			if(err != OS_ERR_NONE)
			{
				return false;
			}
			else
			{
				if(_Drv_VersaPump6_Check(p_unit, p_unit->distance_now - step, _Drv_VersaPump6_GetDataStr(p_unit, p_unit->rx_buffer)) == false)	/*位置不对*/
				{
					OSTimeDlyHMSM(0, 0, 0, 100);
					i++;
					if(i > 100)	/*超时*/
					{
						return false;
					}
				}
				else
				{
					p_unit->distance_now -= step;
					return true;
				}
			}
		}
	}
}

/* 微量泵复位
  -----------------------------
  /1W4R<enter>
  2F3040030D0AFF
  入口：微量泵模块结构体
  返回值：true 成功，false 失败
*/
bool Drv_VersaPump6_Reset(DRV_VERSAPUMP6_TYPE* p_unit)
{
	uint8_t err = OS_ERR_NONE;
	uint8_t i = 0;
	
	_Drv_VersaPump6_SendCmd(p_unit, "/1W4R\r\n");
	OSSemPend(p_unit->work_done_sem, 500, &err);
	if(err != OS_ERR_NONE)
	{
		return false;
	}
	else
	{
		while(1)
		{
			_Drv_VersaPump6_SendCmd(p_unit, "/1?\r\n");
			OSSemPend(p_unit->work_done_sem, 500, &err);
			if(err != OS_ERR_NONE)
			{
				return false;
			}
			else
			{
				if(_Drv_VersaPump6_Check(p_unit, 0, _Drv_VersaPump6_GetDataStr(p_unit, p_unit->rx_buffer)) == false)	/*位置不对*/
				{
					OSTimeDlyHMSM(0, 0, 0, 100);
					i++;
					if(i > 100)	/*超时*/
					{
						return false;
					}
				}
				else
				{
					p_unit->distance_now = 0;
					return true;
				}
			}
		}
	}
}

/* 微量泵阀状态切换
  -----------------------------
  /1IR<enter>
  /1OR<enter>
  /1BR<enter>
  2F3040030D0AFF
  入口：微量泵模块结构体，阀的状态
  返回值：true 成功，false 失败
*/
bool Drv_VersaPump6_ValueToggle(DRV_VERSAPUMP6_TYPE* p_unit, DRV_VERSAPUMP6_VALUE_STATUS_ENUM status)
{
	uint8_t err = OS_ERR_NONE;
	
	switch(status)
	{
		case VERSAPUMP6_VALUE_AB:
			p_unit->value_status = VERSAPUMP6_VALUE_AB;
			_Drv_VersaPump6_SendCmd(p_unit, "/1BR\r\n");
			break;
		
		case VERSAPUMP6_VALUE_AS:
			p_unit->value_status = VERSAPUMP6_VALUE_AS;
			_Drv_VersaPump6_SendCmd(p_unit, "/1IR\r\n");
			break;
			
		case VERSAPUMP6_VALUE_BS:
			p_unit->value_status = VERSAPUMP6_VALUE_BS;
			_Drv_VersaPump6_SendCmd(p_unit, "/1OR\r\n");
			break;
		
		default:
			return false;
	}
	OSSemPend(p_unit->work_done_sem, 500, &err);
	if(err != OS_ERR_NONE)
		return false;
	else
		return true;
}

/* 发送命令
  -----------------------------
  入口：微量泵模块结构体，命令字符串
  返回值：true 成功，false 失败
*/
static bool _Drv_VersaPump6_SendCmd(DRV_VERSAPUMP6_TYPE* p_unit, uint8_t* datas)
{
	uint8_t i = 0;
	
	p_unit->status = VERSAPUMP6_BUSY;
	p_unit->rx_push = 0;
	
	while(datas[i] != '\0')
	{
		BSP_UsartSendByte(p_unit->usart_number, datas[i]);	/*依次发送字符串*/
		i++;
		if(i > 100)
			return false;
	}
	
	return true;
}

/* 判断整形数和字符串数是否相等
  -----------------------------
  入口：微量泵模块结构体，数据，字符串
  返回值：true 相等，false 不相等
*/
static bool _Drv_VersaPump6_Check(DRV_VERSAPUMP6_TYPE* p_unit, uint16_t data_int, uint8_t* data_str)
{
	uint32_t temp = 0;
	uint8_t i = 0, j = 0;
	
	for(i = 0; i <= 5; i++)
	{
		if(data_str[i] == '\0')	/*寻找字符串结尾*/
		{
			for(j = 0; j < i; j++)
			{
				temp += data_str[j] - '0';
				temp *= 10;
			}
			temp /= 10;
			break;
		}
	}
	if(temp == data_int)
		return true;
	else
		return false;
}

/* 提取字符串中的数值
  -----------------------------
  入口：微量泵模块结构体，字符串
  返回值：数值地址
*/
static uint8_t* _Drv_VersaPump6_GetDataStr(DRV_VERSAPUMP6_TYPE* p_unit, uint8_t* data_str)
{
	uint8_t i = 0;
	
	for(i = 0; i < 15; i++)
	{
		if((p_unit->rx_buffer[i] == 0x20) 
		&& (p_unit->rx_buffer[i + 1] == 0x03) 
		&& (p_unit->rx_buffer[i + 2] == 0x0D) 
		&& (p_unit->rx_buffer[i + 3] == 0x0A) 
		&& (p_unit->rx_buffer[i + 4] == 0xFF))
		{
			p_unit->rx_buffer[i] = '\0';
			return &(p_unit->rx_buffer[3]);
		}
	}
	
	return NULL;
}

/* 串口4中断处理
  -------------------------------
  将收到的数据放入缓存
*/
void BSP_Uart4_IRQHandler(void)
{
	if(_gp_VersaPump6[VERSAPUMP6_1]->status == VERSAPUMP6_BUSY)	/*在动作才读数据*/
	{
		_gp_VersaPump6[VERSAPUMP6_1]->rx_buffer[_gp_VersaPump6[VERSAPUMP6_1]->rx_push] = BSP_UsartGetByte(_gp_VersaPump6[VERSAPUMP6_1]->usart_number);
		_gp_VersaPump6[VERSAPUMP6_1]->rx_push = (_gp_VersaPump6[VERSAPUMP6_1]->rx_push + 1) % USART_RX_MAX_NUMBER;
		if(_gp_VersaPump6[VERSAPUMP6_1]->rx_buffer[0] != '/')	/*如果没收到包头，就清零*/
		{
			_gp_VersaPump6[VERSAPUMP6_1]->rx_push = 0;
			return;
		}
		if((_gp_VersaPump6[VERSAPUMP6_1]->rx_buffer[_gp_VersaPump6[VERSAPUMP6_1]->rx_push - 1] == 0xFF) \
		&& (_gp_VersaPump6[VERSAPUMP6_1]->rx_buffer[_gp_VersaPump6[VERSAPUMP6_1]->rx_push - 2] == 0x0A) \
		&& (_gp_VersaPump6[VERSAPUMP6_1]->rx_buffer[_gp_VersaPump6[VERSAPUMP6_1]->rx_push - 3] == 0x0D))	/*收到包尾 0D 0A FF*/
		{
			_gp_VersaPump6[VERSAPUMP6_1]->status = VERSAPUMP6_READY;	/*退出执行状态*/
			_gp_VersaPump6[VERSAPUMP6_1]->rx_push = 0;
			OSSemPost(_gp_VersaPump6[VERSAPUMP6_1]->work_done_sem);
			return;
		}
	}
}
