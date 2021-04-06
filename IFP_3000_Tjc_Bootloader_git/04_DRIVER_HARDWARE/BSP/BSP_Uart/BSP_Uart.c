/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

				嵌入式开发平台——BSP层 UART封装

  -------------------------------------------------------
   文 件 名   : BSP_Uart.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2019年11月14日
   功能描述   : 定义一种基于STM32的板级支持包。
				该层依赖于硬件电路。
   依赖于     : STM32F10x_StdPeriph_Lib_V3.5.0
 ********************************************************/
 
#include "BSP_Uart.h"  

//static uint8_t l_uRec1Statc = 0;
////static uint8_t l_uRec2Statc = 0;
////static uint8_t l_uRec3Statc = 0;
//static uint8_t l_uRecNum = 0;
uint8_t g_UsartPrintfFlag = _USART1_;
//uint8_t g_UsartPrintfFlag = _USART3_;

/*串口中断函数注册表*/
void(* BSP_UartIRQHandler[4])(void) = {0};	/*串口中断函数指针列表*/

/* 初始化
  ----------------------------------------------------------------------*/

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{   
	if( _USART1_==g_UsartPrintfFlag ){
		while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
		USART1->DR = (uint8_t) ch;  
	}else if(_USART2_==g_UsartPrintfFlag){		
		while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
		USART2->DR = (uint8_t) ch; 
	}else if(_USART3_==g_UsartPrintfFlag){	
		while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
		USART3->DR = (uint8_t) ch; 
	}if(_USART4_==g_UsartPrintfFlag){	
		while((UART4->SR&0X40)==0);//循环发送,直到发送完毕   
		UART4->DR = (uint8_t) ch; 
	}else{
	
	}
	
	return ch;
}

/* */
int myprintf( const char *format,... )
{
	int ierr = 0;
	CPU_SR_ALLOC();                                             /*申请临界区变量*/
	va_list args;

	OS_CRITICAL_ENTER();	                                    //进入临界区	
	va_start(args, format);
	ierr = vprintf( format, args );                             //printf调用了vprintf
	va_end(args);
	OS_CRITICAL_EXIT();		                                    //退出临界区
	
	return ierr;
}
#endif 


/* 初始化UART及接收中断
  -----------------------------------------
  入口：串口编号、波特率，TX、RX端口
  返回值：成功true，失败false
*/
bool BSP_Init_UsartInterrupt(BSP_USART_ENUM usart_number, uint32_t baud_rate, \
							 BSP_PORT_ENUM tx_port_number, BSP_PIN_ENUM tx_pin_number, \
							 BSP_PORT_ENUM rx_port_number, BSP_PIN_ENUM rx_pin_number)
{
	GPIO_InitTypeDef    GPIO_InitStructure;  
	USART_InitTypeDef   USART_InitStructure; 
	NVIC_InitTypeDef    NVIC_InitStructure;
	
	uint8_t irq;

	/*初始化串口时钟*/
	switch(usart_number)
	{
		case _USART1_:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
			break;
			
		case _USART2_:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
			break;
			
		case _USART3_:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
			break;
			
		case _USART4_:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
			break;
			
		default:
			return false;
	}
	/*引脚时钟初始化*/
	RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOA << tx_port_number) | (RCC_APB2Periph_GPIOA << rx_port_number) | RCC_APB2Periph_AFIO, ENABLE);
	
	/*使能串口重映射*/
	switch(usart_number)
	{
		case _USART1_:
			if(tx_port_number == _PB_)		/*需要重映射*/
				GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
			break;
			
		case _USART2_:
			if(tx_port_number == _PD_)		/*需要重映射*/
				GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
			break;
			
		case _USART3_:
			if(tx_port_number == _PC_)		/*需要重映射*/
				GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
			else if(tx_port_number == _PD_)	/*需要重映射*/
				GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);
			break;
			
		case _USART4_:
			break;
			
		default:
			return false;
	}
		
	/*管脚配置*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 << tx_pin_number;			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
	GPIO_Init(PORT(tx_port_number), &GPIO_InitStructure);			/* TXIO */
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 << rx_pin_number;			 	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(PORT(rx_port_number), &GPIO_InitStructure); 			/* RXIO */
	
	/*串口工作模式配置*/
	USART_InitStructure.USART_BaudRate = baud_rate;						        	    /*设置波特率*/	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 		                /*8位数据位*/		 	
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					            /*1位停止位*/	
	USART_InitStructure.USART_Parity = USART_Parity_No; 						        /*无校验*/
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;     /*硬件流控 None*/
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;        				/*设置为收发模式*/
	
	switch(usart_number)
	{
		case _USART1_:
			USART_Init(USART1, &USART_InitStructure);			                   		/*初始化UART*/
			USART_Cmd(USART1, ENABLE);	                                           		/*开启串口*/
			irq = USART1_IRQn;
			break;
			
		case _USART2_:
			USART_Init(USART2, &USART_InitStructure);			                   		/*初始化UART*/
			USART_Cmd(USART2, ENABLE);	                                           		/*开启串口*/
			irq = USART2_IRQn;
			break;
			
		case _USART3_:
			USART_Init(USART3, &USART_InitStructure);			                   		/*初始化UART*/
			USART_Cmd(USART3, ENABLE);	                                           		/*开启串口*/
			irq = USART3_IRQn;
			break;
			
		case _USART4_:
			USART_Init(UART4, &USART_InitStructure);			                   		/*初始化UART*/
			USART_Cmd(UART4, ENABLE);	                                           		/*开启串口*/
			irq = UART4_IRQn;
			break;
			
		default:
			return false;
	}                             

	/*中断设置*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
	NVIC_InitStructure.NVIC_IRQChannel = irq;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;       					/*低优先级别的中断*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			    					/*响应中断等级为0*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);  
	
	switch(usart_number)
	{
		case _USART1_:
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	                 					/*Enable UART IRQ*/
			break;
			
		case _USART2_:
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	                 					/*Enable UART IRQ*/
			break;
			
		case _USART3_:
			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	                 					/*Enable UART IRQ*/
			break;
			
		case _USART4_:
			USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	                 					/*Enable UART IRQ*/
			break;
			
		default:
			return false;
	}
	
	return true;
}

/* 操作
  ----------------------------------------------------------------------*/

/* 串口发送一个字节
  -----------------------------
  入口：串口编号，发送内容
  返回值：成功true，失败false
*/
bool BSP_UsartSendByte(BSP_USART_ENUM usart_number, uint8_t data)
{
	
	switch(usart_number)
	{
		case _USART1_: 
			USART_SendData(USART1, data); 			/*发送数据*/
			while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
			break;
		case _USART2_:
			USART_SendData(USART2, data); 			/*发送数据*/
			while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
			break;
		case _USART3_:
			USART_SendData(USART3, data); 			/*发送数据*/
			while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
			break;
		case _USART4_:
			USART_SendData(UART4, data); 			/*发送数据*/
			while (USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
			break;
		default: 
			return false;
	}
	
	return true;
}

/* 串口接收一个字节
-----------------------------ok
入口：串口编号
返回值：串口接收到的数据
*/
uint8_t BSP_UsartGetByte(BSP_USART_ENUM usart_number)
{
	switch(usart_number)
	{
		case _USART1_:
			return USART_ReceiveData(USART1);
		case _USART2_:
			return USART_ReceiveData(USART2);
		case _USART3_:
			return USART_ReceiveData(USART3);
		case _USART4_:
			return USART_ReceiveData(UART4);
		default:
			return 0;
	}
}

/* 中断
  ----------------------------------------------------------------------*/
 
/* 串口1中断
  -------------------------------
*/
void USART1_IRQHandler(void)
{
   if(USART_GetITStatus(USART1, USART_IT_IDLE)!=RESET)
   {
		USART_ClearITPendingBit(USART1 , USART_IT_IDLE); 
		BSP_Usart1_IRQHandler();
   }
}

/* 串口2中断
  -------------------------------
*/
void USART2_IRQHandler(void)
{
   if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
   {
		USART_ClearITPendingBit(USART2 , USART_IT_RXNE);
		BSP_Usart2_IRQHandler();
   }
}

/* 串口3中断
  -------------------------------
*/
void USART3_IRQHandler(void)
{
   if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
   {	   
		USART_ClearITPendingBit(USART3 , USART_IT_RXNE); 
		BSP_Usart3_IRQHandler();		
   }
}

/* 串口4中断
  -------------------------------
*/
void UART4_IRQHandler(void)
{
   if(USART_GetITStatus(UART4,USART_IT_IDLE)!=RESET)
   {	   
		USART_ClearITPendingBit(UART4 , USART_IT_IDLE); 
		BSP_Usart4_IRQHandler();		
   }
}

void BSP_Usart1_IRQHandler( void )
{
	uint16_t Count = 0;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OS_ERR err = OS_ERR_NONE;
	OSIntEnter();    
#endif	
	USART_ReceiveData(USART1);	/* 不能取消 */
	
	/* 获取接收数据个数 */
	Count = DMA_GetCurrDataCounter(DMA1_Channel5);
	g_Usart_Rx_Sta = USART_REC_LEN - Count;
	
	OSSemPost( (OS_SEM *)&g_TjcUpdata,OS_OPT_POST_NO_SCHED,&err );               /*释放信号量 关机/开机 */
	
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
}

//void BSP_Usart1_IRQHandler( void )
//{
//	u8 Res;
//#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntEnter();    
//#endif	
//	Res =USART_ReceiveData(USART1);	//读取接收到的数据

//	if((g_Usart_Rx_Sta&0x8000)==0){  //接收未完成		
//		if(g_Usart_Rx_Sta&0x4000){   //接收到了0x0d			
//			if(Res!=0x0a){
//				g_Usart_Rx_Sta=0;//接收错误,重新开始
//			}
//			else{
//				g_Usart_Rx_Sta|=0x8000;	//接收完成了 
//			}
//		}
//		else //还没收到0X0D
//		{	
//			if(Res==0x0d){
//				g_Usart_Rx_Sta|=0x4000;
//			}
//			else{	
//				g_Usart_Rx_Buf[g_Usart_Rx_Sta&0X3FFF]=Res ;
//				g_Usart_Rx_Sta++;
//				if(g_Usart_Rx_Sta>(USART_REC_LEN-1)){ 
//					g_Usart_Rx_Sta=0;//接收数据错误,重新开始接收
//				}						
//			}		 
//		}
//	} 

//#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//#endif
//}

#if 0
void BSP_Usart2_IRQHandler( void )
{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OS_ERR err = OS_ERR_NONE;
	OSIntEnter();    
#endif	
	Res =USART_ReceiveData(USART2);	//读取接收到的数据
	
	if((g_Usart2_Rx_Sta&0x8000)==0){  //接收未完成		
		if(g_Usart2_Rx_Sta&0x4000){   //接收到了0x4b			
			if(Res!=0x0a){
				g_Usart2_Rx_Sta=0;//接收错误,重新开始
			}else{
				g_Usart2_Rx_Buf[g_Usart2_Rx_Sta&0X3FFF]=Res ;
				g_Usart2_Rx_Sta|=0x8000;	   //接收完成了 				
				OSSemPost( (OS_SEM *)&g_WifiReceive,OS_OPT_POST_NO_SCHED,&err );   /* 发送Wifi信号量 */			
			}
		}
		else //还没收到4f
		{	
			g_Usart2_Rx_Buf[g_Usart2_Rx_Sta&0X3FFF]=Res ;
			g_Usart2_Rx_Sta++;
			if(Res==0x0d){
				g_Usart2_Rx_Sta|=0x4000;
			}
			else{	
				if(g_Usart2_Rx_Sta>(USART2_REC_LEN-1)){ 
					g_Usart2_Rx_Sta=0;//接收数据错误,重新开始接收
				}						
			}		 
		}
	} 	       
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
}
#else
void BSP_Usart2_IRQHandler( void )
{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OS_ERR err = OS_ERR_NONE;
	OSIntEnter();    
#endif	
	Res =USART_ReceiveData(USART2);	//读取接收到的数据
	
	if((g_Usart2_Rx_Sta&0x8000)==0){  //接收未完成		
		if(g_Usart2_Rx_Sta&0x4000){   //接收到了0x4b			
			if(Res!=0x4b){
				g_Usart2_Rx_Sta=0;//接收错误,重新开始
			}else{
				g_Usart2_Rx_Buf[g_Usart2_Rx_Sta&0X3FFF]=Res ;
				g_Usart2_Rx_Sta|=0x8000;	   //接收完成了 				
				OSSemPost( (OS_SEM *)&g_WifiReceive,OS_OPT_POST_NO_SCHED,&err );   /* 发送Wifi信号量 */			
			}
		}
		else //还没收到4f
		{	
			g_Usart2_Rx_Buf[g_Usart2_Rx_Sta&0X3FFF]=Res ;
			g_Usart2_Rx_Sta++;
			if(Res==0x4f){
				g_Usart2_Rx_Sta|=0x4000;
			}
			else{	
				if(g_Usart2_Rx_Sta>(USART2_REC_LEN-1)){ 
					g_Usart2_Rx_Sta=0;//接收数据错误,重新开始接收
				}						
			}		 
		}
	} 	       
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
}
#endif

void BSP_Usart3_IRQHandler( void )
{
	u8 Res;
	//u8 RecSta = 0;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif	
	Res =USART_ReceiveData(USART3);	//读取接收到的数据

	if((g_Usart3_Rx_Sta&0x8000)==0){  //接收未完成		
		if(g_Usart3_Rx_Sta&0x4000){   //接收到了0x0d			
			if(Res!=0x0a){
				g_Usart3_Rx_Sta=0;    //接收错误,重新开始
			}
			else{
				g_Usart3_Rx_Sta|=0x8000;	//接收完成了 
			}
		}
		else //还没收到0X0D
		{	
			if(Res==0x0d){
				g_Usart3_Rx_Sta|=0x4000;
			}
			else{	
				g_Usart3_Rx_Buf[g_Usart3_Rx_Sta&0X3FFF]=Res ;
				g_Usart3_Rx_Sta++;
				if(g_Usart3_Rx_Sta>(USART3_REC_LEN-1)){ 
					g_Usart3_Rx_Sta=0;//接收数据错误,重新开始接收
				}						
			}		 
		}
	}   		 
      
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
}

/* 不能接收16777215==0xffffff数 */
void BSP_Usart4_IRQHandler( void )
{
	uint16_t Count = 0;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OS_ERR err = OS_ERR_NONE;
	OSIntEnter();    
#endif	
	USART_ReceiveData(UART4);	/* 不能取消 */
	
	/* 获取接收数据个数 */
	Count = DMA_GetCurrDataCounter(DMA2_Channel3);
	g_Usart4_Rx_Sta = USART4_REC_LEN - Count;
	
	OSSemPost( (OS_SEM *)&g_TjcUpgarde,OS_OPT_POST_NO_SCHED,&err );               /*  */
	
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif

}

//	u8 Res;
//#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OS_ERR err = OS_ERR_NONE;
//	OSIntEnter();    
//#endif	
//	Res =USART_ReceiveData(UART4);	//读取接收到的数据UART4 USART4
//	//USART_SendData(USART1, Res); 			/* 测试使用 发送数据*/
//#if DOWN_TJC_BIN
//	if( TJC_FILE_DOWNLOAD_OFF==g_uTjcFileDownload ){
//#endif		
//		g_Usart4_Rx_Buf[g_Usart4_Rx_Sta++]=Res ;
//		
//		if( 0xff==Res ){
//			l_uRecNum++;
//			if( 1==(l_uRecNum%3) ){
//				l_uRec1Statc = g_Usart4_Rx_Sta;	
//			}else if( 2==(l_uRecNum%3) ){
//				if( (l_uRec1Statc+1)!=g_Usart4_Rx_Sta){				
//					l_uRecNum = 1;
//				}
//				l_uRec1Statc = g_Usart4_Rx_Sta;
//			}else if( 0==(l_uRecNum%3) ){
//				if( (l_uRec1Statc+1)!=g_Usart4_Rx_Sta ){
//					l_uRecNum = 1;
//					l_uRec1Statc = g_Usart4_Rx_Sta;
//				}else{				
//					l_uRecNum = 0;
//					OSSemPost( (OS_SEM *)&g_TjcTouchsem,OS_OPT_POST_NO_SCHED,&err );  /* 释放触摸事件信号量 */
//					g_uRecAutoDownTime = 0;       /* 自动关机时间清零 */
//				}
//			}		
//		}
//		
//		if(g_Usart4_Rx_Sta>(USART4_REC_LEN-1)){ 
//			g_Usart4_Rx_Sta=0;//接收数据错误,重新开始接收
//		}	
//#if DOWN_TJC_BIN		
//	}else{
//		USART_SendData( USART1,Res );
//	}
//#endif	
//#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//#endif
