#include "Func_Dma_Uart.h"

/********************************************************************************************************
** ����: USART1_Init,  ����1��ʼ��
**------------------------------------------------------------------------------------------------------
** ����: ��
** ����: ��											  
********************************************************************************************************/
void USART1_Init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* ��GPIO��USART������ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;		       // �������PA9(TX)
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;    // IO��Ƶ��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	   // �����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);  			   // ��ʼ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;		   // ��������PA10(RX)
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;// ��������
	GPIO_Init(GPIOA,&GPIO_InitStructure); 			   // ��ʼ�� 

	/* ���ô���Ӳ������ */
	USART_InitStructure.USART_BaudRate = bound;    /* ������ */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);    /* ʹ�ܴ��ڿ����ж� */
	USART_ClearFlag(USART1, USART_FLAG_TC | USART_FLAG_IDLE);
	USART_Cmd(USART1, ENABLE);        /* ʹ�ܴ��� */
	/* ���������շ�DMA���� */
	USART_DMACmd(USART1,USART_DMAReq_Tx | USART_DMAReq_Rx,ENABLE);

	/* ʹ�ܴ���1�ж� */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/********************************************************************************************************
** ����: USART1_DMA_Init,  ����1��ʼ���� ���ô���1��DMA��������DMA�����жϡ�
**------------------------------------------------------------------------------------------------------
** ����: ��
** ����: ��											  
********************************************************************************************************/
void USART1_DMA_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	/* ��DMAͨ��ʱ�� */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	DMA_DeInit(DMA1_Channel4);//TX ͨ��
	DMA_DeInit(DMA1_Channel5);//RX ͨ��

	/* TX ͨ�� ����*/
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

	/* RX ͨ�� ����*/
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

	/* ʹ��DMA�շ�ͨ�� */
	DMA_Cmd(DMA1_Channel4,ENABLE);
	DMA_Cmd(DMA1_Channel5,ENABLE);

	/* ����û��ʹ��DMA������ɻ��߷�������жϣ�����Ҫ��������������� */
}

void USART4_Init(uint32_t bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;        
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	//����4��ʹ�ùܽ�������붨��
	//����UART4 Tx (PC.10)��Ϊ�����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;         //IO�ڵĵ�2��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO���ٶ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //IO�ڸ����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);            //��ʼ������1���IO��	
	//���� UART4 Rx (PC.11)Ϊ�������� 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;           //IO�ڵĵ�3��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//IO����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);               //��ʼ������1����IO�� 

	//����4������ʼ�����岿��,����1����Ϊ9600 �� 8 ��1 ��N  �����жϷ�ʽ  
	USART_InitStructure.USART_BaudRate = bound;                  //�趨��������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //�趨��������λ��
	USART_InitStructure.USART_StopBits = USART_StopBits_1;      //�趨ֹͣλ����
	USART_InitStructure.USART_Parity = USART_Parity_No ;        //����У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                //ʹ�ý��պͷ��͹���	
	USART_Init(UART4, &USART_InitStructure);      //��ʼ������4	

	USART_ITConfig(UART4, USART_IT_IDLE,ENABLE);  //ʹ�ܴ���4�����ж�	
	USART_ClearFlag(UART4, USART_FLAG_TC|USART_FLAG_IDLE );        // ���־(������) 
	USART_Cmd(UART4, ENABLE);                     //ʹ�ܴ���4
	/* ���������շ�DMA���� */	
	USART_DMACmd(UART4, USART_DMAReq_Tx | USART_DMAReq_Rx, ENABLE);

	//ʹ�ܴ���4�ж�
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
 }

void USART4_DMA_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;	 //����DMA��ʼ���ṹ��DMA_InitStructure 
	
	/* ��DMAͨ��ʱ�� */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	
	DMA_DeInit(DMA2_Channel5);	 //Tx����DMA 2ͨ������
	DMA_DeInit(DMA2_Channel3);	 //Rx����DMA 2ͨ������
	
	/* TX ͨ������ */
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
	DMA_Init(DMA2_Channel5, &DMA_InitStructure);	 //��ʼ��
	
	/* RX ͨ������ */
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);	 //�����ַ  
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)g_Usart4_Rx_Buf;	 //�ڴ��ַ  
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	 //������Ϊ����Ŀ�ĵ� 
	DMA_InitStructure.DMA_BufferSize = USART4_REC_LEN;	 //DMA�����С:BufferSize 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	 //�����ַ�Ĵ��������� 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	  	 //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 	//�������ݿ��Ϊ8λ 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;	 //�ڴ����ݿ��Ϊ8λ 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;	 //��������������ģʽ 
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;	 //����DMAͨ�����ȼ�Ϊ�� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	 //��ֹDMAͨ������Ϊ�ڴ����ڴ洫�� 	
	DMA_Init(DMA2_Channel3, &DMA_InitStructure);	 //��ʼ��	 

	/* ʹ��DMA�շ�ͨ�� */
	DMA_Cmd(DMA2_Channel5, ENABLE);
	DMA_Cmd(DMA2_Channel3, ENABLE);
}	


