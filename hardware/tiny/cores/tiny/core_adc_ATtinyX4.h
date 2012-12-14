#ifndef core_adc_ATtinyX4_h
#define core_adc_ATtinyX4_h

#include <avr/io.h>
#include <binary.h>

#include "core_build_options.h"
#include "core_macros.h"

/*=============================================================================
  Veneer for the ATtiny84 ADC
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
  ADC_Input_ADC0            = B000000,
  ADC_Input_ADC1            = B000001,
  ADC_Input_ADC2            = B000010,
  ADC_Input_ADC3            = B000011,
  ADC_Input_ADC4            = B000100,
  ADC_Input_ADC5            = B000101,
  ADC_Input_ADC6            = B000110,
  ADC_Input_ADC7            = B000111,

  ADC_Input_GND             = B100000,  // 0V (AGND)
  ADC_Input_1p1             = B100001,  // 1.1V (I Ref)
  ADC_Input_ADC8            = B100010,  // For temperature sensor.

  ADC_Input_Pos0_Neg0_20x   = B100011,  // For offset calibration, only.
  ADC_Input_Pos0_Neg1_1x    = B001000,
  ADC_Input_Pos0_Neg1_20x   = B001001,
  ADC_Input_Pos0_Neg3_1x    = B001010,
  ADC_Input_Pos0_Neg3_20x   = B001011,
  ADC_Input_Pos1_Neg0_1x    = B101000,
  ADC_Input_Pos1_Neg0_20x   = B101001,
  ADC_Input_Pos1_Neg2_1x    = B001100,
  ADC_Input_Pos1_Neg2_20x   = B001101,
  ADC_Input_Pos1_Neg3_1x    = B001110,
  ADC_Input_Pos1_Neg3_20x   = B001111,
  ADC_Input_Pos2_Neg1_1x    = B101100,
  ADC_Input_Pos2_Neg1_20x   = B101101,
  ADC_Input_Pos2_Neg3_1x    = B010000,
  ADC_Input_Pos2_Neg3_20x   = B010001,
  ADC_Input_Pos3_Neg0_1x    = B101010,
  ADC_Input_Pos3_Neg0_20x   = B101011,
  ADC_Input_Pos3_Neg1_1x    = B101110,
  ADC_Input_Pos3_Neg1_20x   = B101111,
  ADC_Input_Pos3_Neg2_1x    = B110000,
  ADC_Input_Pos3_Neg2_20x   = B110001,
  ADC_Input_Pos3_Neg3_1x    = B100100,  // For offset calibration, only.
  ADC_Input_Pos3_Neg3_20x   = B100101,  // For offset calibration, only.
  ADC_Input_Pos3_Neg4_1x    = B010010,
  ADC_Input_Pos3_Neg4_20x   = B010011,
  ADC_Input_Pos3_Neg5_1x    = B010100,
  ADC_Input_Pos3_Neg5_20x   = B010101,
  ADC_Input_Pos3_Neg6_1x    = B010110,
  ADC_Input_Pos3_Neg6_20x   = B010111,
  ADC_Input_Pos3_Neg7_1x    = B011000,
  ADC_Input_Pos3_Neg7_20x   = B011001,
  ADC_Input_Pos4_Neg3_1x    = B110010,
  ADC_Input_Pos4_Neg3_20x   = B110011,
  ADC_Input_Pos4_Neg5_1x    = B011010,
  ADC_Input_Pos4_Neg5_20x   = B011011,
  ADC_Input_Pos5_Neg3_1x    = B110100,
  ADC_Input_Pos5_Neg3_20x   = B110101,
  ADC_Input_Pos5_Neg4_1x    = B111010,
  ADC_Input_Pos5_Neg4_20x   = B111011,
  ADC_Input_Pos5_Neg6_1x    = B011100,
  ADC_Input_Pos5_Neg6_20x   = B011101,
  ADC_Input_Pos6_Neg3_1x    = B110110,
  ADC_Input_Pos6_Neg3_20x   = B110111,
  ADC_Input_Pos6_Neg5_1x    = B111100,
  ADC_Input_Pos6_Neg5_20x   = B111101,
  ADC_Input_Pos6_Neg7_1x    = B011110,
  ADC_Input_Pos6_Neg7_20x   = B011111,
  ADC_Input_Pos7_Neg3_1x    = B111000,
  ADC_Input_Pos7_Neg3_20x   = B111001,
  ADC_Input_Pos7_Neg6_1x    = B111110,
  ADC_Input_Pos7_Neg6_20x   = B111111,
  ADC_Input_Pos7_Neg7_1x    = B100110,  // For offset calibration, only.
  ADC_Input_Pos7_Neg7_20x   = B100111   // For offset calibration, only.
}
adc_ic_t;

__attribute__((always_inline)) static inline void ADC_SetInputChannel( adc_ic_t ic )
{
  ADMUX = (ADMUX & ~MASK6(MUX5,MUX4,MUX3,MUX2,MUX1,MUX0)) | (ic << MUX0);
}




#endif