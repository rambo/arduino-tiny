#ifndef core_pins_ATtinyX4_h
#define core_pins_ATtinyX4_h

#include "core_build_options.h"


/*=============================================================================
  Pin definitions for the ATtiny84
=============================================================================*/

#define PIN_A0  (10)
#define PIN_A1  ( 9)
#define PIN_A2  ( 8)
#define PIN_A3  ( 7)
#define PIN_A4  ( 6)
#define PIN_A5  ( 5)
#define PIN_A6  ( 4)
#define PIN_A7  ( 3)
#define PIN_B0  ( 0)
#define PIN_B1  ( 1)
#define PIN_B2  ( 2)
#define PIN_B3  (11)  /* RESET */

#define CORE_DIGITAL_FIRST    (0)
#define CORE_DIGITAL_LAST     (11)
#define CORE_DIGITAL_COUNT    (CORE_DIGITAL_LAST-CORE_DIGITAL_FIRST+1)
#define CORE_RESET_INCLUDED   (1)

#define CORE_ANALOG_FIRST     (CORE_DIGITAL_LAST+1)
#define CORE_ANALOG_COUNT     (8)
#define CORE_ANALOG_LAST      (CORE_ANALOG_FIRST+CORE_ANALOG_COUNT-1)

#define CORE_INT0_PIN  PIN_B2

#define CORE_OC0A_PIN  PIN_B2
#define CORE_OC0B_PIN  PIN_A7
#define CORE_OC1A_PIN  PIN_A6
#define CORE_OC1B_PIN  PIN_A5

#define CORE_PWM0_PIN       CORE_OC0A_PIN
#define CORE_PWM0_TIMER     0
#define CORE_PWM0_CHANNEL   A

#define CORE_PWM1_PIN       CORE_OC0B_PIN
#define CORE_PWM1_TIMER     0
#define CORE_PWM1_CHANNEL   B

#define CORE_PWM2_PIN       CORE_OC1A_PIN
#define CORE_PWM2_TIMER     1
#define CORE_PWM2_CHANNEL   A

#define CORE_PWM3_PIN       CORE_OC1B_PIN
#define CORE_PWM3_TIMER     1
#define CORE_PWM3_CHANNEL   B

#define CORE_PWM_COUNT      (4)

#endif