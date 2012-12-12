#ifndef core_build_options_ATtiny1634_h
#define core_build_options_ATtiny1634_h

/*=============================================================================
  Build options for the ATtiny1634 processor
=============================================================================*/

/*
  The old standby ... millis on Timer 0.
*/
#define TIMER_TO_USE_FOR_MILLIS                   0

/*
  Tone goes on whichever timer was not used for millis.
*/
#if TIMER_TO_USE_FOR_MILLIS == 1
#define TIMER_TO_USE_FOR_TONE                     0
#else
#define TIMER_TO_USE_FOR_TONE                     1
#endif

#define HAVE_ADC                                  1

#define DEFAULT_TO_TINY_DEBUG_SERIAL              0



#endif