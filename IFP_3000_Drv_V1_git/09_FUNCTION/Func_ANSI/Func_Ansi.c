#include "Func_Ansi.h"
//ANSI编码 

uint8_t ChooseCoefficient( uint8_t uCoefficient )
{
	memset( g_uSampleType,0,ARR_SAMPLE_TYPE_SIZE );
	
	if( BUTTON_VALUE_WHOLE==uCoefficient ){
		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
			sprintf( (char *)g_uSampleType,"%s",(const char *)"Whole  blood" );	
		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
			sprintf( (char *)g_uSampleType,"%s",(const char *)"全血" );	
		}else{
			sprintf( (char *)g_uSampleType,"%s",(const char *)"Whole  blood" );	
		}			
	}else if( BUTTON_VALUE_SERUM==uCoefficient ){		
		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
			sprintf( (char *)g_uSampleType,"%s",(const char *)"Serum/Plasma" );		
		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
			sprintf( (char *)g_uSampleType,"%s",(const char *)"血清/血浆" );	
		}else{
			sprintf( (char *)g_uSampleType,"%s",(const char *)"Serum/Plasma" );	
		}	
	}else if( BUTTON_VALUE_S_MORE==uCoefficient ){
		if( EN_ON==gp_stuConfigFile->uCutEnCu ){
			sprintf( (char *)g_uSampleType,"%s",(const char *)"Other" );	
		}else if( CH_ON==gp_stuConfigFile->uCutEnCu ){
			sprintf( (char *)g_uSampleType,"%s",(const char *)"其他" );	
		}else{
			sprintf( (char *)g_uSampleType,"%s",(const char *)"Other" );
		}			
	}else{
		//sprintf( (char *)g_uSampleType,"%s",(const char *)"Others blood" );
		//sprintf( (char *)g_uSampleType,"%s",(const char *)"Finger blood" );		
	}
	
	return EXE_SUCCEED;
}
