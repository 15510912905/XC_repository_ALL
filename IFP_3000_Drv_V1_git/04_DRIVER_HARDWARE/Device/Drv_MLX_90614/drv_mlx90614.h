#ifndef DRV_MLX90614_H
#define DRV_MLX90614_H
#include "stm32f10x.h"

#define ACK           0
#define NACK          1
#define SA            0x00 //Slave address single MLX90614 address 0x00,multi mlx90614 default address 0x5a
#define RAM_ACCESS    0x00 //RAM access command
#define EEPROM_ACCESS 0x20 //EEPROM access command
#define RAM_TOBJ1     0x07 //To1 address in the eeprom
#define UCEERTIME     1000


#define SMBUS_SDA_PORT          GPIOB
#define SMBUS_SDA_PIN           GPIO_Pin_15


#define SMBUS_SCK_PORT          GPIOB
#define SMBUS_SCK_PIN           GPIO_Pin_13

#define SDA_L GPIO_ResetBits(SMBUS_SDA_PORT,SMBUS_SDA_PIN)
#define SDA_H GPIO_SetBits(SMBUS_SDA_PORT,SMBUS_SDA_PIN)
#define SCL_L GPIO_ResetBits(SMBUS_SCK_PORT,SMBUS_SCK_PIN)
#define SCL_H GPIO_SetBits(SMBUS_SCK_PORT,SMBUS_SCK_PIN)

#define SDA_INPUT  {GPIOB->CRH&=0x0fffffff;GPIOB->CRH|=((uint32_t)8<<28);}
#define SDA_OUTPUT {GPIOB->CRH&=0x0fffffff;GPIOB->CRH|=((uint32_t)3<<28);}
//#define SDA_INPUT  {GPIOB->CRH&=0x0fffffff;GPIOB->CRH|=(0x80<<24);}
//#define SDA_OUTPUT {GPIOB->CRH&=0x0fffffff;GPIOB->CRH|=(0x30<<24);}

void Mlx96014_Configuration(void);
void SMBus_StartBit(void);
void SMBus_StopBit(void);
void SMBus_SendBit(uint8_t byte);
uint8_t SMBus_SendByte(uint8_t data);
uint8_t SMBus_ReceiveBit(void);
uint8_t SMBus_ReceiveByte(uint8_t data);
void SMBus_Delay(uint16_t time);
void SMBus_Init(void);
uint16_t SMBus_ReadMemory(uint8_t slave, uint8_t offset);
uint8_t PEC_Calculation(uint8_t pec[]);
float SMBus_ReadTemp(void);                                 //
static void mxldelay_ms(uint16_t time);

#endif
