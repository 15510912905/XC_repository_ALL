/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——P25Q32h模数转换模块

  -------------------------------------------------------
   文 件 名   : Drv_Flash_P25Q32h.c
   版 本 号   : V1.0.0.0
   作    者   : 
   生成日期   : 2020年06月12日
   功能描述   : 
   使用方法   ：
   依赖于     : 
   注         ：该模块不依赖于硬件电路,使用了硬件SPI。 
 ********************************************************/

#include "Drv_Flash_P25Q32h.h"
#include "Func_IFP_300_Drv.h"

//uint16_t g_SpiFlashType=W25Q128J;   //默认就是
//uint8_t g_SpiFlashBuf[4096];

DRV_FLASH_P25Q32H_TYPE* _gp_FlashP25Q32hUnits[FLASH_P25Q32H_BUTT] = {0};	/*P25Q32h模数转换模块的注册表*/

//SPI1的初始化结构体
SPI_InitTypeDef  SPI_InitStructure;

///* 接口函数
// ********************************************************/

/* 初始化Flash_P25Q32h模块
  -----------------------------
  入口：Flash_P25Q32h模块的ID号，SPI端口编号，引脚端口号
  返回值：初始化好的AD7685模块结构体
*/
DRV_FLASH_P25Q32H_TYPE* Drv_FlashP25Q32hInit( DRV_FLASH_P25Q32H_ENUM id,BSP_SPI_ENUM spi_number,uint32_t theta, \
								              BSP_PORT_ENUM nss_port_number, BSP_PIN_ENUM nss_pin_number, \
								              BSP_PORT_ENUM sck_port_number, BSP_PIN_ENUM sck_pin_number, \
								              BSP_PORT_ENUM miso_port_number, BSP_PIN_ENUM miso_pin_number, \
								              BSP_PORT_ENUM mosi_port_number, BSP_PIN_ENUM mosi_pin_number )
{	
	DRV_FLASH_P25Q32H_TYPE* p_unit = (DRV_FLASH_P25Q32H_TYPE*)calloc(1, sizeof(DRV_FLASH_P25Q32H_TYPE));	/*申请内存*/

	/*分配失败返回NULL*/
	if(p_unit == NULL)
	{
		return NULL;
	}
		
	/*id错误返回NULL*/
	if(id>=FLASH_P25Q32H_BUTT)
	{
		free(p_unit); 
		return NULL;
	}
	
	/*如果当前模块存在，取消分配新存储区*/
	if(_gp_FlashP25Q32hUnits[id] != NULL)
	{
		free(p_unit);
		p_unit = _gp_FlashP25Q32hUnits[id];
	}
	else
	{
		_gp_FlashP25Q32hUnits[id] = p_unit;
	}
	
	/*初始化*/
	
	/*-------------------------------常量*/
	p_unit->id         = id;				/*模块id*/
	p_unit->theta      = theta;             /* 延时调节 */
	
	p_unit->spi_number = spi_number;		/*spi端口编号*/
	p_unit->nss_port_number = nss_port_number;
	p_unit->nss_pin_number = nss_pin_number;

	/* 硬件SPI */
	BSP_InitSpiMaster8Bit( spi_number, \
				           nss_port_number, nss_pin_number, \
				           sck_port_number, sck_pin_number, \
				           miso_port_number, miso_pin_number, \
				           mosi_port_number, mosi_pin_number );
	
	//uSPI1_ReadWriteByte(p_unit->spi_number,0xff);

	/*-------------------------------变量*/
	p_unit->status     = FLASH_P25Q32H_READY;
//	p_unit->tx_buffer  = 0;
//	p_unit->rx_buffer  = 0;
		
	return p_unit;
}

//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
static uint16_t uSPI1_ReadWriteByte(BSP_SPI_ENUM BspNum,uint8_t TxData)
{	
	CPU_SR_ALLOC();                                             /*申请临界区变量*/	
	uint16_t retry = 0;
	uint16_t uRecData = 0; 
	
	OS_CRITICAL_ENTER();  		                    /* 以下必须考虑临界资源的问题 */
	
	while (BSP_SpiGetStatus(BspNum,TXE_STATUS) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		retry++;
		if(retry>W25x_DELAY){
			return 0;
		}
	}			  
	BSP_SpiSendData(BspNum, TxData);        //通过外设SPIx发送一个数据
	retry=0;

	while (BSP_SpiGetStatus(BspNum,RXNE_STATUS) == RESET)//检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		retry++;
		if(retry>W25x_DELAY){
			return 0;
		}
	}		
	uRecData = BSP_SpiReceiveData(BspNum); //返回通过SPIx最近接收的数据		
	
	OS_CRITICAL_EXIT();                            /* 以上必须考虑临界资源的问题 */		
	
	return uRecData;
}

//读取芯片ID W25X16的ID:0XEF14
uint16_t uSPI_FlashReadID(DRV_FLASH_P25Q32H_TYPE *p_unit)
{
	uint16_t Temp = 0;	
	
	BSP_SpiNssSet(p_unit->nss_port_number, p_unit->nss_pin_number,NSS_LOW);      /* SPI_FLASH_CS_EN; */
	
	uSPI1_ReadWriteByte(p_unit->spi_number,W25X_ManufactDeviceID);               //发送读取ID命令	    /* 	SPI1_ReadWriteByte(0x94);//发送读取ID命令	// */
	uSPI1_ReadWriteByte(p_unit->spi_number,W25X_NULL); 	    
	uSPI1_ReadWriteByte(p_unit->spi_number,W25X_NULL); 	    
	uSPI1_ReadWriteByte(p_unit->spi_number,W25X_NULL); 	 		
	Temp|=uSPI1_ReadWriteByte(p_unit->spi_number,W25X_FULL)<<8;  
	Temp|=uSPI1_ReadWriteByte(p_unit->spi_number,W25X_FULL);
	
	BSP_SpiNssSet(p_unit->nss_port_number, p_unit->nss_pin_number,NSS_HIGH);     /* SPI_FLASH_CS_DIS; */
			    
	return Temp;
} 


/*-------------------------------------------------------------------------------------------------------------------------------------------*/
//初始化SPI FLASH的IO口
void SPI_Flash_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;              //SPI CS
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //复用推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	SPI1_Init();		                                  //初始化SPI
	SPI1_SetSpeed( SPI_BaudRatePrescaler_2 );	          //设置为36M时钟,高速模式  
	
//	g_SpiFlashType=SPI_Flash_ReadID();                    //读取FLASH ID.
}  
/*
//以下是SPI模块的初始化代码，配置成主机模式，访问SD Card/W25X16/24L01/JF24C							  
//SPI口初始化
//这里针是对SPI1的初始化
//1 page = 256byte
//1 sector = 4k
//1 block = 64k
//1 chip = 4M
//1 chip = 64 block
//1 chip = 1024 sector
//1 chip = 16384 page
*/
void SPI1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                             //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;          //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		                        //设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		                    //设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		                            //选择了串行时钟的稳态:时钟悬空高
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	                            //数据捕获于第二个时钟沿
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		                            //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;	     	//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                        //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	                                //CRC值计算的多项式
	SPI_Init(SPI1, &SPI_InitStructure);                                         //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设
	
	SPI1_ReadWriteByte(0xff);//启动传输		 
}

//SPI 速度设置函数
//SpeedSet:
//SPI_BaudRatePrescaler_2   2分频   (SPI 36M@sys 72M)
//SPI_BaudRatePrescaler_8   8分频   (SPI 9M@sys 72M)
//SPI_BaudRatePrescaler_16  16分频  (SPI 4.5M@sys 72M)
//SPI_BaudRatePrescaler_256 256分频 (SPI 281.25K@sys 72M)  
void SPI1_SetSpeed(u8 SpeedSet)
{
	SPI_InitStructure.SPI_BaudRatePrescaler = SpeedSet ;
  	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE);
} 

//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI1_ReadWriteByte(u8 TxData)
{	
	OS_ERR err = OS_ERR_NONE;
	//CPU_SR_ALLOC();                                             /*申请临界区变量*/	
	
	uint8_t uRecError = 0;
	uint16_t retry = 0;
	uint16_t uRecData = 0; 
	
	//OSIntEnter();
	OSMutexPend( (OS_MUTEX *)&g_FlashCom, 0,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err );	              /*等待信号量*/
	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){                                               //检查指定的SPI标志位设置与否:发送缓存空标志位
		retry++;
		if(retry>W25x_DELAY){
			uRecError = EXE_FAILED;
			break;
		}
	}		
	if( EXE_FAILED!=uRecError ){
		SPI_I2S_SendData(SPI1, TxData);                                                                           //通过外设SPIx发送一个数据
		retry=0;
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){                                          //检查指定的SPI标志位设置与否:接受缓存非空标志位	
			retry++;
			if(retry>W25x_DELAY){
				uRecError = EXE_FAILED;
				break;
			}
		}		

		//OS_CRITICAL_ENTER();  		                                                                         /* 以下必须考虑临界资源的问题 */	
		if( EXE_FAILED!=uRecError ){
			uRecData = SPI_I2S_ReceiveData(SPI1);                                                                //返回通过SPIx最近接收的数据	
		}			
	}
	//OS_CRITICAL_EXIT();                                                                                        /* 以上必须考虑临界资源的问题 */	
	OSMutexPost( (OS_MUTEX *)&g_FlashCom,OS_OPT_POST_NO_SCHED,&err );                                            /*释放信号量 */
	//OSIntExit(); 
	
	return uRecData;
}

//读取SPI_FLASH的状态寄存器
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
u8 SPI_Flash_ReadSR(void)   
{  
	u8 byte=0;   
	SPI_FLASH_CS_EN;                           //使能器件   
	SPI1_ReadWriteByte(W25X_ReadStatusReg);    //发送读取状态寄存器命令    
	byte=SPI1_ReadWriteByte(0Xff);             //读取一个字节  
	SPI_FLASH_CS_DIS;                          //取消片选     
	
	return byte;   
} 

//写SPI_FLASH状态寄存器
//只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
void SPI_FLASH_Write_SR(u8 sr)   
{   
	SPI_FLASH_CS_EN;                           //使能器件   
	SPI1_ReadWriteByte(W25X_WriteStatusReg);   //发送写取状态寄存器命令    
	SPI1_ReadWriteByte(sr);                    //写入一个字节  
	SPI_FLASH_CS_DIS;                          //取消片选     	      
}   

//SPI_FLASH写使能	
//将WEL置位   
void SPI_FLASH_Write_Enable(void)   
{
	SPI_FLASH_CS_EN;                            //使能器件   
    SPI1_ReadWriteByte(W25X_WriteEnable);       //发送写使能  
	SPI_FLASH_CS_DIS;                           //取消片选     	      
} 

//SPI_FLASH写禁止	
//将WEL清零  
void SPI_FLASH_Write_Disable(void)   
{  
	SPI_FLASH_CS_EN;                            //使能器件   
    SPI1_ReadWriteByte(W25X_WriteDisable);     //发送写禁止指令    
	SPI_FLASH_CS_DIS;                            //取消片选     	      
} 		

//读取芯片ID W25X16的ID:0XEF14
u16 SPI_Flash_ReadID(void)
{
	u16 Temp = 0;	  
	SPI_FLASH_CS_EN;				    
	SPI1_ReadWriteByte(W25X_ManufactDeviceID);//发送读取ID命令	    /* 	SPI1_ReadWriteByte(0x94);//发送读取ID命令	// */
	SPI1_ReadWriteByte(W25X_NULL); 	    
	SPI1_ReadWriteByte(W25X_NULL); 	    
	SPI1_ReadWriteByte(W25X_NULL); 	 		
	Temp|=SPI1_ReadWriteByte(W25X_FULL)<<8;  
	Temp|=SPI1_ReadWriteByte(W25X_FULL);	 
	SPI_FLASH_CS_DIS;				    
	return Temp;
}   

//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
 	u16 i;    	
	SPI_Flash_Wait_Busy();					       //等待读结束
	
	SPI_FLASH_CS_EN;                               //使能器件   
    SPI1_ReadWriteByte( W25X_ReadData );           //发送读取命令   W25X_FastReadData
	//SPI1_ReadWriteByte( (u8)((ReadAddr)>>24) );  //发送32bit地址   
    SPI1_ReadWriteByte( (u8)((ReadAddr)>>16) );    //发送24bit地址    
    SPI1_ReadWriteByte( (u8)((ReadAddr)>>8) );   
    SPI1_ReadWriteByte( (u8)ReadAddr ); 
	
    for(i=0;i<NumByteToRead;i++){ 
        pBuffer[i]=SPI1_ReadWriteByte(0XFF);   //循环读数  
    }
	
	SPI_FLASH_CS_DIS;                            //取消片选    
	
	SPI_Flash_Wait_Busy();					     //等待读结束
}  

//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	 
u8 SPI_Flash_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
	u8 i = 0;
	u8 uBufferTemp[256] = {0};
#if WRITE_PAGE_ERASE_EN	
	SPI_Flash_Erase_Sector( (WriteAddr/SPIFLASH_PAGE_BASE_ADDR) );
#endif	
	SPI_Flash_Write_Page_Dual( pBuffer,WriteAddr,NumByteToWrite );
	SPI_Flash_Read( uBufferTemp,WriteAddr,NumByteToWrite );
	
	while( (0!=arrcompare((const unsigned char *)uBufferTemp,(const unsigned char *)pBuffer,NumByteToWrite))&&(i<10) ){
#if WRITE_PAGE_ERASE_EN	
		SPI_Flash_Erase_Sector( (WriteAddr/SPIFLASH_PAGE_BASE_ADDR) );
#endif
		SPI_Flash_Write_Page_Dual( pBuffer,WriteAddr,NumByteToWrite );
		SPI_Flash_Read( uBufferTemp,WriteAddr,NumByteToWrite );
		i++;
		if( i>8 ){
#if DEBUH_UART1		
			myprintf( "\r\nSPI_Flash_Write_Error:%08x,%d \r\n",WriteAddr,NumByteToWrite );
#endif	
			vForceWarn();                    /* 提示强制关机 */
			return EXE_FAILED;
		}
	}	
	
	return EXE_SUCCEED;
} 

//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!	
u8 SPI_Flash_Write_PageNoErase(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
	u8 i = 0;
	u8 uBufferTemp[256] = {0};
	
	SPI_Flash_Write_Page_Dual( pBuffer,WriteAddr,NumByteToWrite );
	SPI_Flash_Read( uBufferTemp,WriteAddr,NumByteToWrite );
	
	while( (0!=arrcompare((const unsigned char *)uBufferTemp,(const unsigned char *)pBuffer,NumByteToWrite))&&(i<10) ){
		SPI_Flash_Write_Page_Dual( pBuffer,WriteAddr,NumByteToWrite );
		SPI_Flash_Read( uBufferTemp,WriteAddr,NumByteToWrite );
		i++;
		if( i>8 ){
#if DEBUH_UART1		
			myprintf( "\r\nSPI_Flash_Write_Error:%08x,%d \r\n",WriteAddr,NumByteToWrite );
#endif	
			vForceWarn();                    /* 提示强制关机 */
			return EXE_FAILED;
		}
	}	
	
	return EXE_SUCCEED;
} 

//需要重复写两次才能写正确
void SPI_Flash_Write_Page_Dual(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
	
	SPI_Flash_Wait_Busy();					   //等待写入结束
	
    SPI_FLASH_Write_Enable();                  //SET WEL 
	
	SPI_Flash_Wait_Busy();					   //等待写入结束
	
	SPI_FLASH_CS_EN;                              //使能器件   
    SPI1_ReadWriteByte(W25X_PageProgram);         //发送写页命令 
	//SPI1_ReadWriteByte( (u8)((WriteAddr)>>24) );  //发送32bit地址 
    SPI1_ReadWriteByte((u8)((WriteAddr)>>16));    //发送24bit地址    
    SPI1_ReadWriteByte((u8)((WriteAddr)>>8));   
    SPI1_ReadWriteByte((u8)WriteAddr);  
	
    for(i=0;i<NumByteToWrite;i++){
		SPI1_ReadWriteByte(pBuffer[i]);  
	}
	
	SPI_FLASH_CS_DIS;                            //取消片选 
	SPI_Flash_Wait_Busy();					   //等待写入结束
} 

//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
uint8_t SPI_Flash_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 	
	uint8_t uRecError = 0;
	u16 pageremain;	   
	
	pageremain=256-WriteAddr%256;                             //单页剩余的字节数		
	
	if(NumByteToWrite<=pageremain){
		pageremain=NumByteToWrite;                            //不大于256个字节
	}
	
#if WRITE_PAGE_ERASE_EN	
	SPI_Flash_Erase_Sector( (WriteAddr/SPIFLASH_PAGE_BASE_ADDR) );
#endif	
	
	while(1){	   
		uRecError = SPI_Flash_Write_PageNoErase(pBuffer,WriteAddr,pageremain);

		if( EXE_FAILED==uRecError ){
			break;
		}
		if(NumByteToWrite==pageremain){
			break;                                            //写入结束了
	 	}else{                                                //NumByteToWrite>pageremain
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	
			NumByteToWrite-=pageremain;			              //减去已经写入了的字节数
			if(NumByteToWrite>256){
				pageremain=256;                               //一次可以写入256个字节
			}
			else{ 
				pageremain=NumByteToWrite; 	                  //不够256个字节了
			}
		}
	};	
	return uRecError;
} 

//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)  	
uint8_t SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
	uint8_t uRecError = 0;
	u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;    
	uint8_t* puSpiFlashBuf = NULL;
	
	puSpiFlashBuf = calloc( 4096,sizeof(uint8_t) );
	if( NULL!=puSpiFlashBuf ){	
		secpos=WriteAddr/4096;                                                         //扇区地址 0~511 for w25x16
		secoff=WriteAddr%4096;                                                         //在扇区内的偏移
		secremain=4096-secoff;                                                         //扇区剩余空间大小   
															               
		if(NumByteToWrite<=secremain){                                                 
			secremain=NumByteToWrite;                                                  //不大于4096个字节
		}                                                                              
		while(1){	                                                                           
			SPI_Flash_Read(puSpiFlashBuf,secpos*4096,4096);                            //读出整个扇区的内容
			for(i=0;i<secremain;i++){                                                  //校验数据		                                                           
				if(puSpiFlashBuf[secoff+i]!=0XFF){                                     
					break;                                                             //需要擦除  	  
				}                                                                      
			}                                                                          
			if(i<secremain){                                                           //需要擦除	                                                              
				SPI_Flash_Erase_Sector(secpos);                                        //擦除这个扇区
#if DEBUH_UART1	
	#if PRIVATE_UART1	
				myprintf( "Write Erase Sector: %d \r\n",secpos );
	#endif	
#endif
				for(i=0;i<secremain;i++){	                                           //复制
					puSpiFlashBuf[i+secoff]=pBuffer[i];	  
				}
				uRecError = SPI_Flash_Write_NoCheck(puSpiFlashBuf,secpos*4096,4096);   //写入整个扇区  
			}else{ 
				uRecError = SPI_Flash_Write_NoCheck(pBuffer,WriteAddr,secremain);      //写已经擦除了的,直接写入扇区剩余区间. 		
			}	
			if( EXE_FAILED==uRecError ){
				break;
			}
			if(NumByteToWrite==secremain){
				break;                                                                 //写入结束了
			}else{                                                                     //写入未结束	
				secpos++;                                                              //扇区地址增1
				secoff=0;                                                              //偏移位置为0 	 
																		               
				pBuffer+=secremain;                                                    //指针偏移
				WriteAddr+=secremain;                                                  //写地址偏移	   
				NumByteToWrite-=secremain;				                               //字节数递减
				if(NumByteToWrite>4096){                                               
					secremain=4096;	                                                   //下一个扇区还是写不完
				}else{                                                                 
					secremain=NumByteToWrite;			                               //下一个扇区可以写完了
				}
			}	 
		};	
		
		free( puSpiFlashBuf );
	}else{
#if DEBUH_UART1	
	#if PRIVATE_UART1
		myprintf( "puSpiFlashBuf \r\n" );
	#endif	
#endif
	}
	
	return uRecError;
}

//擦除整个芯片
//整片擦除时间:
//W25X16:25s 
//W25X32:40s 
//W25X64:40s 
//等待时间超长...
void SPI_Flash_Erase_Chip(void)   
{                                             
    SPI_FLASH_Write_Enable();                  //SET WEL 
    SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS_EN;                            //使能器件   
    SPI1_ReadWriteByte(W25X_ChipErase);        //发送片擦除命令  
	SPI_FLASH_CS_DIS;                            //取消片选     	      
	SPI_Flash_Wait_Busy();   				   //等待芯片擦除结束
} 

//擦除一个扇区
//Dst_Addr:扇区地址 0~511 for w25x16
//擦除一个山区的最少时间:150ms
void SPI_Flash_Erase_Sector(u32 Dst_Addr)   
{   
	Dst_Addr*=4096;
	
    SPI_FLASH_Write_Enable();                  //SET WEL 	 
    SPI_Flash_Wait_Busy();   
  	SPI_FLASH_CS_EN;                            //使能器件   
    SPI1_ReadWriteByte(W25X_SectorErase);      //发送扇区擦除指令 
    SPI1_ReadWriteByte((u8)((Dst_Addr)>>16));  //发送24bit地址    
    SPI1_ReadWriteByte((u8)((Dst_Addr)>>8));   
    SPI1_ReadWriteByte((u8)Dst_Addr);  
	SPI_FLASH_CS_DIS;                            //取消片选     	      
    SPI_Flash_Wait_Busy();   				   //等待擦除完成
} 

//等待空闲
void SPI_Flash_Wait_Busy(void)   
{   
	while((SPI_Flash_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
}  

//进入掉电模式
void SPI_Flash_PowerDown(void)   
{
	OS_ERR err;
	
  	SPI_FLASH_CS_EN;                            //使能器件   
    SPI1_ReadWriteByte(W25X_PowerDown);         //发送掉电命令  
	SPI_FLASH_CS_DIS;                           //取消片选
	
    OSTimeDlyHMSM(0, 0, 0, 30,OS_OPT_TIME_HMSM_STRICT,&err);	            //等待TPD  
}  

//唤醒
void SPI_Flash_WAKEUP(void)   
{  
	OS_ERR err;
	
  	SPI_FLASH_CS_EN;                             //使能器件   
    SPI1_ReadWriteByte(W25X_ReleasePowerDown);   //  send W25X_PowerDown command 0xAB    
    SPI_FLASH_CS_DIS;                            //取消片选     
	
    OSTimeDlyHMSM(0, 0, 0, 30,OS_OPT_TIME_HMSM_STRICT,&err);                 //等待TRES1
}   





