/********************************************************
   版权所有 (C), 2001-2100, 四川新健康成生物股份有限公司
  -------------------------------------------------------

				嵌入式开发平台——PID模块

  -------------------------------------------------------
   文 件 名   : Drv_Pid.c
   版 本 号   : V1.0.0.0
   作    者   : ryc
   生成日期   : 2020年2月14日
   功能描述   : 定义一种PID模块。
   使用方法   ：
   依赖于     : 
   注         ：该模块不依赖于硬件电路。 
 ********************************************************/
 
#include "Drv_Pid.h"

DRV_PID_TYPE* _gp_PidUnits[PID_BUTT] = {0};	/*PID的注册表*/

/* 接口函数
 ********************************************************/

/* 初始化PID模块
  -----------------------------
  入口：PID模块的ID号，目标值，P、I、D参数
  返回值：初始化好的PID模块结构体
*/
DRV_PID_TYPE* Drv_PidInit(DRV_PID_ENUM id, float setpoint, float kp, float ki, float kd)
{	
	DRV_PID_TYPE* p_unit = (DRV_PID_TYPE*)calloc(1, sizeof(DRV_PID_TYPE));	/*申请内存*/

	/*分配失败返回NULL*/
	if(p_unit == NULL)
	{
		return NULL;
	}
		
	/*id错误返回NULL*/
	if(id >= PID_BUTT)
	{
		free(p_unit); 
		return NULL;
	}
	
	/*如果当前模块存在，取消分配新存储区*/
	if(_gp_PidUnits[id] != NULL)
	{
		free(p_unit);
		p_unit = _gp_PidUnits[id];
	}
	else
	{
		_gp_PidUnits[id] = p_unit;
	}
	
	/*初始化*/
	
	/*-------------------------------常量*/
	p_unit->id			= id;				/*模块id*/
	p_unit->setpoint	= setpoint;
	p_unit->kp 			= kp;
	p_unit->ki 			= ki;
	p_unit->kd 			= kd;
	
	/*-------------------------------变量*/
	p_unit->status		= PID_WORKING;
	p_unit->lasterr		= 0;
	p_unit->preverr		= 0;
	p_unit->sumerr		= 0;
	
	return p_unit;
}

/* PID模块输出计算
  -----------------------------
  入口：PID模块指针，当前值
  返回值：输出值
*/
float Drv_PidCalculate(DRV_PID_TYPE* p_unit, float current)
{
    float kp = 0.0;
    float ki = 0.0;
    float kd = 0.0;
    float sum = 0.0;
    float sumerr = 0.0;
    int index = 0;
    
    p_unit->preverr = p_unit->lasterr;				/*记录前一轮误差*/
    p_unit->lasterr = p_unit->setpoint - current;	/*计算当前误差*/
    p_unit->sumerr += p_unit->lasterr;				/*计算误差累积*/
        
//    if(fabs((double)(p_unit->lasterr)) > ARRAY_ERR) 			/*积分限幅清零*/
//    {
//        p_unit->sumerr = 0;
//    }
//    
//    if(fabs((double)(p_unit->ki)) > FLT_EPSILON)				/*积分舍弃偏差*/
//    {
//        sumerr = (2 * ARRAY_DUTY / p_unit->ki);
//    }
//    else
//    {
//        sumerr = 0.0;
//    }
//
//    if(p_unit->sumerr > sumerr)
//    {
//        p_unit->sumerr = sumerr;
//    }
//    else if(p_unit->sumerr < -sumerr)
//    {
//        p_unit->sumerr = -sumerr;
//    }
    
    kp = p_unit->kp * p_unit->lasterr;
    ki = p_unit->ki * p_unit->sumerr;
    kd = p_unit->kd * (p_unit->lasterr - p_unit->preverr);

    sum = kp + ki + kd;
    if (sum <= 0)
    {
        return 0;
    }
    else if (sum >= FULLDUTY)
    {
        return FULLDUTY;
    }
    else
    {
        return sum;
    }
}
