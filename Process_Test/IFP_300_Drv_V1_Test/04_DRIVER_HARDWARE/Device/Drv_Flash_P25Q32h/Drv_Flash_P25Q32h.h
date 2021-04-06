/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

			嵌入式开发平台——AD7685模数转换模块

  -------------------------------------------------------
   文 件 名   : Drv_Flash_P25Q32h.h
   版 本 号   : V1.0.0.0
   作    者   :  
   生成日期   : 
   功能描述   : 
   使用方法   ：
   依赖于     : 
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/
 
#ifndef _DRV_FLASH_P25Q32H_H_
#define _DRV_FLASH_P25Q32H_H_

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "BSP_Spi.h"
#include "Drv_SimulateSpi.h"

//#define DUMMY   0xFFFF
#define W25Q64 	  (0XEF16)
#define W25Q128J  (0xEF17) //
#define P25Q32H   (0x8515)
//extern uint16_t g_SpiFlashType;		//定义我们使用的flash芯片型号	
//extern uint8_t g_SpiFlashBuf[4096];

#define	SPI_FLASH_CS_EN   (GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET))//(*((volatile unsigned long  *)(0x00000001)))//PAout(2)  //选中FLASH	
#define	SPI_FLASH_CS_DIS  (GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_SET))  //(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4))//
////////////////////////////////////////////////////////////////////////////

#define SPIFLASH_ADDR_MAX (0x3FFFFF)          /* 最大存储地址 */

#define SPIFLASH_PAGE     (0x0000FF)        //0~255
#define SPIFLASH_SECTOR   (0x000FFF)        //0~4095
#define SPIFLASH_BLOCK    (0x00FFFF)        //0~65535

//W25X16读写
#define FLASH_ID 0XEF14
//指令表
#define W25X_NULL		        (0x00)
#define W25X_FULL		        (0xff)
#define W25X_WriteEnable		(0x06)
#define W25X_WriteDisable		(0x04)
#define W25X_ReadStatusReg		(0x05)
#define W25X_WriteStatusReg		(0x01)
#define W25X_READ_2_STATUS_REG	(0x35)
#define W25X_WRITE_2_STATUS_REG	(0x31)
#define W25X_READ_3_STATUS_REG	(0x15)
#define W25X_WRITE_3_Status_Reg	(0x11)
#define W25X_ReadData			(0x03)
#define W25X_FastReadData		(0x0B)
#define W25X_FastReadDual		(0x3B)
#define W25X_PageProgram		(0x02)
#define W25X_BlockErase			(0xD8)
#define W25X_SectorErase		(0x20)
#define W25X_ChipErase			(0xC7)
#define W25X_PowerDown			(0xB9)
#define W25X_ReleasePowerDown	(0xAB)
#define W25X_DeviceID			(0xAB)
#define W25X_ManufactDeviceID	(0x90)
#define W25X_JedecDeviceID		(0x9F)

#define W25x_DELAY              (500)  /* (500) */

#define WRITE_PAGE_ERASE_EN     (1) 

/*Flash_P25Q32h模块枚举*/
typedef enum{
	FLASH_P25Q32H_1 = 0,
	FLASH_P25Q32H_2 = 1,
	FLASH_P25Q32H_BUTT
} DRV_FLASH_P25Q32H_ENUM;

/*Flash_P25Q32h模块状态枚举*/
typedef enum{
	FLASH_P25Q32H_UNDEFINED = 0,				/*未初始化*/
	FLASH_P25Q32H_READY  = 1					/*可用*/
} DRV_FLASH_P25Q32H_STATUS_ENUM;

/*Flash_P25Q32h模块结构体*/
typedef struct{
	/*------------------------------变量*/
	
	DRV_FLASH_P25Q32H_STATUS_ENUM status;			/*该模块的状态*/
//	uint16_t tx_buffer;						        /*发送缓存*/
//	uint16_t rx_buffer;						        /*接收缓存*/
	/*------------------------------变常*/
	/*------------------------------常量*/
	DRV_FLASH_P25Q32H_ENUM id;						/*AD7685*/
	uint32_t theta;							/*时钟速度参数*/
	
	BSP_SPI_ENUM spi_number;				/*spi接口编号*/
	BSP_PORT_ENUM nss_port_number; 
	BSP_PIN_ENUM nss_pin_number;	
	//DRV_SOFTWARE_SPI_TYPE* SW_SPI;       /* 软件SPI */
} DRV_FLASH_P25Q32H_TYPE;

///* 接口函数
// ********************************************************/

/* 初始化Flash_P25Q32h模块
  -----------------------------
  入口：Flash_P25Q32h模块的ID号，SPI端口编号，引脚端口号
  返回值：初始化好的Flash_P25Q32h模块结构体
*/
extern DRV_FLASH_P25Q32H_TYPE* Drv_FlashP25Q32hInit( DRV_FLASH_P25Q32H_ENUM id,BSP_SPI_ENUM spi_number,uint32_t theta, \
								                     BSP_PORT_ENUM nss_port_number, BSP_PIN_ENUM nss_pin_number, \
								                     BSP_PORT_ENUM sck_port_number, BSP_PIN_ENUM sck_pin_number, \
								                     BSP_PORT_ENUM miso_port_number, BSP_PIN_ENUM miso_pin_number, \
								                     BSP_PORT_ENUM mosi_port_number, BSP_PIN_ENUM mosi_pin_number );

static uint16_t uSPI1_ReadWriteByte(BSP_SPI_ENUM BspNum,uint8_t TxData);
uint16_t uSPI_FlashReadID(DRV_FLASH_P25Q32H_TYPE *p_unit);

void SPI1_Init(void);			 //初始化SPI口
void SPI1_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI总线读写一个字节

void SPI_Flash_Init(void);
u16  SPI_Flash_ReadID(void);  	    //读取FLASH ID
u8	 SPI_Flash_ReadSR(void);        //读取状态寄存器 
void SPI_FLASH_Write_SR(u8 sr);  	//写状态寄存器
void SPI_FLASH_Write_Enable(void);  //写使能 
void SPI_FLASH_Write_Disable(void);	//写保护
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //读取flash
uint8_t SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//写入flash
void SPI_Flash_Erase_Chip(void);    	  //整片擦除
void SPI_Flash_Erase_Sector(u32 Dst_Addr);//扇区擦除
void SPI_Flash_Wait_Busy(void);           //等待空闲
void SPI_Flash_PowerDown(void);           //进入掉电模式
void SPI_Flash_WAKEUP(void);			  //唤醒
uint8_t SPI_Flash_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);

u8 SPI_Flash_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
u8 SPI_Flash_Write_PageNoErase(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
void SPI_Flash_Write_Page_Dual(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);


#endif
