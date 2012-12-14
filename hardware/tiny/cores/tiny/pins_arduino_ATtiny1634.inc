#ifndef Pins_Arduino_ATtiny1634_inc
#define Pins_Arduino_ATtiny1634_inc

#include <avr/io.h>
#include "pins_arduino.h"
#include "wiring_private.h"


// On the Arduino board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.

// ATMEL ATTINY1634
//
//                   +-\/-+
// TX   (D  0) PB0  1|    |20  PB1 (D  16)
// RX   (D  1) PA7  2|    |19  PB2 (D  15)
//    * (D  2) PA6  3|    |18  PB3 (D  14) *
//    * (D  3) PA5  4|    |17  PC0 (D  13) *
//      (D  4) PA4  5|    |16  PC1 (D  12)
//      (D  5) PA4  6|    |15  PC2 (D  11)
//      (D  6) PA3  7|    |14  PC3/RESET (D 17)
//      (D  7) PA2  8|    |13  PC4 (D  10)
//      (D  8) PA0  9|    |12  PC5 (D  9)
//             GND 10|    |11  VCC
//                   +----+
//
// Reminder: Pins 6 - 1 & 20 - 15 are ADC pins
// * indicates PWM port

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint8_t PROGMEM port_to_mode_PGM[] = 
{
	NOT_A_PORT,
	&DDRA,
	&DDRB,
	&DDRC,
};

const uint8_t PROGMEM port_to_output_PGM[] = 
{
	NOT_A_PORT,
	&PORTA,
	&PORTB,
	&PORTC,
};

const uint8_t PROGMEM port_to_input_PGM[] = 
{
	NOT_A_PORT,
	&PINA,
	&PINB,
	&PINC,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = 
{
	PORT_B_ID, /* 0 */
	PORT_A_ID,
	PORT_A_ID,
	PORT_A_ID,
	PORT_A_ID,
	PORT_A_ID,
	PORT_A_ID,
	PORT_A_ID,
	PORT_A_ID, /* 8 */
	PORT_C_ID,
	PORT_C_ID,
	PORT_C_ID,
	PORT_C_ID,
	PORT_C_ID,
	PORT_B_ID, /* 14 */
	PORT_B_ID,
	PORT_B_ID,
    PORT_C_ID, /* 17 = RESET */
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = 
{
	_BV(0), /* 0 */
	_BV(7),
	_BV(6),
	_BV(5),
	_BV(4),
	_BV(3),
	_BV(2),
	_BV(1),
	_BV(0), /* 8 */
	_BV(5),
	_BV(4),
	_BV(2),
	_BV(1),
	_BV(0),
	_BV(3), /* 14 */
	_BV(2),
	_BV(1),
    _BV(3), /* 17 = RESET */
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = 
{
	NOT_ON_TIMER, /* 0 */
	NOT_ON_TIMER,
	TIMER1B,
    TIMER0B,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER, /* 8 */
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER0A,
	TIMER1A,      /* 14 */
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER, /* 17 = RESET */
};



#endif