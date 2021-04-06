#include "sys.h"
#include "malloc.h"	
#include "includes.h"
#include "Task.h"
#include "Func_IFP_300_Drv.h"

/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

				嵌入式开发平台——任务定义

  -------------------------------------------------------
   文 件 名   : main.c
   版 本 号   : V1.0.0.0
   作    者   : ZR
   生成日期   : 2020年10月01日
   功能描述   : 定义并行任务。
   依赖于     : uC/OS-III V3.0.03
   注         ：该文件不依赖于硬件电路。 
********************************************************/

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();                                                         /*申请临界区变量*/
	
	/* OSCfg_TickRate_Hz 目前是在节拍在5ms  */
	BSP_InitSysTick(SystemCoreClock, OSCfg_TickRate_Hz);	                /*设置系统滴答时钟 delay_init();延时初始化 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                         //中断分组配置	
	
	OSInit(&err);		                                                    //初始化UCOSIII	                                                                        
	OS_CRITICAL_ENTER();                                                    //进入临界区
	bFuncPrivateInit1();                                                    //初始化	
	//创建开始任务                                                          
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		                        //任务控制块
				 (CPU_CHAR	* )"start task", 		                        //任务名字
                 (OS_TASK_PTR )start_task, 			                        //任务函数
                 (void		* )0,					                        //传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,                             //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	                        //任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	                        //任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		                        //任务堆栈大小
                 (OS_MSG_QTY  )0,					                        //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					                        //当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					                        //用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,     //任务选项
                 (OS_ERR 	* )&err);				                        //存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	                                                    //退出临界区					 
	OSStart(&err);                                                          //开启UCOSIII
				 
	while(1){;}
}


