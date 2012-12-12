#ifndef core_build_options_ATtinyX5_h
#define core_build_options_ATtinyX5_h

/*=============================================================================
  Build options for the ATtiny85 processor
=============================================================================*/

/*
  For various reasons, Timer 1 is a better choice for the millis timer on the
  '85 processor.
*/
#define TIMER_TO_USE_FOR_MILLIS                   1

/*
  If the following is true (non-zero) there will be two phase-correct PWM 
  pins and one fast PWM pin.  If false there will be one phase-correct PWM 
  pin and two fast PWM pins.
*/
#define FAVOR_PHASE_CORRECT_PWM                   1

/*
  Tone goes on whichever timer was not used for millis.
*/
#if TIMER_TO_USE_FOR_MILLIS == 1
#define TIMER_TO_USE_FOR_TONE                     0
#else
#define TIMER_TO_USE_FOR_TONE                     1
#endif

#define HAVE_ADC                                  1

#define DEFAULT_TO_TINY_DEBUG_SERIAL              1


#endif