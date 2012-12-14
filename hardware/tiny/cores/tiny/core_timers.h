/*==============================================================================

  core_timers.h - Veneer for the timers.

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

#ifndef core_timers_h
#define core_timers_h

#include <avr/io.h>
#include <binary.h>

#include "core_pins.h"
#include "core_build_options.h"
#include "core_macros.h"


/*=============================================================================
  Macros for generating application specific names for the stuff here (like 
  Millis_SetToPowerup as an alias for Timer1_SetToPowerup).
=============================================================================*/

#define TIMER_PASTE_A(lft,t,rgt)                  TIMER_PASTE_B(lft,t,rgt)
#define TIMER_PASTE_B(lft,t,rgt)                  lft##t##_##rgt

#define TIMER_PASTE_CHANNEL_A(lft,t,rgt,ch)       TIMER_PASTE_CHANNEL_B(lft,t,rgt,ch)
#define TIMER_PASTE_CHANNEL_B(lft,t,rgt,ch)       lft##t##_##rgt##ch


/*=============================================================================
  Notes...

  - The 2313, X4, and X5 Timer0 code only differs by TIMSK0 / TIMSK and TIFR0
    / TIFR.  It's time to make the Timer0 code reusable.

  - The 2313 and X4 Timer1 code is source code compatible (interchangeable).
    It's time to make the Timer1 code reusable.
    
=============================================================================*/

/*=============================================================================
  Veneer for the two ATtinyX313 timers
=============================================================================*/

#if defined( __AVR_ATtinyX313__ )
#include "core_timers_ATtinyX313.h"
#endif


/*=============================================================================
  Veneer for the two ATtiny84 timers
=============================================================================*/

#if defined( __AVR_ATtinyX4__ )
#include "core_timers_ATtinyX4.h"
#endif


/*=============================================================================
  Veneer for the two ATtiny85 timers
=============================================================================*/

#if defined( __AVR_ATtinyX5__ )
#include "core_timers_ATtinyX5.h"
#endif

/*=============================================================================
  Veneer for the two ATtiny1634 timers
=============================================================================*/

#if defined( __AVR_ATtiny1634__ )
#include "core_timers_ATtiny1634.h"
#endif


/*=============================================================================
  Aliases for the interrupt service routine vector numbers so the code 
  doesn't have to be riddled with #ifdefs.
=============================================================================*/

#if defined( TIM0_COMPA_vect ) && ! defined( TIMER0_COMPA_vect )
#define TIMER0_COMPA_vect TIM0_COMPA_vect
#endif

#if defined( TIM0_COMPB_vect ) && ! defined( TIMER0_COMPB_vect )
#define TIMER0_COMPB_vect TIM0_COMPB_vect
#endif

#if defined( TIM0_OVF_vect ) && ! defined( TIMER0_OVF_vect )
#define TIMER0_OVF_vect TIM0_OVF_vect
#endif

#if defined( TIM1_COMPA_vect ) && ! defined( TIMER1_COMPA_vect )
#define TIMER1_COMPA_vect TIM1_COMPA_vect
#endif

#if defined( TIM1_COMPB_vect ) && ! defined( TIMER1_COMPB_vect )
#define TIMER1_COMPB_vect TIM1_COMPB_vect
#endif

#if defined( TIM1_OVF_vect ) && ! defined( TIMER1_OVF_vect )
#define TIMER1_OVF_vect TIM1_OVF_vect
#endif


#endif
