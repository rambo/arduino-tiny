#ifndef Pins_Arduino_ATtinyX4_inc
#define Pins_Arduino_ATtinyX4_inc

#include <avr/io.h>
#include "pins_arduino.h"
#include "wiring_private.h"

// ATMEL ATTINY84 / ARDUINO
//
//                           +-\/-+
//                     VCC  1|    |14  GND
//             (D  0)  PB0  2|    |13  AREF (D 10)
//             (D  1)  PB1  3|    |12  PA1  (D  9) 
//                     PB3  4|    |11  PA2  (D  8) 
//  PWM  INT0  (D  2)  PB2  5|    |10  PA3  (D  7) 
//  PWM        (D  3)  PA7  6|    |9   PA4  (D  6) 
//  PWM        (D  4)  PA6  7|    |8   PA5  (D  5)        PWM
//                           +----+

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint8_t PROGMEM port_to_mode_PGM[] = 
{
  NOT_A_PORT,
  &DDRA,
  &DDRB,
};

const uint8_t PROGMEM port_to_output_PGM[] = 
{
  NOT_A_PORT,
  &PORTA,
  &PORTB,
};

const uint8_t PROGMEM port_to_input_PGM[] = 
{
  NOT_A_PORT,
  &PINA,
  &PINB,
};

const uint8_t PROGMEM port_to_pcmask_PGM[] = 
{
  NOT_A_PORT,
  &PCMSK0,
  &PCMSK1,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = 
{
  PORT_B_ID, /* 0 */
  PORT_B_ID,
  PORT_B_ID,
  PORT_A_ID,
  PORT_A_ID,
  PORT_A_ID,
  PORT_A_ID,
  PORT_A_ID,
  PORT_A_ID, /* 8 */
  PORT_A_ID,
  PORT_A_ID,
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = 
{
  _BV(0), /* 0, port B */
  _BV(1),
  _BV(2),
  _BV(7), /* 3 port B */
  _BV(6),
  _BV(5),
  _BV(4),
  _BV(3),
  _BV(2), 
  _BV(1),
  _BV(0),
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = 
{
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  TIMER0A, /* OC0A */
  TIMER0B, /* OC0B */
  TIMER1A, /* OC1A */
  TIMER1B, /* OC1B */
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER, 
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
};


#endif