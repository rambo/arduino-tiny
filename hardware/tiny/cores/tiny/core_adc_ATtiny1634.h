#ifndef core_adc_ATtiny1634_h
#define core_adc_ATtiny1634_h

#include <avr/io.h>
#include <binary.h>

#include "core_build_options.h"
#include "core_macros.h"

/*=============================================================================
  Veneer for the ATtiny1634 ADC
=============================================================================*/
// First get the common ADC config
#include "core_adc_common.h"


typedef enum
{
  ADC_Reference_VCC                             = B00,
  ADC_Reference_External                        = B01,
  ADC_Reference_Internal_1p1                    = B10,
  ADC_Reference_Reserved_1                      = B11
}
adc_vr_t;

__attribute__((always_inline)) static inline void ADC_SetVoltageReference( adc_vr_t vr )
{
  ADMUX = (ADMUX & ~MASK2(REFS1,REFS0)) | (((vr & B11) >> 0) << REFS0);
}

typedef enum
{
  ADC_Input_ADC0            = B0000,
  ADC_Input_ADC1            = B0001,
  ADC_Input_ADC2            = B0010,
  ADC_Input_ADC3            = B0011,
  ADC_Input_ADC4            = B0100,
  ADC_Input_ADC5            = B0101,
  ADC_Input_ADC6            = B0110,
  ADC_Input_ADC7            = B0111,
  ADC_Input_ADC8            = B0111,
  ADC_Input_ADC9            = B0111,
  ADC_Input_ADC10           = B0111,
  ADC_Input_ADC11           = B0111,

  ADC_Input_GND             = B1100,  // 0V (AGND)
  ADC_Input_1p1             = B1101,  // 1.1V (I Ref)
  ADC_Input_ADC12           = B1110,  // For temperature sensor.

}
adc_ic_t;

__attribute__((always_inline)) static inline void ADC_SetInputChannel( adc_ic_t ic )
{
  ADMUX = (ADMUX & ~MASK4(MUX3,MUX2,MUX1,MUX0)) | (ic << MUX0);
}


#endif