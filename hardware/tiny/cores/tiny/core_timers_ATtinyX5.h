#ifndef core_timers_ATtinyX5_h
#define core_timers_ATtinyX5_h

#include <avr/io.h>
#include <binary.h>

#include "core_pins.h"
#include "core_build_options.h"
#include "core_macros.h"

/*=============================================================================
  Veneer for the two ATtiny85 timers
=============================================================================*/

#define Timer0_OutputComparePinA  CORE_OC0A_PIN
#define Timer0_OutputComparePinB  CORE_OC0B_PIN

#define TIMER0_SUPPORTS_PHASE_CORRECT_PWM  (1)

__attribute__((always_inline)) static inline void Timer0_SetToPowerup( void )
{
  // Stop the clock, set waveform generation to normal, and set output mode to normal
  TCCR0B = (0<<FOC0A) | (0<<FOC0B) | (0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
  TCCR0A = (0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
  // Reset the count to zero
  TCNT0 = 0;
  // Set the output compare registers to zero
  OCR0A = 0;
  OCR0B = 0;
  // Disable all Timer0 interrupts
  TIMSK &= ~ MASK3(OCIE0A,OCIE0B,TOIE0);
  // Clear the Timer0 interrupt flags
  TIFR |= MASK3(OCF0A,OCF0B,TOV0);
}

__attribute__((always_inline)) static inline void Timer0_InterruptsOff( void )
{
  TIMSK &= ~MASK3(OCIE0A,OCIE0B,TOIE0);
}

#define TIMER0_NUMBER_PRESCALERS  (5)

#define TIMER0_PRESCALER_VALUE_1  (1)
#define TIMER0_PRESCALER_VALUE_2  (8)
#define TIMER0_PRESCALER_VALUE_3  (64)
#define TIMER0_PRESCALER_VALUE_4  (256)
#define TIMER0_PRESCALER_VALUE_5  (1024)

typedef uint16_t timer0_prescale_value_t;

typedef enum
{
  Timer0_Stopped               = B000,
  Timer0_Prescale_Value_1      = B001,
  Timer0_Prescale_Value_8      = B010,
  Timer0_Prescale_Value_64     = B011,
  Timer0_Prescale_Value_256    = B100,
  Timer0_Prescale_Value_1024   = B101,
  Timer0_T0_Falling            = B110,
  Timer0_T0_Rising             = B111,
  Timer0_Prescale_Index_1      = B001,
  Timer0_Prescale_Index_2      = B010,
  Timer0_Prescale_Index_3      = B011,
  Timer0_Prescale_Index_4      = B100,
  Timer0_Prescale_Index_5      = B101
}
timer0_cs_t;

__attribute__((always_inline)) static inline void Timer0_ClockSelect( timer0_cs_t cs )
{
  TCCR0B = (TCCR0B & ~MASK3(CS02,CS01,CS00)) | (cs << CS00);
}

typedef enum
{
  Timer0_Normal                     = B000,
  Timer0_Phase_Correct_PWM_FF       = B001,
  Timer0_CTC_OCR                    = B010,
  Timer0_Fast_PWM_FF                = B011,
  Timer0_Reserved_1                 = B100,
  Timer0_Phase_Correct_PWM_OCR      = B101,
  Timer0_Reserved_2                 = B110,
  Timer0_Fast_PWM_OCR               = B111
}
timer0_wgm_t;

__attribute__((always_inline)) static inline void Timer0_SetWaveformGenerationMode( timer0_wgm_t wgm )
{
  TCCR0A = (TCCR0A & ~MASK2(WGM01,WGM00)) | (((wgm & B011) >> 0) << WGM00);
  TCCR0B = (TCCR0B & ~MASK1(WGM02))       | (((wgm & B100) >> 2) << WGM02);
}

typedef enum
{
  Timer0_Disconnected = 0,
  Timer0_Toggle = B01,
  Timer0_Clear  = B10,
  Timer0_Set    = B11
}
timer0_com_t;

__attribute__((always_inline)) static inline void Timer0_SetCompareOutputModeA( timer0_com_t com )
{
  TCCR0A = (TCCR0A & ~MASK2(COM0A1,COM0A0)) | (com << COM0A0);
}

__attribute__((always_inline)) static inline void Timer0_SetCompareOutputModeB( timer0_com_t com )
{
  TCCR0A = (TCCR0A & ~MASK2(COM0B1,COM0B0)) | (com << COM0B0);
}

__attribute__((always_inline)) static inline void Timer0_DisconnectOutputs( void )
{
  TCCR0A &= ~MASK4(COM0A1,COM0A0,COM0B1,COM0B0);
}

#define TIMER0_MAXIMUM_OCR        (255)
#define TIMER0_PRESCALE_SET       (1)

typedef uint8_t timer0_ocr_t;
typedef uint8_t timer0_tcnt_t;

__attribute__((always_inline)) static inline void Timer0_SetOutputCompareMatchAndClear( timer0_ocr_t oc )
{
  OCR0A = oc;
}

__attribute__((always_inline)) static inline void Timer0_SetOutputCompareMatchA( timer0_ocr_t oc )
{
  OCR0A = oc;
}

__attribute__((always_inline)) static inline void Timer0_SetOutputCompareMatchB( timer0_ocr_t oc )
{
  OCR0B = oc;
}

__attribute__((always_inline)) static inline void Timer0_EnableOutputCompareInterruptA( void )
{
  TIMSK |= (1<<OCIE0A);
} 

__attribute__((always_inline)) static inline void Timer0_EnableOverflowInterrupt( void )
{
  TIMSK |= (1<<TOIE0);
} 

__attribute__((always_inline)) static inline timer0_tcnt_t Timer0_GetCount( void )
{
  return( TCNT0 );
}

__attribute__((always_inline)) static inline void Timer0_SetCount( timer0_tcnt_t v )
{
  TCNT0 = v;
}

__attribute__((always_inline)) static inline uint8_t Timer0_IsOverflowSet( void )
{
  return( (TIFR & (1<<TOV0)) != 0 );
}


#define Timer1_OutputComparePinA  CORE_OC1A_PIN
#define Timer1_OutputComparePinB  CORE_OC1B_PIN

#define TIMER1_SUPPORTS_PHASE_CORRECT_PWM  (0)

__attribute__((always_inline)) static inline void Timer1_SetToPowerup( void )
{
  // Turn off Clear on Compare Match, turn off PWM A, disconnect the timer from the output pin, stop the clock
  TCCR1 = (0<<CTC1) | (0<<PWM1A) | (0<<COM1A1) | (0<<COM1A0) | (0<<CS13) | (0<<CS12) | (0<<CS11) | (0<<CS10);
  // Turn off PWM A, disconnect the timer from the output pin, no Force Output Compare Match, no Prescaler Reset
  GTCCR &= ~MASK6(PWM1B,COM1B1,COM1B0,FOC1B,FOC1A,PSR1);
  // Reset the count to zero
  TCNT1 = 0;
  // Set the output compare registers to zero
  OCR1A = 0;
  OCR1B = 0;
  OCR1C = 0;
  // Disable all Timer1 interrupts
  TIMSK &= ~MASK3(OCIE1A,OCIE1B,TOIE1);
  // Clear the Timer1 interrupt flags
  TIFR |= MASK3(OCF1A,OCF1B,TOV1);
}

__attribute__((always_inline)) static inline void Timer1_InterruptsOff( void )
{
  TIMSK &= ~MASK3(OCIE1A,OCIE1B,TOIE1);
}

#define TIMER1_NUMBER_PRESCALERS  (15)

#define TIMER1_PRESCALER_VALUE_1  (1)
#define TIMER1_PRESCALER_VALUE_2  (2)
#define TIMER1_PRESCALER_VALUE_3  (4)
#define TIMER1_PRESCALER_VALUE_4  (8)
#define TIMER1_PRESCALER_VALUE_5  (16)
#define TIMER1_PRESCALER_VALUE_6  (32)
#define TIMER1_PRESCALER_VALUE_7  (64)
#define TIMER1_PRESCALER_VALUE_8  (128)
#define TIMER1_PRESCALER_VALUE_9  (256)
#define TIMER1_PRESCALER_VALUE_10 (512)
#define TIMER1_PRESCALER_VALUE_11 (1024)
#define TIMER1_PRESCALER_VALUE_12 (2048)
#define TIMER1_PRESCALER_VALUE_13 (4096)
#define TIMER1_PRESCALER_VALUE_14 (8192)
#define TIMER1_PRESCALER_VALUE_15 (16384)

typedef uint16_t timer1_prescale_value_t;

typedef enum
{
  Timer1_Stopped               = B0000,
  Timer1_Prescale_Value_1      = B0001,
  Timer1_Prescale_Value_2      = B0010,
  Timer1_Prescale_Value_4      = B0011,
  Timer1_Prescale_Value_8      = B0100,
  Timer1_Prescale_Value_16     = B0101,
  Timer1_Prescale_Value_32     = B0110,
  Timer1_Prescale_Value_64     = B0111,
  Timer1_Prescale_Value_128    = B1000,
  Timer1_Prescale_Value_256    = B1001,
  Timer1_Prescale_Value_512    = B1010,
  Timer1_Prescale_Value_1024   = B1011,
  Timer1_Prescale_Value_2048   = B1100,
  Timer1_Prescale_Value_4096   = B1101,
  Timer1_Prescale_Value_8192   = B1110,
  Timer1_Prescale_Value_16384  = B1111,
  Timer1_Prescale_Index_1      = B0001,
  Timer1_Prescale_Index_2      = B0010,
  Timer1_Prescale_Index_3      = B0011,
  Timer1_Prescale_Index_4      = B0100,
  Timer1_Prescale_Index_5      = B0101,
  Timer1_Prescale_Index_6      = B0110,
  Timer1_Prescale_Index_7      = B0111,
  Timer1_Prescale_Index_8      = B1000,
  Timer1_Prescale_Index_9      = B1001,
  Timer1_Prescale_Index_10     = B1010,
  Timer1_Prescale_Index_11     = B1011,
  Timer1_Prescale_Index_12     = B1100,
  Timer1_Prescale_Index_13     = B1101,
  Timer1_Prescale_Index_14     = B1110,
  Timer1_Prescale_Index_15     = B1111
}
timer1_cs_t;

__attribute__((always_inline)) static inline void Timer1_ClockSelect( timer1_cs_t cs )
{
  TCCR1 = (TCCR1 & ~MASK4(CS13,CS12,CS11,CS10)) | (cs << CS10);
}

typedef enum
{
  // Used internally
  _Timer1_Enable_PWM_Mask           = B10000000,
  _Timer1_Set_OCRnC_To_FF_Mask      = B01000000,

  Timer1_Normal                     = B0,
  Timer1_CTC_OCR                    = B1,
  Timer1_Fast_PWM_FF                = Timer1_CTC_OCR | _Timer1_Enable_PWM_Mask | _Timer1_Set_OCRnC_To_FF_Mask

/* fix: The following requires a function to set the match+clear value (OCR1C).  A similar function needs to be provided for Timer0.  And, both need to be tested.
  ,
  Timer1_Fast_PWM_OCR               = Timer1_CTC_OCR | _Timer1_Enable_PWM_Mask
*/
}
timer1_wgm_t;

__attribute__((always_inline)) static inline void Timer1_SetWaveformGenerationMode( timer1_wgm_t wgm )
{
  TCCR1 = (TCCR1 & ~MASK1(CTC1)) | ((wgm & 0x1) << CTC1);

  if ( wgm & _Timer1_Enable_PWM_Mask )
  {
    TCCR1 |= MASK1(PWM1A);
    GTCCR |= MASK1(PWM1B);
  }

  if ( wgm & _Timer1_Set_OCRnC_To_FF_Mask )
  {
    OCR1C = 0xFF;
  }
}

typedef enum
{
  Timer1_Disconnected = 0,
  Timer1_Toggle = B01,
  Timer1_Clear  = B10,
  Timer1_Set    = B11
}
timer1_com_t;

__attribute__((always_inline)) static inline void Timer1_SetCompareOutputModeA( timer1_com_t com )
{
  TCCR1 = (TCCR1 & ~MASK2(COM1A1,COM1A0)) | (com << COM1A0);
}

__attribute__((always_inline)) static inline void Timer1_SetCompareOutputModeB( timer1_com_t com )
{
  GTCCR = (GTCCR & ~MASK2(COM1B1,COM1B0)) | (com << COM1B0);
}

__attribute__((always_inline)) static inline void Timer1_DisconnectOutputs( void )
{
  TCCR1 &= ~MASK2(COM1A1,COM1A0);
  GTCCR &= ~MASK2(COM1B1,COM1B0);
}

#define TIMER1_MAXIMUM_OCR        (255)
#define TIMER1_PRESCALE_SET       (2)

typedef uint8_t timer1_ocr_t;
typedef uint8_t timer1_tcnt_t;

__attribute__((always_inline)) static inline void Timer1_SetOutputCompareMatchAndClear( timer1_ocr_t oc )
{
  OCR1A = oc;
  OCR1B = oc;
  OCR1C = oc;
}

__attribute__((always_inline)) static inline void Timer1_SetOutputCompareMatchA( timer1_ocr_t oc )
{
  OCR1A = oc;
}

__attribute__((always_inline)) static inline void Timer1_SetOutputCompareMatchB( timer1_ocr_t oc )
{
  OCR1B = oc;
}

__attribute__((always_inline)) static inline void Timer1_EnableOutputCompareInterruptA( void )
{
  TIMSK |= (1<<OCIE1A);
} 

__attribute__((always_inline)) static inline void Timer1_EnableOverflowInterrupt( void )
{
  TIMSK |= (1<<TOIE1);
} 

__attribute__((always_inline)) static inline timer1_tcnt_t Timer1_GetCount( void )
{
  return( TCNT1 );
}

__attribute__((always_inline)) static inline void Timer1_SetCount( timer1_tcnt_t v )
{
  TCNT1 = v;
}

__attribute__((always_inline)) static inline uint8_t Timer1_IsOverflowSet( void )
{
  return( (TIFR & (1<<TOV1)) != 0 );
}



#endif