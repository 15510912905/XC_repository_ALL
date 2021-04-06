#ifndef _DRV_TJC4832T_H_
#define _DRV_TJC4832T_H_ 

#include "Task.h"

#define TJC_RED           (63488)
#define TJC_GREEN         (2016)
#define TJC_YELLOW        (65504)
#define TJC_1_GREEN       (1024)
#define TJC_WHITE         (65535)

uint8_t uTjc4832tSetPage( uint8_t uPage );
int16_t uTjc4832tGetPage( void );
uint8_t uTjc4832tSetBackLight( uint8_t uBackLight );
uint8_t uTjc4832tSetSleep( uint8_t uSleepOnOff );
uint8_t uTjc4832tSetWakup( uint8_t uWakup );
uint8_t uTjc4832tReset( void );
uint8_t uTjc4832tSetLableValue( uint8_t page_id,uint8_t control_id,uint8_t *str);
uint8_t uTjc4832tSetButterValue( uint8_t page_id,uint8_t control_id,uint8_t *str);
uint8_t uTjc4832tSetChexkBox( uint8_t page_id,uint8_t control_id,uint8_t uvale );
uint8_t uTjc4832tSetVariableValue( uint8_t page_id,uint8_t control_id,uint8_t uvale );
uint8_t uTjc4832tClickEvent( uint8_t control_id,uint8_t uevent );
uint8_t uTjc4832tWriterStr( uint16_t uX,uint16_t uY,uint16_t uW,uint16_t uH,uint8_t uFontid,uint16_t uPointcolor,uint16_t uBackcolor,uint8_t uXcenter,uint8_t uYcenter,uint8_t uSta,uint8_t* uString );
uint8_t uTjc4832tFill( uint16_t uX,uint16_t uY,uint16_t uW,uint16_t uH,uint16_t uColor );
uint8_t uTjc4832tDraw( uint16_t uX,uint16_t uY,uint16_t uW,uint16_t uH,uint16_t uColor );
uint8_t uTjc4832tVisObjState( uint8_t page_id,uint8_t control_id,uint8_t uState );
uint8_t uTjc4832tSetNumValue( uint8_t page_id,uint8_t control_id,uint8_t *str);
uint8_t uTjc4832tSetFloatNumValue( uint8_t page_id,uint8_t control_id,uint8_t *str);
uint8_t uTjc4832tSetSwitchValue( uint8_t page_id,uint8_t control_id,uint8_t *str);
uint8_t uTjc4832tSetProgressbarValue( uint8_t page_id,uint8_t control_id,uint8_t value );
uint8_t uTjc4832tTouchSwitch( uint8_t control_id,uint8_t uenable );
uint8_t uTjc4832tPageTextId( uint8_t page_id,uint8_t* pBuf );
uint8_t uTjc4832tTextId( uint8_t control_id,uint8_t* pBuf );
uint8_t uTjc4832tButterId( uint8_t control_id,uint8_t* pBuf );
uint8_t uTjc4832tCheckBoxId( uint8_t control_id,uint8_t* pBuf );
uint8_t uTjc4832tNumId( uint8_t control_id,uint8_t* pBuf );
uint8_t uTjc4832tVariableId( uint8_t control_id,uint8_t* pBuf );
uint8_t uTjc4832tFNumId( uint8_t control_id,uint8_t* pBuf );
uint8_t uTjc4832tSwitchId( uint8_t control_id,uint8_t* pBuf );
uint8_t uTjc4832tScheduleId( uint8_t control_id,uint8_t* pBuf );
uint8_t uTjc4832tSetLableValuePco( uint8_t page_id,uint8_t control_id,uint32_t Color);
uint8_t uTjc4832tTextPcoId( uint8_t control_id,uint8_t* pBuf );
uint8_t uTestTjc4832t( void );

#endif
