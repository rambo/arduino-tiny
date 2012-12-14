#ifndef core_adc_common_h
#define core_adc_common_h

#include <avr/io.h>
#include <binary.h>

#include "core_build_options.h"
#include "core_macros.h"

/*=============================================================================
  Some common things
=============================================================================*/


/*
  From the '84 and '85 datasheets... By default, the successive approximation 
  circuitry requires an input clock frequency between 50 kHz and 200 kHz to 
  get maximum resolution.
*/
#if F_CPU == 16000000
  // 16 MHz / 128 = 125 KHz
  #define ADC_ARDUINO_PRESCALER   ADC_Prescaler_Value_128
#elif F_CPU == 8000000
  // 8 MHz / 64 = 125 KHz
  #define ADC_ARDUINO_PRESCALER   ADC_Prescaler_Value_64
#elif F_CPU == 1000000
  // 1 MHz / 8 = 125 KHz
  #define ADC_ARDUINO_PRESCALER   ADC_Prescaler_Value_8
#else
  #error Add an entry for the selected processor speed.
#endif

typedef enum
{
  ADC_Prescaler_Value_2      = B001,
  ADC_Prescaler_Value_4      = B010,
  ADC_Prescaler_Value_8      = B011,
  ADC_Prescaler_Value_16     = B100,
  ADC_Prescaler_Value_32     = B101,
  ADC_Prescaler_Value_64     = B110,
  ADC_Prescaler_Value_128    = B111,
  ADC_Prescaler_Index_1      = B001,
  ADC_Prescaler_Index_2      = B010,
  ADC_Prescaler_Index_3      = B011,
  ADC_Prescaler_Index_4      = B100,
  ADC_Prescaler_Index_5      = B101,
  ADC_Prescaler_Index_6      = B110,
  ADC_Prescaler_Index_7      = B111
}
adc_ps_t;

__attribute__((always_inline)) static inline void ADC_PrescalerSelect( adc_ps_t ps )
{
  ADCSRA = (ADCSRA & ~MASK3(ADPS2,ADPS1,ADPS0)) | (ps << ADPS0);
}

__attribute__((always_inline)) static inline void ADC_Enable( void )
{
  ADCSRA |= MASK1( ADEN );
}

__attribute__((always_inline)) static inline void ADC_StartConversion( void )
{
  ADCSRA |= MASK1( ADSC );
}

__attribute__((always_inline)) static inline uint8_t ADC_ConversionInProgress( void )
{
  return( (ADCSRA & (1<<ADSC)) != 0 );
}

__attribute__((always_inline)) static inline uint16_t ADC_GetDataRegister( void )
{
  return( ADC );
}


#endif