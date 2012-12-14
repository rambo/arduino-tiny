#ifndef core_adc_noadc_h
#define core_adc_noadc_h

#include <avr/io.h>
#include <binary.h>

#include "core_build_options.h"
#include "core_macros.h"


/*=============================================================================
  Veneer for non-existant ADC
=============================================================================*/

typedef enum
{
  ADC_No_Reference  = 0
}
adc_vr_t;

__attribute__((always_inline)) static inline void ADC_SetVoltageReference( adc_vr_t vr )
{
}

typedef enum
{
  ADC_No_Input = 0
}
adc_ic_t;

__attribute__((always_inline)) static inline void ADC_SetInputChannel( adc_ic_t ic )
{
}

__attribute__((always_inline)) static inline void ADC_StartConversion( void )
{
}

__attribute__((always_inline)) static inline uint8_t ADC_ConversionInProgress( void )
{
  return( 0 );
}

__attribute__((always_inline)) static inline uint16_t ADC_GetDataRegister( void )
{
  return( 0 );
}




#endif