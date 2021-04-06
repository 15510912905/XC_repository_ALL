//
// 版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
//-------------------------------------------------------
//
//		嵌入式开发平台——XC2000液压检测功能定义
//
//-------------------------------------------------------
// 文 件 名   : Func_XC2000_Liquid_Pressure.cpp
// 版 本 号   : V1.0.0.0
// 作    者   : ryc
// 生成日期   : 2020年04月22日
// 功能描述   : XC2000液压检测功能定义
// 依赖于     : 
//
 
#ifndef _FUNC_IFP_300_DRV_H_
#define _FUNC_IFP_300_DRV_H_

//------------------------------------------------------
// 头文件												
//------------------------------------------------------
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "stm32f10x.h"
#include "sys.h"
#include "BSP_Sys.h"
#include "BSP_Gpio.h"
#include "BSP_Uart.h"
#include "BSP_Adc.h"
#include "BSP_Timer.h"
#include "BSP_Spi.h"
#include "os.h"
#include "includes.h"
#include "Drv_StepMotor.h"
#include "Drv_PWM_TimerDriven.h"
#include "Drv_AT24C32.h"
#include "Drv_MAX5402EUA.h"
#include "Drv_SimulateSpi.h"
#include "Drv_Flash_P25Q32h.h"
#include "Drv_HardAD7685.h"
#include "Drv_AD7685.h"
#include "Drv_HardMAX5402EUA.h"
#include "Drv_Tjc4832t.h"
#include "Drv_WIFIE103W01.h"
#include "drv_mlx90614.h"
#include "Drv_Bluetooth.h"
#include "Func_Config.h"
#include "Func_Common.h"
#include "Func_MA1100_User_Interface.h"
#include "Func_Motor.h"
#include "Func_WIFIE103W01.h"
#include "Func_LogIn.h"
#include "Func_Time.h"
#include "Func_BarCode.h"
#include "Func_BarCode_2.h"
#include "Func_Tjc4832t.h"
#include "Func_Ansi.h"
#include "Func_Lis.h"
#include "Func_Bluetooth.h"
#include "Func_Electric.h"
#include "Func_TjcBootloader.h"
#include "Func_Dma_Uart.h"

#include "led.h"
#include "Global_Variable.h"

//#include "Drv_CANProtocol.h"
//#include "Drv_U4525DO5BK.h"
//#include "Prt_CmdRegedit.h"
//#include "Drv_AD7685.h"
//#include "Func_ADHandler.h"

//#include "Func_GY_K950E.h"
//#include "Func_Wk_Up.h"
//#include "Func_Error.h"
//#include "Drv_HardAD7685.h"

//#include "Func_Flash_P25Q32h.h"
//#include "Func_GY_K950E.h"
//#include "time.h"

#define UART1_BAUD_RATE             (115200)//(115200)
#define UART4_BAUD_RATE             (115200)
#define UART2_BAUD_RATE             (115200) 
#define UART3_BAUD_RATE             (115200)

//#define UART1_BAUD_RATE             (256000)
//#define UART4_BAUD_RATE             (256000)
//#define UART2_BAUD_RATE             (256000)
//#define UART3_BAUD_RATE             (256000)

#define AT24C32_ID_ADDR             (0xA0)
#define AT24C32_EEP_ADDR            (0xA2)

#define LED_GLOW_CONTORL_PORT       (_PA_)
#define LED_GLOW_CONTORL_PIN        (_P15_)
#define LED_GLOW_CONTORL_TRUE       (1)
#define LED_GLOW_CONTORL_FALSE      (0)
#define LED_GLOW_CONTORL_OUT        PAout(15)

#define BUZZER_CONTORL_PORT         (_PB_)
#define BUZZER_CONTORL_PIN          (_P9_)
#define BUZZER_CONTORL_TRUE         (1)
#define BUZZER_CONTORL_FALSE        (0)
#define BUZZER_CONTORL_OUT          PBout(9)

#define MOTOR_SLEEP_PORT            (_PB_)
#define MOTOR_SLEEP_PIN             (_P1_)
#define MOTOR_SLEEP_TRUE            (1)
#define MOTOR_SLEEP_FALSE           (0)

#define MOTOR_EN_PORT               (_PC_)
#define MOTOR_EN_PIN                (_P8_)
#define MOTOR_EN_TRUE               (1)
#define MOTOR_EN_FALSE              (0)
                                    
#define MOTOR_DIR_PORT              (_PC_)
#define MOTOR_DIR_PIN               (_P9_)
#define MOTOR_DIR_TRUE              (0)//(1)
#define MOTOR_DIR_FALSE             (1)//(0)
                                    
#define MOTOR_STEP_PORT             (_PC_)
#define MOTOR_STEP_PIN              (_P7_)
#define MOTOR_STEP_TRUE             (1)
#define MOTOR_STEP_FALSE            (0)

#define MOTOR_RESET_PORT            (_PC_)
#define MOTOR_RESET_PIN             (_P2_)
#define MOTOR_RESET_TRUE            (1)
#define MOTOR_RESET_FALSE           (0)
#define MOTOR_RESET_IN              PCin(2)
                                    
#define LCD_INT_PORT                (_PC_)
#define LCD_INT_PIN                 (_P13_)
#define LCD_INT_TRUE                (1)
#define LCD_INT_FALSE               (0)

#define LCD_IIC_SDA_PORT            (_PA_)
#define LCD_IIC_SDA_PIN             (_P12_)
#define LCD_IIC_SDA_TRUE            (1)
#define LCD_IIC_SDA_FALSE           (0)
                                    
#define LCD_IIC_CLK_PORT            (_PA_)
#define LCD_IIC_CLK_PIN             (_P11_)
#define LCD_IIC_CLK_TRUE            (1)
#define LCD_IIC_CLK_FALSE           (0)
                                    
#define ID_IIC_SDA_PORT             (_PA_)
#define ID_IIC_SDA_PIN              (_P12_)
#define ID_IIC_SDA_TRUE             (1)
#define ID_IIC_SDA_FALSE            (0)
                                    
#define ID_IIC_CLK_PORT             (_PA_)
#define ID_IIC_CLK_PIN              (_P11_)
#define ID_IIC_CLK_TRUE             (1)
#define ID_IIC_CLK_FALSE            (0)
                                    
#define ID_DETECT_PORT              (_PA_)
#define ID_DETECT_PIN               (_P8_)
#define ID_DETECT_TRUE              (1)
#define ID_DETECT_FALSE             (0)
#define ID_DETECT_IN                PAin(8)
                                    
#define EEP_IIC_SDA_PORT            (_PB_)
#define EEP_IIC_SDA_PIN             (_P8_)
#define EEP_IIC_SDA_TRUE            (1)
#define EEP_IIC_SDA_FALSE           (0)
                                    
#define EEP_IIC_CLK_PORT            (_PB_)
#define EEP_IIC_CLK_PIN             (_P9_)
#define EEP_IIC_CLK_TRUE            (1)
#define EEP_IIC_CLK_FALSE           (0)

#define P25Q32H_SPI_SDI_PORT        (_PA_)
#define P25Q32H_SPI_SDI_PIN         (_P6_)
#define P25Q32H_SPI_SDI_TRUE        (1)
#define P25Q32H_SPI_SDI_FALSE       (0)
                                    
#define P25Q32H_SPI_SDO_PORT        (_PA_)
#define P25Q32H_SPI_SDO_PIN         (_P7_)
#define P25Q32H_SPI_SDO_TRUE        (1)
#define P25Q32H_SPI_SDO_FALSE       (0)
                                    
#define P25Q32H_SPI_CLK_PORT        (_PA_)
#define P25Q32H_SPI_CLK_PIN         (_P5_)
#define P25Q32H_SPI_CLK_TRUE        (1)
#define P25Q32H_SPI_CLK_FALSE       (0)
                                    
#define P25Q32H_SPI_CS_PORT         (_PA_)
#define P25Q32H_SPI_CS_PIN          (_P4_)
#define P25Q32H_SPI_CS_TRUE         (1)
#define P25Q32H_SPI_CS_FALSE        (0)
                                    
#define AD7685_SPI_SDI_PORT         (_PB_)
#define AD7685_SPI_SDI_PIN          (_P14_)
#define AD7685_SPI_SDI_TRUE         (1)
#define AD7685_SPI_SDI_FALSE        (0)

#define AD7685_SPI_CLK_PORT         (_PB_)
#define AD7685_SPI_CLK_PIN          (_P13_)
#define AD7685_SPI_CLK_TRUE         (1)
#define AD7685_SPI_CLK_FALSE        (0)

#define AD7685_SPI_CS_PORT          (_PB_)
#define AD7685_SPI_CS_PIN           (_P12_)
#define AD7685_SPI_CS_TRUE          (1)
#define AD7685_SPI_CS_FALSE         (0)

#define MAX5402_SPI_SDI_PORT        (_PA_)
#define MAX5402_SPI_SDI_PIN         (_P6_)
#define MAX5402_SPI_SDI_TRUE        (1)
#define MAX5402_SPI_SDI_FALSE       (0)
                                    
#define MAX5402_SPI_SDO_PORT        (_PA_)
#define MAX5402_SPI_SDO_PIN         (_P7_)
#define MAX5402_SPI_SDO_TRUE        (1)
#define MAX5402_SPI_SDO_FALSE       (0)
                                    
#define MAX5402_SPI_CLK_PORT        (_PA_)
#define MAX5402_SPI_CLK_PIN         (_P5_)
#define MAX5402_SPI_CLK_TRUE        (1)
#define MAX5402_SPI_CLK_FALSE       (0)
                                    
#define MAX5402_SPI_CS_PORT         (_PC_)
#define MAX5402_SPI_CS_PIN          (_P5_)
#define MAX5402_SPI_CS_TRUE         (1)
#define MAX5402_SPI_CS_FALSE        (0)

#define USART1_TX_PORT              (_PA_)
#define USART1_TX_PIN               (_P9_)
#define USART1_TX_TRUE              (1)
#define USART1_TX_FALSE             (0)
                                    
#define USART1_RX_PORT              (_PA_)
#define USART1_RX_PIN               (_P10_)
#define USART1_RX_TRUE              (1)
#define USART1_RX_FALSE             (0)
                                    
#define USART2_TX_PORT              (_PA_)
#define USART2_TX_PIN               (_P2_)
#define USART2_TX_TRUE              (1)
#define USART2_TX_FALSE             (0)
                                    
#define USART2_RX_PORT              (_PA_)
#define USART2_RX_PIN               (_P3_)
#define USART2_RX_TRUE              (1)
#define USART2_RX_FALSE             (0)
                                    
#define USART3_TX_PORT              (_PB_)
#define USART3_TX_PIN               (_P10_)
#define USART3_TX_TRUE              (1)
#define USART3_TX_FALSE             (0)
                                    
#define USART3_RX_PORT              (_PB_)
#define USART3_RX_PIN               (_P11_)
#define USART3_RX_TRUE              (1)
#define USART3_RX_FALSE             (0)
                                    
#define USART4_TX_PORT              (_PC_)
#define USART4_TX_PIN               (_P10_)
#define USART4_TX_TRUE              (1)
#define USART4_TX_FALSE             (0)
          
#define USART4_RX_PORT              (_PC_)
#define USART4_RX_PIN               (_P11_)
#define USART4_RX_TRUE              (1)
#define USART4_RX_FALSE             (0)

#define HOME_WAK_UP_PORT            (_PA_)
#define HOME_WAK_UP_PIN             (_P0_)
#define HOME_WAK_UP_TRUE            (1)
#define HOME_WAK_UP_FALSE           (0)

#define LED_INDI_CONTROL_PORT	    (_PB_)		
#define LED_INDI_CONTROL_PIN	    (_P7_)	
#define LED_INDI_CONTROL_TRUE       (1)
#define LED_INDI_CONTROL_FALSE      (0)
#define LED_INDI_CONTROL_OUT        PBout(7)
 
#define POWER3_CONTROL_PORT         (_PB_)
#define POWER3_CONTROL_PIN          (_P6_)
#define POWER3_CONTROL_TRUE         (1)
#define POWER3_CONTROL_FALSE        (0)
#define POWER3_CONTROL_OUT          PBout(6)
                                    
#define POWER5_CONTROL_PORT         (_PB_)
#define POWER5_CONTROL_PIN          (_P5_)
#define POWER5_CONTROL_TRUE         (1)
#define POWER5_CONTROL_FALSE        (0)
#define POWER5_CONTROL_OUT          PBout(5)

#define POWER_CONTROL_PORT          (_PB_)
#define POWER_CONTROL_PIN           (_P2_)
#define POWER_CONTROL_TRUE          (1)
#define POWER_CONTROL_FALSE         (0)
#define POWER_CONTROL_OUT           PBout(2)

#define POWER_AUTO_CONTROL_PORT     (_PB_)
#define POWER_AUTO_CONTROL_PIN      (_P0_)
#define POWER_AUTO_CONTROL_TRUE     (1)
#define POWER_AUTO_CONTROL_FALSE    (0)

#define READCARD_DEC_CONTROL_PORT   (_PA_)
#define READCARD_DEC_CONTROL_PIN    (_P1_)
#define READCARD_DEC_CONTROL_TRUE   (1)
#define READCARD_DEC_CONTROL_FALSE  (0)

#define CHARGE_STATUS_PORT          (_PB_)
#define CHARGE_STATUS_PIN           (_P15_)
#define CHARGE_STATUS_TRUE          (1)
#define CHARGE_STATUS_FALSE         (0)
#define CHARGE_STATUS_IN            PBin(15)

#define WIFI_RST_PORT               (_PC_)
#define WIFI_RST_PIN                (_P3_)
#define WIFI_RST_TRUE               (1)
#define WIFI_RST_FALSE              (0)
#define WIFI_RST_OUT                PCout(3)

#define PG_ADC_PORT                 (_PB_)
#define PG_ADC_PIN                  (_P7_)
#define PG_ADC_TRUE                 (1)
#define PG_ADC_FALSE                (0)
                                    
#define VSENSE_PORT                 (_ADC1_)//(_PC_)
#define VSENSE_PIN                  (_CH14_)//(_P4_)
#define VSENSE_TRUE                 (1)
#define VSENSE_FALSE                (0)

#define BAR_CODE_PORT              (_ADC1_)//(_PC_)
#define BAR_CODE_PIN               (_CH10_)//(_P0_)
#define BAR_CODE_TRUE              (1)
#define BAR_CODE_FALSE             (0)

//#define AD7685_SPI_SDO_PORT      (_PB_)
//#define AD7685_SPI_SDO_PIN       (_P15_)
//#define AD7685_SPI_SDO_TRUE      (1)
//#define AD7685_SPI_SDO_FALSE     (0)

//#define MOTOR_DECAYA_PORT        (_PC_)
//#define MOTOR_DECAYA_PIN         (_P12_)
//#define MOTOR_DECAYA_TRUE        (1)
//#define MOTOR_DECAYA_FALSE       (0)
//#define MOTOR_DECAYA_OUT         PCout(12)
//                                   
//#define MOTOR_DECAYB_PORT        (_PA_)
//#define MOTOR_DECAYB_PIN         (_P15_)
//#define MOTOR_DECAYB_TRUE        (1)
//#define MOTOR_DECAYB_FALSE       (0)
//#define MOTOR_DECAYB_OUT         PAout(15)

//#define ANALOG_IN_PORT           (_PC_)
//#define ANALOG_IN_PIN            (_P0_)
//#define ANALOG_IN_TRUE           (1)
//#define ANALOG_IN_FALSE          (0)

#define MAX5402_INIT_VALUE         (100)
                                   
#define SET_TRUE                   (1)
#define SET_FALSE                  (0)

//------------------------------------------------------
// 模块初始化											
//------------------------------------------------------
bool bFuncPrivateInit1( void );
bool bFuncIFP300UcosValInit( void );
bool bFuncIFP300FlashValInit( void );
bool bFuncFlashP25Q32hInit( void );

//返回值：true，成功；false，失败
//
static bool _bFuncIFP300DrvInit(void);
static bool _bFuncIFP300ModuleInit(void);
static bool _bFuncSteopMotorInit( void );
static bool _bFuncIDCardInit( void );
static bool _bFuncFlashP25Q32hInit( void );
static bool _bFuncMax5402eInit( uint16_t uGain );
static bool _bFuncAd7685Init( void );
static bool _bFuncIFP300SoftWareInit(void);
static bool _bFuncIFP300UcosValInit(void);

#endif
