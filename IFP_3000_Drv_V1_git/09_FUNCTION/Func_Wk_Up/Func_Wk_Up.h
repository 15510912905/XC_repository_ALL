#ifndef _FUNC_WKUP_H_
#define _FUNC_WKUP_H_

#include "Func_XC2000_Liquid_Pressure.h"
#include "Func_ADHandler.h"
#include "Global_Variable.h"

#pragma pack(1)	/*��1�ֽڶ���*/

#define HOME_WAK_UP_PORT_A (GPIOA)
#define HOME_WAK_UP_PIN_A  (GPIO_Pin_0)
					    
#define WKUP_KD (!GPIO_ReadInputDataBit(HOME_WAK_UP_PORT_A,HOME_WAK_UP_PIN_A)) //(1)//PAin(0)			//PA0 ����Ƿ��ⲿWK_UP��������
	
void Sys_Standby(void);
uint8_t Check_WKUP(void);		//���WKUP�ŵ��ź�
void WKUP_Init(void); 			//PA0 WKUP���ѳ�ʼ��
void Sys_Enter_Standby(void);	//ϵͳ�������ģʽ

#endif
	
