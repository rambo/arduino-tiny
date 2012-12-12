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


#if defined( __AVR_ATtiny1634__ )
#include "pins_arduino_ATtiny1634.inc"
#endif

