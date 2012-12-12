#ifndef Pins_Arduino_ATtinyX313_inc
#define Pins_Arduino_ATtinyX313_inc

#include <avr/io.h>
#include "pins_arduino.h"
#include "wiring_private.h"

// On the Arduino board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.

// ATMEL ATTINY2313
//
//                   +-\/-+
//      (D 17) PA2  1|    |29  VCC
// RX   (D  0) PD0  2|    |19  PB7 (D  16)
// TX   (D  1) PD1  3|    |18  PB6 (D  15)
//      (D  2) PA1  4|    |17  PB5 (D  14)
//      (D  3) PA0  5|    |16  PB4 (D  13)*
// INT0 (D  4) PD2  6|    |15  PB3 (D  12)*
// INT1 (D  5) PD3  7|    |14  PB2 (D  11)*
//      (D  6) PD4  8|    |13  PB1 (D  10)
//     *(D  7) PD5  9|    |12  PB0 (D  9)
//             GND 10|    |11  PD6 (D  8)
//                   +----+
//
// * indicates PWM port

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint8_t PROGMEM port_to_mode_PGM[] = 
{
	NOT_A_PORT,
	&DDRA,
	&DDRB,
	NOT_A_PORT,
	&DDRD,
};

const uint8_t PROGMEM port_to_output_PGM[] = 
{
	NOT_A_PORT,
	&PORTA,
	&PORTB,
	NOT_A_PORT,
	&PORTD,
};

const uint8_t PROGMEM port_to_input_PGM[] = 
{
	NOT_A_PORT,
	&PINA,
	&PINB,
	NOT_A_PORT,
	&PIND,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = 
{
	PORT_D_ID, /* 0 */
	PORT_D_ID,
	PORT_A_ID,
	PORT_A_ID,
	PORT_D_ID,
	PORT_D_ID,
	PORT_D_ID,
	PORT_D_ID,
	PORT_D_ID, /* 8 */
	PORT_B_ID,
	PORT_B_ID,
	PORT_B_ID,
	PORT_B_ID,
	PORT_B_ID,
	PORT_B_ID, /* 14 */
	PORT_B_ID,
	PORT_B_ID,
  PORT_A_ID,
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = 
{
	_BV(0), /* 0 */
	_BV(1),
	_BV(1),
	_BV(0),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6), /* 8 */
	_BV(0),
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5), /* 14 */
	_BV(6),
	_BV(7),
  _BV(2),
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = 
{
	NOT_ON_TIMER, 
	NOT_ON_TIMER,
	NOT_ON_TIMER,
  NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER0B,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER0A,
	TIMER1A,
	TIMER1B,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
};

#endif