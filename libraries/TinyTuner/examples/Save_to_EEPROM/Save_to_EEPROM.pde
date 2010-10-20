/*==============================================================================

  Copyright 2010 Rowdy Dog Software.

  This file is part of TinyTuner.

  TinyTuner is free software: you can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation, either version 3 of the License, or (at your option)
  any later version.

  TinyTuner is distributed in the hope that it will be useful, but WITHOUT 
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
  License for more details.

  You should have received a copy of the GNU Lesser General Public License 
  along with TinyTuner.  If not, see <http://www.gnu.org/licenses/>.

  Inspired by the work of oPossum (Kevin Timmerman)...
  http://forums.adafruit.com/viewtopic.php?t=5078

==============================================================================*/
#include <EEPROM.h>
#include <TinyTuner.h>

const uint8_t PinLED = 3;

void setup( void )
{
  pinMode( PinLED, OUTPUT );
}

void loop( void )
{
  Tiny84Tuner tt;
  bool KeepGoing = true;

  while ( KeepGoing )
  {
    KeepGoing = tt.update();

    for ( uint8_t i=0; i < 2; ++i )
    {    
      digitalWrite( PinLED, ! digitalRead( PinLED ) );
      delay( 100 );
    }
  }
  uint8_t Temp = OSCCAL;
  EEPROM.write( 0, Temp );
  
  if ( EEPROM.read(0) == Temp )
  {
    digitalWrite( PinLED, HIGH );
  }
  else
  {
    digitalWrite( PinLED, LOW );
  }
  while ( 1 );
}

