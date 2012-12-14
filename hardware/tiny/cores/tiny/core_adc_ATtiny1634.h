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






#error "Not implemented"


#endif