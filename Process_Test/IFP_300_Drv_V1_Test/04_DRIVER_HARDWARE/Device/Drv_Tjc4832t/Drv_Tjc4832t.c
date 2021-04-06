#include "Drv_Tjc4832t.h"

/* 设置完页面后不要立即设置别的页面id */
uint8_t uTjc4832tSetPage( uint8_t uPage )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	myprintf( "page %d",uPage );                     /*清除打印缓存各参数恢复为默认值*/	
	myprintf( "\xff\xff\xff" );                      /*清除打印缓存各参数恢复为默认值*/
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	return EXE_SUCCEED;
}

/* 获取当前页面 */
int16_t uTjc4832tGetPage( void )
{
#if	DEBUH_UART4	
	OS_ERR err = OS_ERR_NONE;

	uint8_t uRecUsart = 0;
	
	OSTimeDlyHMSM(0, 0, 0, 120,OS_OPT_TIME_HMSM_STRICT,&err);                       /* 临时增加 */
		
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	myprintf( "sendme" );                            /*清除打印缓存各参数恢复为默认值*/	
	myprintf( "\xff\xff\xff" );                      /*清除打印缓存各参数恢复为默认值*/
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
	
	OSSemPend( (OS_SEM *)&g_GetPageId,200,OS_OPT_PEND_BLOCKING,(CPU_TS *)NULL,( OS_ERR *)&err);	   	       /* 等待获取页面id信号量 不要超过150 */
	if( OS_ERR_NONE==err ){
		return g_RecPageID;
	}else{
		return EXE_SPECIAL_FAILED;
	}	
#endif
	

}

/* 设置背光 */
uint8_t uTjc4832tSetBackLight( uint8_t uBackLight )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	myprintf( "dim=%d",uBackLight );                    /*清除打印缓存各参数恢复为默认值*/	
	myprintf( "\xff\xff\xff" );                         /*清除打印缓存各参数恢复为默认值*/
	
	vEnableUsartPrintf( uRecUsart );                  /* 使能串口1printf */
#endif 
	return 0;
}

/* 睡眠 */
uint8_t uTjc4832tSetSleep( uint8_t uSleepOnOff )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	if( TJC_SLEEP_ON==uSleepOnOff ){
		myprintf( "sleep=1" );                    /*清除打印缓存各参数恢复为默认值*/	
	}else{
		myprintf( "sleep=0" );                    /*清除打印缓存各参数恢复为默认值*/	
	}
	myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	return 0;
}

/* 唤醒 */
uint8_t uTjc4832tSetWakup( uint8_t uWakup )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	myprintf( "wup=%d",uWakup );                         /* 唤醒页面 */	
	myprintf( "\xff\xff\xff" );                          /*清除打印缓存各参数恢复为默认值*/
	
	vEnableUsartPrintf( uRecUsart );                   /* 使能串口1printf */
#endif
	return 0;
}

/* 复位 */
uint8_t uTjc4832tReset( void )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	myprintf( "rest" );                            /* 唤醒页面 */	
	myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	return 0;
}

/* 设置文本内容  */
uint8_t uTjc4832tSetLableValue( uint8_t page_id,uint8_t control_id,uint8_t *str)
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[255] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	uTjc4832tPageTextId( page_id,ucSendBuf );
	Len = strlen( (const char*)ucSendBuf );
	uTjc4832tTextId( control_id,ucSendBuf+Len );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%s",(const char*)str );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%s","\"" );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif	
	return 0;
}

/* 设置文本内容颜色 */
uint8_t uTjc4832tSetLableValuePco( uint8_t page_id,uint8_t control_id,uint32_t Color)
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[255] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	uTjc4832tPageTextId( page_id,ucSendBuf );
	Len = strlen( (const char*)ucSendBuf );
	uTjc4832tTextPcoId( control_id,ucSendBuf+Len );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d",Color );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif	
	return 0;
}

/* 设置按钮内容  */
uint8_t uTjc4832tSetButterValue( uint8_t page_id,uint8_t control_id,uint8_t *str)
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[128] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	uTjc4832tPageTextId( page_id,ucSendBuf );
	Len = strlen( (const char*)ucSendBuf );
	uTjc4832tButterId( control_id,ucSendBuf+Len );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%s",(const char*)str );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%s","\"" );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif	
	return 0;
}

/* 设置复选框值 */
uint8_t uTjc4832tSetChexkBox( uint8_t page_id,uint8_t control_id,uint8_t uvale )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[128] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	uTjc4832tPageTextId( page_id,ucSendBuf );
	Len = strlen( (const char*)ucSendBuf );
	uTjc4832tCheckBoxId( control_id,ucSendBuf+Len );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d",uvale );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;	
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif
	return 0;
}

/* 设置变量值 */
uint8_t uTjc4832tSetVariableValue( uint8_t page_id,uint8_t control_id,uint8_t uvale )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[128] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	uTjc4832tPageTextId( page_id,ucSendBuf );
	Len = strlen( (const char*)ucSendBuf );
	uTjc4832tVariableId( control_id,ucSendBuf+Len );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d",uvale );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
#if DEBUH_UART1
	if( 1==Err ){	
		myprintf( "TjcDataError \r\n" );
	}
#endif	
	return 0;
}

/* 设置点击事件  */
uint8_t uTjc4832tClickEvent( uint8_t control_id,uint8_t uevent )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[128] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	sprintf( (char *)ucSendBuf,"%s","click " );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c%d",control_id,',',uevent );	
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif	
	return 0;
}

/*
red 63488
black 0
全局写字
*/
uint8_t uTjc4832tWriterStr( uint16_t uX,uint16_t uY,uint16_t uW,uint16_t uH,uint8_t uFontid,uint16_t uPointcolor,    \
							uint16_t uBackcolor,uint8_t uXcenter,uint8_t uYcenter,uint8_t uSta,uint8_t* uString )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[255] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  	
	
	sprintf( (char *)ucSendBuf,"xstr " );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uX,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uY,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uW,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uH,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uFontid,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uPointcolor,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uBackcolor,',' );	
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uXcenter,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uYcenter,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uSta,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%c",'\"' );
	Len = strlen( (const char*)ucSendBuf );		
	sprintf( (char *)ucSendBuf+Len,"%s",(const char *)uString );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%c",'\"' );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif
	return 0;
}

/* 填充区域 */
uint8_t uTjc4832tFill( uint16_t uX,uint16_t uY,uint16_t uW,uint16_t uH,uint16_t uColor )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[255] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  	
	
	sprintf( (char *)ucSendBuf,"fill " );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uX,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uY,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uW,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uH,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d",uColor );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif
	return EXE_SUCCEED;	
}

/* 画矩形 */
uint8_t uTjc4832tDraw( uint16_t uX,uint16_t uY,uint16_t uW,uint16_t uH,uint16_t uColor )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[255] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  	
	
	sprintf( (char *)ucSendBuf,"draw " );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uX,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uY,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uW,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",uH,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d",uColor );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif
	return EXE_SUCCEED;	
}

/* 隐藏控件 页面参数无效 */
uint8_t uTjc4832tVisObjState( uint8_t page_id,uint8_t control_id,uint8_t uState )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[128] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	sprintf( (char *)ucSendBuf,"%s","vis " );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d",control_id );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%c",',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d",uState );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif	
	return 0;
}

/* 设置数字值 */
uint8_t uTjc4832tSetNumValue( uint8_t page_id,uint8_t control_id,uint8_t *str)
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[128] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	uTjc4832tPageTextId( page_id,ucSendBuf );
	Len = strlen( (const char*)ucSendBuf );
	uTjc4832tNumId( control_id,ucSendBuf+Len );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%s",(const char*)str );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif	
	return 0;
}

/* 设置浮点数字值 */
uint8_t uTjc4832tSetFloatNumValue( uint8_t page_id,uint8_t control_id,uint8_t *str)
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[128] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	uTjc4832tPageTextId( page_id,ucSendBuf );
	Len = strlen( (const char*)ucSendBuf );
	uTjc4832tFNumId( control_id,ucSendBuf+Len );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%s",(const char*)str );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif	
	return 0;
}

/* 设置双向开关值 */
uint8_t uTjc4832tSetSwitchValue( uint8_t page_id,uint8_t control_id,uint8_t *str)
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[128] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	uTjc4832tPageTextId( page_id,ucSendBuf );
	Len = strlen( (const char*)ucSendBuf );
	uTjc4832tSwitchId( control_id,ucSendBuf+Len );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%s",(const char*)str );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif	
	return 0;
}

/* 设置进度条值 */
uint8_t uTjc4832tSetProgressbarValue( uint8_t page_id,uint8_t control_id,uint8_t value )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[128] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	uTjc4832tPageTextId( page_id,ucSendBuf );
	Len = strlen( (const char*)ucSendBuf );
	uTjc4832tScheduleId( control_id,ucSendBuf+Len );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d",value );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;	
	}
	
	vEnableUsartPrintf( uRecUsart );               /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif
	return 0;
}

/* 设置触摸开关 */
uint8_t uTjc4832tTouchSwitch( uint8_t control_id,uint8_t uenable )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	uint8_t ucSendBuf[128] = {0};
	uint8_t Len = 0;
	uint8_t Err = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );                      /* 使能串口4printf */  
	
	sprintf( (char *)ucSendBuf,"%s","tsw " );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d%c",control_id,',' );
	Len = strlen( (const char*)ucSendBuf );
	sprintf( (char *)ucSendBuf+Len,"%d",uenable );
	
	Len = strlen( (const char*)ucSendBuf );
	if( Len<sizeof(ucSendBuf) ){
		myprintf( "%s",ucSendBuf );                    /*清除打印缓存各参数恢复为默认值*/
		myprintf( "\xff\xff\xff" );                    /*清除打印缓存各参数恢复为默认值*/
	}else{
		Err = 1;
	}
	
	vEnableUsartPrintf( uRecUsart );                           /* 使能串口1printf */
#endif
	
#if DEBUH_UART1	
	if( 1==Err ){
		myprintf( "TjcDataError \r\n" );
	}
#endif	
	return 0;
}

uint8_t uTjc4832tPageTextId( uint8_t page_id,uint8_t* pBuf )
{
	switch( page_id ){
		case 0:
			sprintf( (char *)pBuf,"%s","page0." );
			break;	
		case 1:
			sprintf( (char *)pBuf,"%s","page1." );
			break;
		case 2:
			sprintf( (char *)pBuf,"%s","page2." );
			break;
		case 3:
			sprintf( (char *)pBuf,"%s","page3." );
			break;	
		case 4:
			sprintf( (char *)pBuf,"%s","page4." );
			break;
		case 5:
			sprintf( (char *)pBuf,"%s","page5." );
			break;
		case 6:
			sprintf( (char *)pBuf,"%s","page6." );
			break;
		case 7:
			sprintf( (char *)pBuf,"%s","page7." );
			break;	
		case 8:
			sprintf( (char *)pBuf,"%s","page8." );
			break;
		case 9:
			sprintf( (char *)pBuf,"%s","page9." );
			break;
		case 10:
			sprintf( (char *)pBuf,"%s","page10." );
			break;
		case 11:
			sprintf( (char *)pBuf,"%s","page11." );
			break;
		case 12:
			sprintf( (char *)pBuf,"%s","page12." );
			break;	
		case 13:
			sprintf( (char *)pBuf,"%s","page13." );
			break;
		case 14:
			sprintf( (char *)pBuf,"%s","page14." );
			break;
		case 15:
			sprintf( (char *)pBuf,"%s","page15." );
			break;
		case 16:
			sprintf( (char *)pBuf,"%s","page16." );
			break;
		case 17:
			sprintf( (char *)pBuf,"%s","page17." );
			break;
		case 18:
			sprintf( (char *)pBuf,"%s","page18." );
			break;
		case 19:
			sprintf( (char *)pBuf,"%s","page19." );
			break;
		case 20:
			sprintf( (char *)pBuf,"%s","page20." );
			break;
		case 21:
			sprintf( (char *)pBuf,"%s","page21." );
			break;
		case 22:
			sprintf( (char *)pBuf,"%s","page22." );
			break;
		case 23:
			sprintf( (char *)pBuf,"%s","page23." );
			break;
		case 24:
			sprintf( (char *)pBuf,"%s","page24." );
			break;
		case 25:
			sprintf( (char *)pBuf,"%s","page25." );
			break;
		case 26:
			sprintf( (char *)pBuf,"%s","page26." );
			break;
		case 27:
			sprintf( (char *)pBuf,"%s","page27." );
			break;
		case 28:
			sprintf( (char *)pBuf,"%s","page28." );
			break;
		case 29:
			sprintf( (char *)pBuf,"%s","page29." );
			break;
		case 30:
			sprintf( (char *)pBuf,"%s","page30." );
			break;
		
		default:
			break;
	}
	
	return 0;
}

uint8_t uTjc4832tTextId( uint8_t control_id,uint8_t* pBuf )
{
	switch( control_id ){
		case 0:
			sprintf( (char *)pBuf,"%s","t0.txt=\"" );
			break;	
		case 1:
			sprintf( (char *)pBuf,"%s","t1.txt=\"" );
			break;
		case 2:
			sprintf( (char *)pBuf,"%s","t2.txt=\"" );
			break;
		case 3:
			sprintf( (char *)pBuf,"%s","t3.txt=\"" );
			break;	
		case 4:
			sprintf( (char *)pBuf,"%s","t4.txt=\"" );
			break;
		case 5:
			sprintf( (char *)pBuf,"%s","t5.txt=\"" );
			break;
		case 6:
			sprintf( (char *)pBuf,"%s","t6.txt=\"" );
			break;
		case 7:
			sprintf( (char *)pBuf,"%s","t7.txt=\"" );
			break;	
		case 8:
			sprintf( (char *)pBuf,"%s","t8.txt=\"" );
			break;
		case 9:
			sprintf( (char *)pBuf,"%s","t9.txt=\"" );
			break;
		case 10:
			sprintf( (char *)pBuf,"%s","t10.txt=\"" );
			break;	
		case 11:
			sprintf( (char *)pBuf,"%s","t11.txt=\"" );
			break;
		case 12:
			sprintf( (char *)pBuf,"%s","t12.txt=\"" );
			break;
		case 13:
			sprintf( (char *)pBuf,"%s","t13.txt=\"" );
			break;	
		case 14:
			sprintf( (char *)pBuf,"%s","t14.txt=\"" );
			break;
		case 15:
			sprintf( (char *)pBuf,"%s","t15.txt=\"" );
			break;
		
		default:
			break;
	}
	
	return 0;
}

uint8_t uTjc4832tTextPcoId( uint8_t control_id,uint8_t* pBuf )
{
	switch( control_id ){
		case 0:
			sprintf( (char *)pBuf,"%s","t0.pco=" );
			break;	                           
		case 1:                                
			sprintf( (char *)pBuf,"%s","t1.pco=" );
			break;                             
		case 2:                                
			sprintf( (char *)pBuf,"%s","t2.pco=" );
			break;                             
		case 3:                                
			sprintf( (char *)pBuf,"%s","t3.pco=" );
			break;	                           
		case 4:                                
			sprintf( (char *)pBuf,"%s","t4.pco=" );
			break;                             
		case 5:                                
			sprintf( (char *)pBuf,"%s","t5.pco=" );
			break;                             
		case 6:                                
			sprintf( (char *)pBuf,"%s","t6.pco=" );
			break;                             
		case 7:                                
			sprintf( (char *)pBuf,"%s","t7.pco=" );
			break;	                           
		case 8:                                
			sprintf( (char *)pBuf,"%s","t8.pco=" );
			break;                             
		case 9:                                
			sprintf( (char *)pBuf,"%s","t9.pco=" );
			break;
		case 10:
			sprintf( (char *)pBuf,"%s","t10.pco=" );
			break;	                            
		case 11:                                
			sprintf( (char *)pBuf,"%s","t11.pco=" );
			break;                              
		case 12:                                
			sprintf( (char *)pBuf,"%s","t12.pco=" );
			break;                              
		case 13:                                
			sprintf( (char *)pBuf,"%s","t13.pco=" );
			break;	                            
		case 14:                                
			sprintf( (char *)pBuf,"%s","t14.pco=" );
			break;                              
		case 15:                                
			sprintf( (char *)pBuf,"%s","t15.pco=" );
			break;
		
		default:
			break;
	}
	
	return 0;
}

uint8_t uTjc4832tButterId( uint8_t control_id,uint8_t* pBuf )
{
	switch( control_id ){
		case 0:
			sprintf( (char *)pBuf,"%s","b0.txt=\"" );
			break;	
		case 1:
			sprintf( (char *)pBuf,"%s","b1.txt=\"" );
			break;
		case 2:
			sprintf( (char *)pBuf,"%s","b2.txt=\"" );
			break;
		case 3:
			sprintf( (char *)pBuf,"%s","b3.txt=\"" );
			break;	
		case 4:
			sprintf( (char *)pBuf,"%s","b4.txt=\"" );
			break;
		case 5:
			sprintf( (char *)pBuf,"%s","b5.txt=\"" );
			break;
		case 6:
			sprintf( (char *)pBuf,"%s","b6.txt=\"" );
			break;
		case 7:
			sprintf( (char *)pBuf,"%s","b7.txt=\"" );
			break;	
		case 8:
			sprintf( (char *)pBuf,"%s","b8.txt=\"" );
			break;
		case 9:
			sprintf( (char *)pBuf,"%s","b9.txt=\"" );
			break;
		case 10:
			sprintf( (char *)pBuf,"%s","b10.txt=\"" );
			break;	
		case 11:
			sprintf( (char *)pBuf,"%s","b11.txt=\"" );
			break;
		case 12:
			sprintf( (char *)pBuf,"%s","b12.txt=\"" );
			break;
		case 13:
			sprintf( (char *)pBuf,"%s","b13.txt=\"" );
			break;	
		case 14:
			sprintf( (char *)pBuf,"%s","b14.txt=\"" );
			break;
		case 15:
			sprintf( (char *)pBuf,"%s","b15.txt=\"" );
			break;
		
		default:
			break;
	}
	
	return 0;
}

uint8_t uTjc4832tCheckBoxId( uint8_t control_id,uint8_t* pBuf )
{
	switch( control_id ){
		case 0:
			sprintf( (char *)pBuf,"%s","c0.val=" );
			break;	
		case 1:
			sprintf( (char *)pBuf,"%s","c1.val=" );
			break;
		case 2:
			sprintf( (char *)pBuf,"%s","c2.val=" );
			break;
		case 3:
			sprintf( (char *)pBuf,"%s","c3.val=" );
			break;	
		case 4:
			sprintf( (char *)pBuf,"%s","c4.val=" );
			break;
		case 5:
			sprintf( (char *)pBuf,"%s","c5.val=" );
			break;
		case 6:
			sprintf( (char *)pBuf,"%s","c6.val=" );
			break;
		case 7:
			sprintf( (char *)pBuf,"%s","c7.val=" );
			break;	
		case 8:
			sprintf( (char *)pBuf,"%s","c8.val=" );
			break;
		case 9:
			sprintf( (char *)pBuf,"%s","c9.val=" );
			break;
		case 10:
			sprintf( (char *)pBuf,"%s","c10.val=" );
			break;	
		case 11:
			sprintf( (char *)pBuf,"%s","c11.val=" );
			break;
		case 12:
			sprintf( (char *)pBuf,"%s","c12.val=" );
			break;
		case 13:
			sprintf( (char *)pBuf,"%s","c13.val=" );
			break;	
		case 14:
			sprintf( (char *)pBuf,"%s","c14.val=" );
			break;
		case 15:
			sprintf( (char *)pBuf,"%s","c15.val=" );
			break;
		
		default:
			break;
	}
	
	return 0;
}

uint8_t uTjc4832tVariableId( uint8_t control_id,uint8_t* pBuf )
{
	switch( control_id ){
		case 0:
			sprintf( (char *)pBuf,"%s","va0.val=" );
			break;	
		case 1:
			sprintf( (char *)pBuf,"%s","va1.val=" );
			break;
		case 2:
			sprintf( (char *)pBuf,"%s","va2.val=" );
			break;
		case 3:
			sprintf( (char *)pBuf,"%s","va3.val=" );
			break;	
		case 4:
			sprintf( (char *)pBuf,"%s","va4.val=" );
			break;
		case 5:
			sprintf( (char *)pBuf,"%s","va5.val=" );
			break;
		case 6:
			sprintf( (char *)pBuf,"%s","va6.val=" );
			break;
		case 7:
			sprintf( (char *)pBuf,"%s","va7.val=" );
			break;	
		case 8:
			sprintf( (char *)pBuf,"%s","va8.val=" );
			break;
		case 9:
			sprintf( (char *)pBuf,"%s","va9.val=" );
			break;
		case 10:
			sprintf( (char *)pBuf,"%s","va10.val=" );
			break;	
		case 11:
			sprintf( (char *)pBuf,"%s","va11.val=" );
			break;
		case 12:
			sprintf( (char *)pBuf,"%s","va12.val=" );
			break;
		case 13:
			sprintf( (char *)pBuf,"%s","va13.val=" );
			break;	
		case 14:
			sprintf( (char *)pBuf,"%s","va14.val=" );
			break;
		case 15:
			sprintf( (char *)pBuf,"%s","va15.val=" );
			break;
		
		default:
			break;
	}
	
	return 0;
}

uint8_t uTjc4832tNumId( uint8_t control_id,uint8_t* pBuf )
{
	switch( control_id ){
		case 0:
			sprintf( (char *)pBuf,"%s","n0.val=" );
			break;	
		case 1:
			sprintf( (char *)pBuf,"%s","n1.val=" );
			break;
		case 2:
			sprintf( (char *)pBuf,"%s","n2.val=" );
			break;
		case 3:
			sprintf( (char *)pBuf,"%s","n3.val=" );
			break;	
		case 4:
			sprintf( (char *)pBuf,"%s","n4.val=" );
			break;
		case 5:
			sprintf( (char *)pBuf,"%s","n5.val=" );
			break;
		case 6:
			sprintf( (char *)pBuf,"%s","n6.val=" );
			break;
		case 7:
			sprintf( (char *)pBuf,"%s","n7.val=" );
			break;	
		case 8:
			sprintf( (char *)pBuf,"%s","n8.val=" );
			break;
		case 9:
			sprintf( (char *)pBuf,"%s","n9.val=" );
			break;
		
		default:
			break;
	}
	
	return 0;
}

uint8_t uTjc4832tFNumId( uint8_t control_id,uint8_t* pBuf )
{
	switch( control_id ){
		case 0:
			sprintf( (char *)pBuf,"%s","x0.val=" );
			break;	
		case 1:
			sprintf( (char *)pBuf,"%s","x1.val=" );
			break;
		case 2:
			sprintf( (char *)pBuf,"%s","x2.val=" );
			break;
		case 3:
			sprintf( (char *)pBuf,"%s","x3.val=" );
			break;	
		case 4:
			sprintf( (char *)pBuf,"%s","x4.val=" );
			break;
		case 5:
			sprintf( (char *)pBuf,"%s","x5.val=" );
			break;
		case 6:
			sprintf( (char *)pBuf,"%s","x6.val=" );
			break;
		case 7:
			sprintf( (char *)pBuf,"%s","x7.val=" );
			break;	
		case 8:
			sprintf( (char *)pBuf,"%s","x8.val=" );
			break;
		case 9:
			sprintf( (char *)pBuf,"%s","x9.val=" );
			break;
		
		default:
			break;
	}
	
	return 0;
}

uint8_t uTjc4832tSwitchId( uint8_t control_id,uint8_t* pBuf )
{
	switch( control_id ){
		case 0:
			sprintf( (char *)pBuf,"%s","bt0.val=" );
			break;	
		case 1:
			sprintf( (char *)pBuf,"%s","bt1.val=" );
			break;
		case 2:
			sprintf( (char *)pBuf,"%s","bt2.val=" );
			break;
		case 3:
			sprintf( (char *)pBuf,"%s","bt3.val=" );
			break;	
		case 4:
			sprintf( (char *)pBuf,"%s","bt4.val=" );
			break;
		case 5:
			sprintf( (char *)pBuf,"%s","bt5.val=" );
			break;
		case 6:
			sprintf( (char *)pBuf,"%s","bt6.val=" );
			break;
		case 7:
			sprintf( (char *)pBuf,"%s","bt7.val=" );
			break;	
		case 8:
			sprintf( (char *)pBuf,"%s","bt8.val=" );
			break;
		case 9:
			sprintf( (char *)pBuf,"%s","bt9.val=" );
			break;
		
		default:
			break;
	}
	
	return 0;
}

uint8_t uTjc4832tScheduleId( uint8_t control_id,uint8_t* pBuf )
{
	switch( control_id ){
		case 0:
			sprintf( (char *)pBuf,"%s","j0.val=" );
			break;	
		case 1:
			sprintf( (char *)pBuf,"%s","j1.val=" );
			break;

		
		default:
			break;
	}
	
	return 0;
}

uint8_t uTestTjc4832t( void )
{
#if	DEBUH_UART4
	uint8_t uRecUsart = 0;
	
	uRecUsart = uGetUsartPrintf();	
	vEnableUsartPrintf( TJC_USART_NUM );               /* 使能串口4printf */  
	
	myprintf( "page %d",3 );                             /*清除打印缓存各参数恢复为默认值*/
	
	myprintf( "\xff\xff\xff" );                          /*清除打印缓存各参数恢复为默认值*/
	
	vEnableUsartPrintf( uRecUsart );                   /* 使能串口1printf */
#endif
	return 0;
}


