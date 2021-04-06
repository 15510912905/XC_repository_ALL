/********************************************************
   ��Ȩ���� (C), 2001-2100, �Ĵ��½���������ɷ����޹�˾
  -------------------------------------------------------

				Ƕ��ʽ����ƽ̨����������

  -------------------------------------------------------
   �� �� ��   : Tesk.h
   �� �� ��   : V1.0.0.0
   ��    ��   : ryc
   ��������   : 2019��08��01��
   ��������   : ���岢������
   ������     : uC/OS-II V2.92.07
				Drv_Led V1.0.0.0
   ע         ����ģ�鲻������Ӳ����·�� 
 ********************************************************/

#ifndef _TASK_H_
#define _TASK_H_

#include "stdlib.h"
#include "os.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "Func_IFP_300_Drv.h"

/*--------------------------------------------------------------*/
#define TEST_STK_SIZE           (0)
#define IFP_300_DRV             (1)
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
#ifdef IFP_300_DRV								   /* ͨ��������*/
/*--------------------------------------------------------------*/
	
/*--------------------------------------------------------------*/
#elif XC2000_LIQUID_PRESSURE				   /* */
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
#endif
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*���������ջ���*/
#define START_STK_SIZE 		             (128)//(256)    //�����ջ��С
#define LED0_STK_SIZE 		             (64)//(128)     //�����ջ��С
#define POWER_MANAGESTK_SIZE 		     (128)//(128)    //�����ջ��С
#define USER_DISPLAY_SIZE 		         (2048)//(2048)  //�����ջ��С
#define TJC_INTERFACE_SIZE 		         (256)//(256)    //�����ջ��С
#define READ_ID_CARD_SIZE 		         (512)//(512)    //�����ջ��С
#define LOGIN_SIZE 		                 (256)//(256)    //�����ջ��С
#define UPDATA_SIZE 		             (256)//(256)    //�����ջ��С
#define POWER_ON_SIZE 		             (2048)//(256)    //�����ջ��С
#define WIFI_RECEIVE_SIZE 		         (256)//(256)    //�����ջ��С
#define WIFI_SEND_SIZE 		             (512)//(256)    //�����ջ��С
#define BACK_SHUTDOWN_SIZE 		         (64)//(128)     //�����ջ��С
#define LED1_STK_SIZE                    (128)//(128)    //�����ջ��С
#define FLOAT_STK_SIZE		             (128)//(128)    //�����ջ��С

/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*�����������ȼ�����ֵԽС���ȼ�Խ��*/
#define START_TASK_PRIO		            (3)        //�������ȼ�                                 
#define LED0_TASK_PRIO		            (21)       //�������ȼ�
#define POWER_MANAGESTKTASK_PRIO		(18)       //��Դ�����������ȼ�
#define USER_DISPLAY_PRIO		        (11)       //�û�UI��Ӧ�������ȼ�
#define TJC_INTERFACE_PRIO		        (10)       //��ĻͨѶ�������ȼ�
#define READ_ID_CARD_PRIO		        (17)       //��ID���������ȼ�
#define LOGIN_PRIO		                (12)       //��½�������ȼ�
#define UPDATA_PRIO		                (19)       //ʱ������������ȼ�
#define POWER_ON_PRIO		            (4)       //�ػ��������ȼ�
#define WIFI_RECEIVE_PRIO		        (16)       //WIFI���������ȼ�
#define WIFI_SEND_PRIO		            (15)       //WIFI���������ȼ�
#define BACK_SHUTDOWN_PRIO		        (20)       //��Ļ���عػ��������ȼ�
#define LED1_TASK_PRIO                  (14)       //�������ȼ�
#define FLOAT_TASK_PRIO		            (22)       //�������������ȼ�

/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/* ��ʼ�߳� */
extern OS_TCB StartTaskTCB;                                           //������ƿ�	
extern CPU_STK START_TASK_STK[START_STK_SIZE];                        //�����ջ
extern void start_task(void *p_arg);                                  //������
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*��������������*/
static void led0_task(void *p_arg);
static void led1_task(void *p_arg);                                   //������
static void TaskPowerManage(void *p_arg);
static void TaskUserDisplay(void* p_arg);
static void TaskTjc4832tInterface(void *p_arg);
static void TaskReadIDCard(void *p_arg);
static void TaskLogIn(void *p_arg);
static void TaskUpdataTime(void *p_arg);
static void TaskPowerOn(void *p_arg);
static void TaskWifiReceive(void *p_arg);
static void TaskWifiSend(void *p_arg);
static void TaskBackShutDown(void *p_arg);
static void float_task(void *p_arg);                                  //������

/*--------------------------------------------------------------*/


#endif
