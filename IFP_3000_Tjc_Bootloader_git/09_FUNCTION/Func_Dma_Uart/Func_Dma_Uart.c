#include "Func_Dma_Uart.h"

/********************************************************************************************************
** 函数: USART1_Init,  串口1初始化
**------------------------------------------------------------------------------------------------------
** 参数: 无
** 返回: 无											  
********************************************************************************************************/
void USART1_Init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* 打开GPIO和USART部件的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* 配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;		       // 串口输出PA9(TX)
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;    // IO口频率
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	   // 复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  			   // 初始化
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;		   // 串口输入PA10(RX)
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;// 浮空输入
	GPIO_Init(GPIOA,&GPIO_InitStructure); 			   // 初始化 

	/* 配置串口硬件参数 */
	USART_InitStructure.USART_BaudRate = bound;    /* 波特率 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);    /* 使能串口空闲中断 */
	USART_ClearFlag(USART1, USART_FLAG_TC | USART_FLAG_IDLE);
	USART_Cmd(USART1, ENABLE);        /* 使能串口 */
	/* 开启串口收发DMA请求 */
	USART_DMACmd(USART1,USART_DMAReq_Tx | USART_DMAReq_Rx,ENABLE);

	/* 使能串口1中断 */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/********************************************************************************************************
** 函数: USART1_DMA_Init,  串口1初始化。 配置串口1的DMA，并开启DMA接收中断。
**------------------------------------------------------------------------------------------------------
** 参数: 无
** 返回: 无											  
********************************************************************************************************/
void USART1_DMA_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	/* 打开DMA通道时钟 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	DMA_DeInit(DMA1_Channel4);//TX 通道
	DMA_DeInit(DMA1_Channel5);//RX 通道

	/* TX 通道 配置*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&g_Usart_Tx_Buf;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 0;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel4,&DMA_InitStructure);

	/* RX 通道 配置*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&g_Usart_Rx_Buf;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = USART_REC_LEN;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5,&DMA_InitStructure);

	/* 使能DMA收发通道 */
	DMA_Cmd(DMA1_Channel4,ENABLE);
	DMA_Cmd(DMA1_Channel5,ENABLE);

	/* 这里没有使用DMA接收完成或者发送完成中断，如需要，可以在这里添加 */
}

void USART4_Init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;        
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	//串口4所使用管脚输出输入定义
	//定义UART4 Tx (PC.10)脚为复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;         //IO口的第2脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //IO口复用推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);            //初始化串口1输出IO口	
	//定义 UART4 Rx (PC.11)为悬空输入 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;           //IO口的第3脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//IO口悬空输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);               //初始化串口1输入IO口 

	//串口4参数初始化定义部分,串口1参数为9600 ， 8 ，1 ，N  接收中断方式  
	USART_InitStructure.USART_BaudRate = bound;                  //设定传输速率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //设定传输数据位数
	USART_InitStructure.USART_StopBits = USART_StopBits_1;      //设定停止位个数
	USART_InitStructure.USART_Parity = USART_Parity_No ;        //不用校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//不用流量控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                //使用接收和发送功能	
	USART_Init(UART4, &USART_InitStructure);      //初始化串口4	

	USART_ITConfig(UART4, USART_IT_IDLE,ENABLE);  //使能串口4接收中断	
	USART_ClearFlag(UART4, USART_FLAG_TC|USART_FLAG_IDLE );        // 清标志(后增加) 
	USART_Cmd(UART4, ENABLE);                     //使能串口4
	/* 开启串口收发DMA请求 */	
	USART_DMACmd(UART4, USART_DMAReq_Tx | USART_DMAReq_Rx, ENABLE);

	//使能串口4中断
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
 }

void USART4_DMA_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;	 //定义DMA初始化结构体DMA_InitStructure 
	
	/* 打开DMA通道时钟 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	
	DMA_DeInit(DMA2_Channel5);	 //Tx重置DMA 2通道配置
	DMA_DeInit(DMA2_Channel3);	 //Rx重置DMA 2通道配置
	
	/* TX 通道配置 */
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&g_Usart4_Tx_Buf;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 0;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA2_Channel5, &DMA_InitStructure);	 //初始化
	
	/* RX 通道配置 */
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);	 //外设地址  
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)g_Usart4_Rx_Buf;	 //内存地址  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	 //外设作为数据目的地 
	DMA_InitStructure.DMA_BufferSize = USART4_REC_LEN;	 //DMA缓存大小:BufferSize 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	 //外设地址寄存器不递增 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	  	 //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 	//外设数据宽度为8位 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;	 //内存数据宽度为8位 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	 //工作在正常缓存模式 
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;	 //设置DMA通道优先级为高 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	 //禁止DMA通道设置为内存至内存传输 	
	DMA_Init(DMA2_Channel3, &DMA_InitStructure);	 //初始化	 

	/* 使能DMA收发通道 */
	DMA_Cmd(DMA2_Channel5, ENABLE);
	DMA_Cmd(DMA2_Channel3, ENABLE);
}	


