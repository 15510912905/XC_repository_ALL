#ifndef _FUNC_MOTOR_H_
#define _FUNC_MOTOR_H_

#include "Func_IFP_300_Drv.h"

//#define UI_PROMPT

#define MOTOR_UNLOCK                       (0)
#define MOTOR_LOCK                         (1)

void MotorForward( void );
void MotorBackward( void );

uint8_t ResetMotor( void );
void vResetMotorStauts( void );
//uint8_t uResetMotorStauts( void );
uint8_t uResetMotorInteriorStauts( uint8_t uPrompt );
//uint8_t ReadIDTemp( void );
void MotorLock( uint8_t lock );
bool bMotorResetStatus( void );

#endif
