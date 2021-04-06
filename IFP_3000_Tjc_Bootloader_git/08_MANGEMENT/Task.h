/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

				嵌入式开发平台——任务定义

  -------------------------------------------------------
   文 件 名   : Tesk.h
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2019年08月01日
   功能描述   : 定义并行任务。
   依赖于     : uC/OS-II V2.92.07
				Drv_Led V1.0.0.0
   注         ：该模块不依赖于硬件电路。 
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
#ifdef IFP_300_DRV								   /* 通用驱动板*/
/*--------------------------------------------------------------*/
	
/*--------------------------------------------------------------*/
#elif XC2000_LIQUID_PRESSURE				   /* */
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
#endif
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*定义任务堆栈深度*/
#define START_STK_SIZE 		             (128)//(256)    //任务堆栈大小
#define LED0_STK_SIZE 		             (64)//(128)     //任务堆栈大小
#define POWER_MANAGESTK_SIZE 		     (128)//(128)    //任务堆栈大小
#define USER_DISPLAY_SIZE 		         (2048)//(2048)  //任务堆栈大小
#define TJC_INTERFACE_SIZE 		         (256)//(256)    //任务堆栈大小
#define READ_ID_CARD_SIZE 		         (512)//(512)    //任务堆栈大小
#define LOGIN_SIZE 		                 (256)//(256)    //任务堆栈大小
#define UPDATA_SIZE 		             (256)//(256)    //任务堆栈大小
#define POWER_ON_SIZE 		             (2048)//(256)    //任务堆栈大小
#define WIFI_RECEIVE_SIZE 		         (256)//(256)    //任务堆栈大小
#define WIFI_SEND_SIZE 		             (512)//(256)    //任务堆栈大小
#define BACK_SHUTDOWN_SIZE 		         (64)//(128)     //任务堆栈大小
#define LED1_STK_SIZE                    (128)//(128)    //任务堆栈大小
#define FLOAT_STK_SIZE		             (128)//(128)    //任务堆栈大小

/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*定义任务优先级，数值越小优先级越高*/
#define START_TASK_PRIO		            (3)        //任务优先级                                 
#define LED0_TASK_PRIO		            (21)       //任务优先级
#define POWER_MANAGESTKTASK_PRIO		(18)       //电源管理任务优先级
#define USER_DISPLAY_PRIO		        (11)       //用户UI响应任务优先级
#define TJC_INTERFACE_PRIO		        (10)       //屏幕通讯任务优先级
#define READ_ID_CARD_PRIO		        (17)       //读ID卡任务优先级
#define LOGIN_PRIO		                (12)       //登陆任务优先级
#define UPDATA_PRIO		                (19)       //时间更新任务优先级
#define POWER_ON_PRIO		            (4)       //关机任务优先级
#define WIFI_RECEIVE_PRIO		        (16)       //WIFI收任务优先级
#define WIFI_SEND_PRIO		            (15)       //WIFI发任务优先级
#define BACK_SHUTDOWN_PRIO		        (20)       //屏幕下载关机任务优先级
#define LED1_TASK_PRIO                  (14)       //任务优先级
#define FLOAT_TASK_PRIO		            (22)       //浮点数任务优先级

/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/* 初始线程 */
extern OS_TCB StartTaskTCB;                                           //任务控制块	
extern CPU_STK START_TASK_STK[START_STK_SIZE];                        //任务堆栈
extern void start_task(void *p_arg);                                  //任务函数
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/*变量及函数声明*/
static void led0_task(void *p_arg);
static void led1_task(void *p_arg);                                   //任务函数
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
static void float_task(void *p_arg);                                  //任务函数

/*--------------------------------------------------------------*/


#endif
