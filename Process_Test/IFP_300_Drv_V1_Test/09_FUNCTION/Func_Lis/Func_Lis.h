#ifndef _FUNC_LIS_H_
#define _FUNC_LIS_H_

#include "Func_GY_K950E.h"
#include "Func_IFP_300_Drv.h"

#define  LIS_STX                 (2)
#define  LIS_ETX                 (3)
#define  LIS_EOT                 (4)
#define  LIS_ENQ                 (5)
#define  LIS_ACK                 (6)
				                 
#define  LIS_LF                  (10)
#define  LIS_CR                  (13)
#define  LIS_NAK                 (21)
#define  LIS_MODULUS             (256)

#define  ASCII_ZERO              (48)
#define  ASCII_A1                (55)   /* 10+55=65ΪA */
#define  ASCII_A2                (87)

uint8_t uLisSendTest( void );
uint8_t uLisSendHistory( void );
uint8_t uLisFrameDataPack( uint8_t uFnData,uint8_t* uFrameData,uint32_t uFrameLen );
uint8_t uLisFrameAck( void );

uint8_t uLisSendHistoryPage( const int16_t iPage,uint8_t uOverLoad );

//uint8_t uLisFrameHeardLoad( uint8_t *uLisTemp,const GYK950E *pHistoryTemp );

#endif
	
