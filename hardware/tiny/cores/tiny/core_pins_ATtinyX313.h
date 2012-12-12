#ifndef core_pins_ATtinyX313_h
#define core_pins_ATtinyX313_h

#include "core_build_options.h"

/*=============================================================================
  Pin definitions for the ATtinyX313
=============================================================================*/

#define PIN_D0  ( 0)
#define PIN_D1  ( 1)
#define PIN_A1  ( 2)
#define PIN_A0  ( 3)
#define PIN_D2  ( 4)
#define PIN_D3  ( 5)
#define PIN_D4  ( 6)
#define PIN_D5  ( 7)
#define PIN_D6  ( 8)
#define PIN_B0  ( 9)
#define PIN_B1  (10)
#define PIN_B2  (11)
#define PIN_B3  (12)
#define PIN_B4  (13)
#define PIN_B5  (14)
#define PIN_B6  (15)
#define PIN_B7  (16)
#define PIN_A2  (17)  /* RESET */

#define CORE_DIGITAL_FIRST    (0)
#define CORE_DIGITAL_LAST     (17)
#define CORE_DIGITAL_COUNT    (CORE_DIGITAL_LAST-CORE_DIGITAL_FIRST+1)
#define CORE_RESET_INCLUDED   (1)

#define CORE_ANALOG_COUNT     (0)

#define CORE_INT0_PIN  PIN_D2
#define CORE_INT1_PIN  PIN_D3

#define CORE_OC0A_PIN  PIN_B2
#define CORE_OC0B_PIN  PIN_D5
#define CORE_OC1A_PIN  PIN_B3
#define CORE_OC1B_PIN  PIN_B4

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