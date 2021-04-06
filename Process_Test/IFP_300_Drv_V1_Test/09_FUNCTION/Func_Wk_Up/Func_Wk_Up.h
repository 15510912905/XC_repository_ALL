#ifndef _FUNC_WKUP_H_
#define _FUNC_WKUP_H_

#include "Func_XC2000_Liquid_Pressure.h"
#include "Func_ADHandler.h"
#include "Global_Variable.h"

#pragma pack(1)	/*按1字节对齐*/

#define HOME_WAK_UP_PORT_A (GPIOA)
#define HOME_WAK_UP_PIN_A  (GPIO_Pin_0)
					    
#define WKUP_KD (!GPIO_ReadInputDataBit(HOME_WAK_UP_PORT_A,HOME_WAK_UP_PIN_A)) //(1)//PAin(0)			//PA0 检测是否外部WK_UP按键按下
	
void Sys_Standby(void);
uint8_t Check_WKUP(void);		//检测WKUP脚的信号
void WKUP_Init(void); 			//PA0 WKUP唤醒初始化
void Sys_Enter_Standby(void);	//系统进入待机模式

#endif
	
