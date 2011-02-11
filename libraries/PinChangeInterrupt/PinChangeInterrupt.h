/*==============================================================================

  PinChangeInterrupt.h - Enhanced pin change interrupts for tiny processors.

  Copyright 2010 Rowdy Dog Software.

  This file is part of Arduino-Tiny.

  Arduino-Tiny is free software: you can redistribute it and/or modify it 
  under the terms of the GNU Lesser General Public License as published by 
  the Free Software Foundation, either version 3 of the License, or (at your
  option) any later version.

  Arduino-Tiny is distributed in the hope that it will be useful, but 
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
  License for more details.

  You should have received a copy of the GNU Lesser General Public License 
  along with Arduino-Tiny.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/

#ifndef PinChangeInterrupt_h
#define PinChangeInterrupt_h

#include <inttypes.h>

#include <core_build_options.h>
// rmv #include "wiring_private.h"


#if defined( __AVR_ATtiny2313__ )
#define NUMBER_PIN_CHANGE_INTERRUPT_HANDLERS (1)
#define NUMBER_PIN_CHANGE_INTERRUPT_PORTS 1
#endif

#if defined( __AVR_ATtinyX4__ )
#define NUMBER_PIN_CHANGE_INTERRUPT_HANDLERS (3)
#define NUMBER_PIN_CHANGE_INTERRUPT_PORTS 2
#endif

#if defined( __AVR_ATtinyX5__ )
#define NUMBER_PIN_CHANGE_INTERRUPT_HANDLERS (3)
#define NUMBER_PIN_CHANGE_INTERRUPT_PORTS 1
#endif

void attachPcInterrupt( uint8_t pin, void (*callback)(void), uint8_t mode );
void detachPcInterrupt( uint8_t pin );
void detachPcInterrupt( uint8_t pin, void (*callback)(void), uint8_t mode );


#endif
