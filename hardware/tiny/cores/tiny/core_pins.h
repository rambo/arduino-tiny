/*==============================================================================

  core_pins.h - Pin definitions.

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

#ifndef core_pins_h
#define core_pins_h

#include "core_build_options.h"


/*=============================================================================
  Pin definitions for the ATtinyX313
=============================================================================*/

#if defined( __AVR_ATtinyX313__ )
#include "core_pins_ATtinyX313.h"
#endif


/*=============================================================================
  Pin definitions for the ATtiny84
=============================================================================*/

#if defined( __AVR_ATtinyX4__ )
#include "core_pins_ATtinyX4.h"
#endif


/*=============================================================================
  Pin definitions for the ATtiny85
=============================================================================*/

#if defined( __AVR_ATtinyX5__ )
#include "core_pins_ATtinyX5.h"
#endif

/*=============================================================================
  Pin definitions for the ATtiny1634
=============================================================================*/

#if defined( __AVR_ATtiny1634__ )
#include "core_pins_ATtiny1634.h"
#endif




#endif
