#ifndef core_adc_ATtinyX5_h
#define core_adc_ATtinyX5_h

#include <avr/io.h>
#include <binary.h>

#include "core_build_options.h"
#include "core_macros.h"

/*=============================================================================
  Veneer for the ATtiny85 ADC
=============================================================================*/
// First get the common ADC config
#include "core_adc_common.h"


typedef enum
{
  ADC_Reference_VCC                             = B000,
  ADC_Reference_External                        = B001,
  ADC_Reference_Internal_1p1                    = B010,
  ADC_Reference_Reserved_1                      = B011,
  ADC_Reference_Internal_2p56                   = B110,
  ADC_Reference_Internal_2p56_Bypass_Capacitor  = B111
}
adc_vr_t;

__attribute__((always_inline)) static inline void ADC_SetVoltageReference( adc_vr_t vr )
{
  ADMUX = (ADMUX & ~MASK3(REFS1,REFS0,REFS2)) 
      | (((vr & B011) >> 0) << REFS0) 
      | (((vr & B100) >> 2) << REFS2);
}

typedef enum
{
  ADC_Input_ADC0            = B0000,
  ADC_Input_ADC1            = B0001,
  ADC_Input_ADC2            = B0010,
  ADC_Input_ADC3            = B0011,

  ADC_Input_Pos2_Neg2_1x    = B0100,  // For offset calibration, only.
  ADC_Input_Pos2_Neg2_20x   = B0101,  // For offset calibration, only.
  ADC_Input_Pos2_Neg3_1x    = B0110,
  ADC_Input_Pos2_Neg3_20x   = B0111,
  ADC_Input_Pos0_Neg0_1x    = B1000,
  ADC_Input_Pos0_Neg0_20x   = B1001,
  ADC_Input_Pos0_Neg1_1x    = B1010,
  ADC_Input_Pos0_Neg1_20x   = B1011,

  ADC_Input_VBG             = B1100,
  ADC_Input_GND             = B1101,
  ADC_Input_NA              = B1110,
  ADC_Input_ADC4            = B1111   // For temperature sensor.
}
adc_ic_t;

__attribute__((always_inline)) static inline void ADC_SetInputChannel( adc_ic_t ic )
{
  ADMUX = (ADMUX & ~MASK4(MUX3,MUX2,MUX1,MUX0)) | (ic << MUX0);
}



#endif