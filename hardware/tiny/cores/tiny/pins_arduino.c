/*
  pins_arduino.c - pin definitions for the Arduino board
  Part of Arduino / Wiring Lite

  Copyright (c) 2005 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: pins_arduino.c 565 2009-03-25 10:50:00Z dmellis $

  Modified 28-08-2009 for attiny84 R.Wiersma
  Modified 09-10-2009 for attiny45 A.Saporetti
  Modified for Atmel ATTiny2313 mcu by René Bohne

  Corrected 17-05-2010 for ATtiny84 B.Cook ...

    The default analog_reference leaves chip pin 13 (digital pin 10; PA0) 
    unconnected.  So the pin can be set to a non-floating state and so the 
    pin can be used as another digital pin, support for digital pin 10 was 
    added.
*/

#include <avr/io.h>
#include "pins_arduino.h"
#include "wiring_private.h"

#if defined( __AVR_ATtinyX313__ )
#include "pins_arduino_ATtinyX313.inc"
#endif


#if defined( __AVR_ATtinyX4__ )
#include "pins_arduino_ATtinyX4.inc"
#endif


#if defined( __AVR_ATtinyX5__ )
#include "pins_arduino_ATtinyX5.inc"
#endif


/**
 * BEGIN: attiny1634
 */
#if defined( __AVR_ATtiny1634__ )

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
// Reminder: Pins 6 - 1 are ADC pins
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
/**
 * END: attiny1634
 */
