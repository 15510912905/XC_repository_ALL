#ifndef _FUNC_ERROR_H_
#define _FUNC_ERROR_H_

#include "Func_IFP_300_Drv.h"
#include "Func_ADHandler.h"
#include "Global_Variable.h"

#define ERROE001_CODE     ("001")   //"25Q64 Check Failed!"//"Please Check!      "
#define ERROE002_CODE     ("002")   //"RTC ERROR!" //"RTC Trying...");	
#define ERROE003_CODE     ("Password")//("003")   //登录警告 1s钟警告
#define ERROE004_CODE     ("004")   //登录警告 1分钟等待
#define ERROE005_CODE     ("005")   //没有ID卡
#define ERROE006_CODE     ("006")   //ID数据错误
#define ERROE007_CODE     ("007")   //条码不正确
#define ERROE008_CODE     ("008")   //设置时间数据不对
#define ERROE009_CODE     ("009")   //输入配置数据不合法
#define ERROE010_CODE     ("010")   //稍后再试



#pragma pack(1)	/*按1字节对齐*/


uint8_t ErrorHandler( void );
	
#endif
	
