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
#include <NewSoftSerial.h>

NewSoftSerial nss( 2, 1 );

void setup( void )
{
  nss.begin( 9600 );

  nss.println( "\r\n\r\n\r\n" );
  nss.println( "Poor Man's Tiny Tuner\n" );
  nss.println( "Place this line of code at the top of setup...\r\n" );
  nss.print( "  OSCCAL = 0x" );
  nss.print( EEPROM.read( 0 ), HEX );
  nss.println( ";\r\n" );
}


void loop( void )
{
}

