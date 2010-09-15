/*
  core_pins.h - Pin definitions and constants for Arduino-Tiny
  Part of Arduino - http://www.arduino.cc/

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
*/

#ifndef core_pins_h
#define core_pins_h

// fix? rmv? #define CORE_NUM_TOTAL_PINS	25

/* The following constants are for "normal" digital pins; ones that cannot also be analog inputs. */

#define CORE_NUM_DIGITAL                (5)

#define CORE_DIGITAL_PIN_FIRST          (0)
#define CORE_DIGITAL_PIN_LAST           (4)
#define CORE_DIGITAL_COUNT              (CORE_DIGITAL_PIN_LAST-CORE_DIGITAL_PIN_FIRST+1)

/* The following constants are for "extended" digital pins; ones that are also analog inputs. */

#define CORE_EXTENDED_PIN_FIRST         (5)
#define CORE_EXTENDED_PIN_LAST          (10)
#define CORE_EXTENDED_COUNT             (CORE_EXTENDED_PIN_LAST-CORE_EXTENDED_PIN_FIRST+1s)

/* Are the normal range and extended range continuous? */

#if CORE_EXTENDED_PIN_FIRST == (CORE_DIGITAL_PIN_LAST+1)
#define CORE_EXTENDED_IS_CONTINUOUS     (1)
#else
#define CORE_EXTENDED_IS_CONTINUOUS     (0)
#endif


// fix? rmv? #define CORE_NUM_ANALOG		12
// fix? rmv? #define CORE_NUM_PWM		7
// fix? rmv? #define CORE_NUM_INTERRUPT	4

#endif
