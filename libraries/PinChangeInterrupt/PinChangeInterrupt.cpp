/*==============================================================================

  PinChangeInterrupt.cpp - Enhanced pin change interrupts for tiny processors.

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

#include <wiring.h>
#include <pins_arduino.h>
#include <core_macros.h>

#include <avr/interrupt.h>
#include <avr/io.h>

#include <PinChangeInterrupt.h>


typedef struct 
{
#if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
  uint8_t           port;
#endif
  uint8_t           changeMask;
  uint8_t           risingMask;
  uint8_t           fallingMask;
  void              (*callback)(void);
//rmv  voidFuncPtr       callback;
}
pcint_entry_t;

typedef volatile pcint_entry_t* pcint_entry_p;


volatile static pcint_entry_t pcint[NUMBER_PIN_CHANGE_INTERRUPT_HANDLERS];


static volatile uint8_t previousPinValue0;

#if defined( PCMSK1 )
static volatile uint8_t previousPinValue1;
#endif


void attachPcInterrupt( uint8_t pin, void (*callback)(void), uint8_t mode ) 
{
#if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
  uint8_t           port;
#endif
  uint8_t           bitMask;
  uint8_t           changeMask;
  uint8_t           risingMask;
  uint8_t           fallingMask;
  pcint_entry_p     hole;
  pcint_entry_p     entry;

  changeMask = 0;
  risingMask = 0;
  fallingMask = 0;

  bitMask = digitalPinToBitMask( pin );
  
  switch ( mode )
  {
  case CHANGE:
    changeMask = bitMask;
    break;

  case FALLING:
    fallingMask = bitMask;
    break;

  case RISING:
    risingMask = bitMask;
    break;

  default:
    return;
  }

#if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
  port = digitalPinToPort( pin );
#endif

tryAgain:

  hole = 0;

  entry = pcint;
  for ( uint8_t i=0; i < NUMBER_PIN_CHANGE_INTERRUPT_HANDLERS; ++i )
  {
    uint8_t SaveSREG = SREG;
    cli();

    if ( (hole == 0) && (entry->callback == 0) )
    {
      hole = entry;
    }
    else
    {
      if ( 
          #if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
            (port == entry->port) &&
          #endif
          (changeMask == entry->changeMask)
          && (risingMask == entry->risingMask)
          && (fallingMask == entry->fallingMask)
          && (callback == entry->callback) )
      {
        SREG = SaveSREG;
        return;
      }
    }

    SREG = SaveSREG;

    ++entry;
  }

  if ( hole == 0 )
    return;

  uint8_t SaveSREG = SREG;
  cli();

  if ( hole->callback == 0 )
  {
    #if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
      hole->port = port;
    #endif
    hole->changeMask = changeMask;
    hole->risingMask = risingMask;
    hole->fallingMask = fallingMask;
    hole->callback = callback;

    #if defined( __AVR_ATtinyX4__ )

      if ( port == PORT_A_ID )
      {
        GIMSK |= MASK1( PCIE0 );

        if ( (PCMSK0 & bitMask) == 0 )
        {
          previousPinValue0 |= (PINA & bitMask);
          PCMSK0 |= bitMask;
        }
      }
      else // if ( port = PORT_ID_B )
      {
        GIMSK |= MASK1( PCIE1 );

        if ( (PCMSK1 & bitMask) == 0 )
        {
          previousPinValue1 |= (PINB & bitMask);
          PCMSK1 |= bitMask;
        }
      }

    #endif


    #if defined( __AVR_ATtinyX5__ ) || defined( __AVR_ATtiny2313__ )

      GIMSK |= MASK1( PCIE );

      if ( (PCMSK & bitMask) == 0 )
      {
        previousPinValue0 |= (PINB & bitMask);
        PCMSK |= bitMask;
      }

    #endif
  }
  else
  {
    SREG = SaveSREG;
    goto tryAgain;
  }

  SREG = SaveSREG;
}


static void ClearEntry( pcint_entry_p entry )
{
#if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
  entry->port = 0;
#endif
  entry->changeMask = 0;
  entry->risingMask = 0;
  entry->fallingMask = 0;
  entry->callback = 0;
}

static void InterruptOff( 
    #if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
      uint8_t port, 
    #endif
    uint8_t bitMask )
{
  #if defined( __AVR_ATtinyX4__ )

    if ( port == PORT_A_ID )
    {
      previousPinValue0 &= bitMask;
      PCMSK0 &= bitMask;
      
      if ( PCMSK0 == 0 )
      {
        GIMSK &= ~ MASK1( PCIE0 );
      }
    }
    else // if ( port = PORT_ID_B )
    {
      previousPinValue1 &= bitMask;
      PCMSK1 &= bitMask;
      
      if ( PCMSK1 == 0 )
      {
        GIMSK &= ~ MASK1( PCIE1 );
      }
    }

  #endif


  #if defined( __AVR_ATtinyX5__ ) || defined( __AVR_ATtiny2313__ )

    previousPinValue0 &= bitMask;
    PCMSK &= bitMask;

    if ( PCMSK == 0 )
    {
      GIMSK &= ~ MASK1( PCIE );
    }

  #endif
}

void detachPcInterrupt( uint8_t pin )
{
#if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
  uint8_t           port;
#endif
  uint8_t           bitMask;
  pcint_entry_p     entry;

#if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
  port = digitalPinToPort( pin );
#endif
  bitMask = digitalPinToBitMask( pin );

  InterruptOff( 
      #if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
        port, 
      #endif
      ~ bitMask );

  entry = pcint;
  for ( uint8_t i=0; i < NUMBER_PIN_CHANGE_INTERRUPT_HANDLERS; ++i )
  {
    uint8_t SaveSREG = SREG;
    cli();

    if ( 
        #if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
          (entry->port == port) &&
        #endif
        ( (entry->changeMask == bitMask) || (entry->risingMask == bitMask) || (entry->fallingMask == bitMask) ) )
    {
      ClearEntry( entry );
    }

    SREG = SaveSREG;

    ++entry;
  }
}


void detachPcInterrupt( uint8_t pin, void (*callback)(void), uint8_t mode )
{
#if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
  uint8_t           port;
#endif
  uint8_t           bitMask;
  uint8_t           changeMask;
  uint8_t           risingMask;
  uint8_t           fallingMask;
  uint8_t           otherMask;
  pcint_entry_p     entry;

  changeMask = 0;
  risingMask = 0;
  fallingMask = 0;

#if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
  port = digitalPinToPort( pin );
#endif
  bitMask = digitalPinToBitMask( pin );
  
  switch ( mode )
  {
  case CHANGE:
    changeMask = bitMask;
    break;

  case FALLING:
    fallingMask = bitMask;
    break;

  case RISING:
    risingMask = bitMask;
    break;

  default:
    return;
  }

  otherMask = 0;

  entry = pcint;
  for ( uint8_t i=0; i < NUMBER_PIN_CHANGE_INTERRUPT_HANDLERS; ++i )
  {
    uint8_t SaveSREG = SREG;
    cli();

    #if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
      if ( (entry->port == port) )
    #endif
    {
      if ( (callback == entry->callback)
          && (changeMask == entry->changeMask)
          && (risingMask == entry->risingMask)
          && (fallingMask == entry->fallingMask) )
      {
        ClearEntry( entry );
      }
      else
      {
        otherMask |= entry->changeMask | entry->risingMask | entry->fallingMask;
      }
    }

    SREG = SaveSREG;

    ++entry;
  }

  if ( (otherMask & bitMask) == 0 )
  {
    InterruptOff( 
        #if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
          port, 
        #endif
        ~ bitMask );
  }
}


static void PCINTX_common( 
    #if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
      uint8_t port, 
    #endif
    uint8_t currentPinValue, volatile uint8_t& previousPinValue )
{
  pcint_entry_p     entry;
  uint8_t           changeMask;
  uint8_t           risingMask;
  uint8_t           fallingMask;

  changeMask = previousPinValue ^ currentPinValue;
  risingMask = (~previousPinValue) & currentPinValue;
  fallingMask = previousPinValue & (~currentPinValue);
  previousPinValue = currentPinValue;


  entry = pcint;
  for ( uint8_t i=0; i < NUMBER_PIN_CHANGE_INTERRUPT_HANDLERS; ++i )
  {
    if ( 
        #if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
          (entry->port == port) &&
        #endif
        (entry->callback != 0)
        && ( (entry->changeMask & changeMask) || (entry->risingMask & risingMask) || (entry->fallingMask & fallingMask) ) )
    {
      (entry->callback)();
    }
    ++entry;
  }
}

#if defined( PCINT1_vect )
ISR( PCINT1_vect )
{
  #if defined( __AVR_ATtinyX4__ )
    PCINTX_common( 
        #if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
          PORT_B_ID, 
        #endif
        PINB & PCMSK1, previousPinValue1 );
  #endif
}
#endif

ISR( PCINT0_vect )
{
  #if defined( __AVR_ATtinyX4__ )
    PCINTX_common( 
        #if NUMBER_PIN_CHANGE_INTERRUPT_PORTS > 1
          PORT_A_ID, 
        #endif
        PINA & PCMSK0, previousPinValue0 );
  #endif

  #if defined( __AVR_ATtinyX5__ ) || defined( __AVR_ATtiny2313__ )
    PCINTX_common( PINB & PCMSK, previousPinValue0 );
  #endif
}



/* 
    GIMSK |= MASK2( PCIE1, PCIE0 );

    volatile uint8_t* pcMaskRegister;
    pcMaskRegister = portPcMaskRegister( port );

    if ( (*pcMaskRegister & bitMask) == 0 )
    {
      volatile uint8_t* inputRegister;
      inputRegister = portInputRegister( port );

      portInputRegister( port );
      previousPin[port-1] |= (*inputRegister & bitMask);
      *pcMaskRegister |= bitMask;
    }
*/

/*
'2313...

  PCMSK  PCINT[7:0]  PINB (bits line up)

  GIMSK
    PCIE  PCINT[7:0]

  PCINT


'84...

  PCMSK1  PCINT[11:8]  PINB (bits line up)

  PCMSK0  PCINT[7:0]   PINA (bits line up)

  GIMSK  
    PCIE1  PCINT[11:8]
    PCIE0  PCINT[7:0]

  PCINT1
  PCINT0


'85...

  PCMSK  PCINT[5:0]  PINB (bits line up)

  GIMSK
    PCIE  PCINT[5:0]

  PCINT0


'328...

  PCMSK2  PCINT[23:16]  PIND (bits line up)

  PCMSK1  PCINT[14:8]   PINC (bits line up)

  PCMSK0  PCINT[7:0]    PINB (bits line up)

  PCICR
    PCIE2  PCINT[23:16] 
    PCIE1  PCINT[14:8]
    PCIE0  PCINT[7:0]

  PCINT2
  PCINT1
  PCINT0
*/
