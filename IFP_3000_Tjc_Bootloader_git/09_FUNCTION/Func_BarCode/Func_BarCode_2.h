#ifndef _FUNC_BARCODE_2_H_
#define _FUNC_BARCODE_2_H_

#include "Func_IFP_300_Drv.h"
#include "Func_ADHandler.h"
#include "Global_Variable.h"

uint8_t* uWaveCrestTroughFirstDerivative( const uint16_t* upArrData,uint8_t* upArrBar,int len );

uint8_t uLinearSmooth( const uint16_t* in, int32_t N );
uint8_t uLinearSmooth7 ( const uint16_t* in, uint16_t* out, int32_t N );
uint8_t uQuadraticSmooth7( const uint16_t* in, uint16_t* out, int32_t N );
uint8_t uCubicSmooth7( const uint16_t* in, uint16_t* out, int32_t N );
	
#endif
	
