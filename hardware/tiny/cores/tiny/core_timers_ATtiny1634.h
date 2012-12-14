#ifndef core_timers_ATtiny1634_h
#define core_timers_ATtiny1634_h

#include <avr/io.h>
#include <binary.h>

#include "core_pins.h"
#include "core_build_options.h"
#include "core_macros.h"

/*=============================================================================
  Veneer for the two ATtiny1634 timers (Copied from X313
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
  TIMSK &= ~ MASK3(OCIE0B,TOIE0,OCIE0A);
  // Clear the Timer0 interrupt flags
  TIFR |= MASK3(OCF0B,TOV0,OCF0A);
}

__attribute__((always_inline)) static inline void Timer0_InterruptsOff( void )
{
  TIMSK &= ~ MASK3(OCIE0B,TOIE0,OCIE0A);
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

#define TIMER1_SUPPORTS_PHASE_CORRECT_PWM  (1)

__attribute__((always_inline)) static inline void Timer1_SetToPowerup( void )
{
  // Turn off Input Capture Noise Canceler, Input Capture Edge Select on Falling, stop the clock
  TCCR1B = (0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
  // Disconnect the timer from the output pins, Set Waveform Generation Mode to Normal
  TCCR1A = (0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
  // Reset the count to zero
  TCNT1 = 0;
  // Set the output compare registers to zero
  OCR1A = 0;
  OCR1B = 0;
  // Clear the input capture?
  // ICR1 = 0;
  // Disable all Timer1 interrupts
  TIMSK &= ~MASK4(TOIE1,OCIE1A,OCIE1B,ICIE1);
  // Clear the Timer1 interrupt flags
  TIFR |= MASK4(TOV1,OCF1A,OCF1B,ICF1);
}

__attribute__((always_inline)) static inline void Timer1_InterruptsOff( void )
{
  TIMSK &= ~MASK4(TOIE1,OCIE1A,OCIE1B,ICIE1);
}

#define TIMER1_NUMBER_PRESCALERS  (5)

#define TIMER1_PRESCALER_VALUE_1  (1)
#define TIMER1_PRESCALER_VALUE_2  (8)
#define TIMER1_PRESCALER_VALUE_3  (64)
#define TIMER1_PRESCALER_VALUE_4  (256)
#define TIMER1_PRESCALER_VALUE_5  (1024)

typedef uint16_t timer1_prescale_value_t;

typedef enum
{
  Timer1_Stopped               = B000,
  Timer1_Prescale_Value_1      = B001,
  Timer1_Prescale_Value_8      = B010,
  Timer1_Prescale_Value_64     = B011,
  Timer1_Prescale_Value_256    = B100,
  Timer1_Prescale_Value_1024   = B101,
  Timer1_T0_Falling            = B110,
  Timer1_T0_Rising             = B111,
  Timer1_Prescale_Index_1      = B001,
  Timer1_Prescale_Index_2      = B010,
  Timer1_Prescale_Index_3      = B011,
  Timer1_Prescale_Index_4      = B100,
  Timer1_Prescale_Index_5      = B101
}
timer1_cs_t;

__attribute__((always_inline)) static inline void Timer1_ClockSelect( timer1_cs_t cs )
{
  TCCR1B = (TCCR1B & ~MASK3(CS12,CS11,CS10)) | (cs << CS10);
}

typedef enum
{
  Timer1_Normal                   = B0000,
  Timer1_Phase_Correct_PWM_FF     = B0001,
  Timer1_Phase_Correct_PWM_1FF    = B0010,
  Timer1_Phase_Correct_PWM_3FF    = B0011,
  Timer1_CTC_OCR                  = B0100,
  Timer1_Fast_PWM_FF              = B0101,
  Timer1_Fast_PWM_1FF             = B0110,
  Timer1_Fast_PWM_3FF             = B0111,
  Timer1_Phase_Frequency_PWM_ICR  = B1000,
  Timer1_Phase_Frequency_PWM_OCR  = B1001,
  Timer1_Phase_Correct_PWM_ICR    = B1010,
  Timer1_Phase_Correct_PWM_OCR    = B1011,
  Timer1_CTC_ICR                  = B1100,
  Timer1_Reserved_1               = B1101,
  Timer1_Fast_PWM_ICR             = B1110,
  Timer1_Fast_PWM_OCR             = B1111
}
timer1_wgm_t;

__attribute__((always_inline)) static inline void Timer1_SetWaveformGenerationMode( timer1_wgm_t wgm )
{
  TCCR1A = (TCCR1A & ~MASK2(WGM11,WGM10)) | (((wgm & B0011) >> 0) << WGM10);
  TCCR1B = (TCCR1B & ~MASK2(WGM13,WGM12)) | (((wgm & B1100) >> 2) << WGM12);
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
  TCCR1A = (TCCR1A & ~MASK2(COM1A1,COM1A0)) | (com << COM1A0);
}

__attribute__((always_inline)) static inline void Timer1_SetCompareOutputModeB( timer1_com_t com )
{
  TCCR1A = (TCCR1A & ~MASK2(COM1B1,COM1B0)) | (com << COM1B0);
}

__attribute__((always_inline)) static inline void Timer1_DisconnectOutputs( void )
{
  TCCR1A &= ~MASK4(COM1A1,COM1A0,COM1B1,COM1B0);
}

#define TIMER1_MAXIMUM_OCR        (65535)
#define TIMER1_PRESCALE_SET       (1)

typedef uint16_t timer1_ocr_t;
typedef uint16_t timer1_tcnt_t;

__attribute__((always_inline)) static inline void Timer1_SetOutputCompareMatchAndClear( timer1_ocr_t oc )
{
  OCR1A = oc;
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