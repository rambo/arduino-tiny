#ifndef Pins_Arduino_ATtinyX5_inc
#define Pins_Arduino_ATtinyX5_inc

#include <avr/io.h>
#include "pins_arduino.h"
#include "wiring_private.h"

// ATMEL ATTINY45 / ARDUINO
//
//                           +-\/-+
//  Ain0       (D  5)  PB5  1|    |8   VCC
//  Ain3       (D  3)  PB3  2|    |7   PB2  (D  2)  INT0  Ain1
//  Ain2       (D  4)  PB4  3|    |6   PB1  (D  1)        pwm1
//                     GND  4|    |5   PB0  (D  0)        pwm0
//                           +----+

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing) tiny45 only port B 
const uint8_t PROGMEM port_to_mode_PGM[] = 
{
	NOT_A_PORT,
	&DDRB,
};

const uint8_t PROGMEM port_to_output_PGM[] = 
{
	NOT_A_PORT,
	&PORTB,
};

const uint8_t PROGMEM port_to_input_PGM[] = 
{
	NOT_A_PIN,
	&PINB,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = 
{
	PORT_B_ID, /* 0 */
	PORT_B_ID,
	PORT_B_ID,
	PORT_B_ID,
	PORT_B_ID, 
	PORT_B_ID, /* 5 */

};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = 
{
	_BV(0), /* 0, port B */
	_BV(1),
	_BV(2),
	_BV(3), /* 3 port B */
	_BV(4),
	_BV(5),

};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = 
{
	TIMER0A, /* OC0A */
	TIMER1A, /* OC1A? */
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
};


#endif