#ifndef _FUNC_ELECTRIC_H_
#define _FUNC_ELECTRIC_H_

#include "Func_IFP_300_Drv.h"

#define ELECTRIC_TIME         (10)

int16_t iElectricQuantityDis( uint8_t uDisplay );
int16_t iRealElectricValue( uint8_t uAverage );
uint8_t iElectricInit( void );
int16_t iElectricAve( int16_t* pElecValue );
uint8_t uElecRefresh( uint8_t uDisplay );

#endif
	
