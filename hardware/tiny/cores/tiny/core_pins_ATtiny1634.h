#ifndef core_pins_ATtiny1634_h
#define core_pins_ATtiny1634_h

#include "core_build_options.h"

/*=============================================================================
  Pin definitions for the ATtiny1634
=============================================================================*/

#define PIN_B0  ( 0)
#define PIN_A7  ( 1)
#define PIN_A6  ( 2)
#define PIN_A5  ( 3)
#define PIN_A4  ( 4)
#define PIN_A3  ( 5)
#define PIN_A2  ( 6)
#define PIN_A1  ( 7)
#define PIN_A0  ( 8)
#define PIN_C5  ( 9)
#define PIN_C4  (10)
#define PIN_C2  (11)
#define PIN_C1  (12)
#define PIN_C0  (13)
#define PIN_B3  (14)
#define PIN_B2  (15)
#define PIN_B1  (16)
#define PIN_C3  (17)  /* RESET */

#define CORE_DIGITAL_FIRST    (0)
#define CORE_DIGITAL_LAST     (17)
#define CORE_DIGITAL_COUNT    (CORE_DIGITAL_LAST-CORE_DIGITAL_FIRST+1)
#define CORE_RESET_INCLUDED   (1)

#define CORE_ANALOG_FIRST     (CORE_DIGITAL_LAST+1)
#define CORE_ANALOG_COUNT     (13) // 12 + internal temperature sensor
#define CORE_ANALOG_LAST      (CORE_ANALOG_FIRST+CORE_ANALOG_COUNT-1)

#define CORE_INT0_PIN  PIN_C2

#define CORE_OC0A_PIN  PIN_C0
#define CORE_OC0B_PIN  PIN_A5
#define CORE_OC1A_PIN  PIN_B3
#define CORE_OC1B_PIN  PIN_A6

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