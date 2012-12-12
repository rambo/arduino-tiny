/*==============================================================================

  core_build_options.h - Various options for mapping functionality to hardware.

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

#ifndef core_build_options_h
#define core_build_options_h


/*=============================================================================
  Low power / smaller code options
=============================================================================*/

#define INITIALIZE_ANALOG_TO_DIGITAL_CONVERTER    1
#define INITIALIZE_SECONDARY_TIMERS               1


/*=============================================================================
  Build options for the ATtinyX313 processor
=============================================================================*/

#if defined( __AVR_ATtiny2313__ ) || defined( __AVR_ATtiny4313__ )
#define __AVR_ATtinyX313__
#endif

#if defined( __AVR_ATtinyX313__ )
#include "core_build_options_ATtinyX313.h"
#endif


/*=============================================================================
  Build options for the ATtiny84 processor
=============================================================================*/

#if defined( __AVR_ATtiny24__ ) || defined( __AVR_ATtiny44__ ) || defined( __AVR_ATtiny84__ )
#define __AVR_ATtinyX4__
#endif

#if defined( __AVR_ATtinyX4__ )
#include "core_build_options_ATtinyX4.h"
#endif


/*=============================================================================
  Build options for the ATtiny85 processor
=============================================================================*/

#if defined( __AVR_ATtiny25__ ) || defined( __AVR_ATtiny45__ ) || defined( __AVR_ATtiny85__ )
#define __AVR_ATtinyX5__
#endif

#if defined( __AVR_ATtinyX5__ )
#include "core_build_options_ATtinyX5.h"
#endif

/*=============================================================================
  Build options for the ATtiny81634 processor
=============================================================================*/

#if defined( __AVR_ATtiny1634__ )
#include "core_build_options_ATtiny1634.h"
#endif



/*=============================================================================
  There doesn't seem to be many people using a bootloader so we'll assume 
  there isn't one.  If the following is true (non-zero), the timers are 
  reinitialized to their power-up state in init just in case the bootloader 
  left them in a bad way.
=============================================================================*/

#define HAVE_BOOTLOADER                           0


/*=============================================================================
  Allow the ADC to be optional for low-power applications
=============================================================================*/

#if ! defined( HAVE_ADC )
  #define HAVE_ADC   0
#endif

#if ! HAVE_ADC
  #undef INITIALIZE_ANALOG_TO_DIGITAL_CONVERTER
  #define INITIALIZE_ANALOG_TO_DIGITAL_CONVERTER  0
#else
  #if ! defined( INITIALIZE_ANALOG_TO_DIGITAL_CONVERTER )
    #define INITIALIZE_ANALOG_TO_DIGITAL_CONVERTER   1
  #endif
#endif


/*=============================================================================
  Allow the "secondary timers" to be optional for low-power applications
=============================================================================*/

#if ! defined( INITIALIZE_SECONDARY_TIMERS )
  #define INITIALIZE_SECONDARY_TIMERS               1
#endif


#endif
