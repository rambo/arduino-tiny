===========================================================================

  Copyright 2010 Rowdy Dog Software.

  This file is part of TinyTuner.

  TinyTuner is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or (at
  your option) any later version.

  TinyTuner is distributed in the hope that it will be useful, but WITHOUT 
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
  License for more details.

  You should have received a copy of the GNU Lesser General Public License 
  along with TinyTuner.  If not, see <http://www.gnu.org/licenses/>.

===========================================================================

Poor Man's Tiny Tuner

The TinyTuner is a library for tuning the internal oscillator on AVR processors.

Thank you to Atmel for the motivation and oPossum (Kevin Timmerman) for the inspiration...
http://forums.adafruit.com/viewtopic.php?t=5078


Introduction
===========================================================================

Some stand-alone projects don't need a highly accurate processor clock and can benefit from a reduced component count.  Using the internal oscillator is perfect fit.  The only problem with the internal oscillator is that, from the factory, it can be up to 10% off.  For most applications, a 10% error in the clock can be a problem.  For example, the highest serial baud rate that can be reached when the clock is 4.5% off is 19200.  An application that needs a baud rate of 57600 isn't going to work.


Techniques
===========================================================================

There are a few different methods for tuning the internal oscillator.  These are the two I've tried...
http://atmel.com/dyn/resources/prod_documents/doc2555.pdf
http://forums.adafruit.com/viewtopic.php?t=5078

I had no luck with the AVR053 method.  At one point, my ATtiny2313 processor stopped working (meaning the processor would not execute instructions when powered; yikes!).  I have no idea what I did wrong or how I got the processor back to life.  For someone (like me) who dislikes assembly and has never compiled an assembly source file, this method is, in the best case, very annoying.

I have not actually tried the oPossum for one reason: assembly.  Inspired by the idea to use a serial connection to tune the processor, I decided to create something that was more Arduino friendly.


Overview
===========================================================================

The idea is simple: Use the AVR processor to measure the time of some serial data.  If the serial data is accurately clocked (and generally it is) it is possible to adjust the internal oscillator until the measured time matches the expected time.  The core of the technique is TimeNineBits.  This function waits until a start bit arrives then counts until a stop bit arrives.  If the count is too high, the processor is running too fast.  If the count is too low, the processor is running too slow.


Using
===========================================================================

The Tiny84Tuner class is included for tuning an ATtiny84 processor using pin 0 (PB0).  Connect anything to pin 0 that accurately outputs a lowercase 'x' at 9600 baud.  Ensure the ATtiny84 processor is using the internal oscillator.  Add something like this to a Sketch...

#include <TinyTuner.h>

void Tune( void )
{
  Tiny84Tuner tt;
  bool KeepGoing = true;

  while ( KeepGoing )
  {
    KeepGoing = tt.update();

    // Optionally provide feedback here
  }
  // At this point, OSCCAL is set to the optimal value
}

When Tune returns, OSCCAL is set to the optimal value.  This value can be save to EEPROM, output to a terminal using NewSoftSerial, or used as-is.


For other processors, it is necessary to create a class instance using the TinyTuner template.  The syntax looks like this...

TinyTuner<0x16,0x00> tt;

"0x16" is the PIN register and "0x00" is the bit within the register where the serial data arrives.  (I apologize for not supporting Arduino pin numbers nor the GCC #defines.)  Then use "tt" like in the example above.


The package includes three example Sketches.  All three use Tiny84Tuner.  Interactive_with_NewSoftSerial is intended to be used interactively.  As a human sends each 'x', a status message is sent back.  The final result is the OSCCAL register value.  

Save_to_EEPROM blinks an LED as each 'x' is processed.  Then the optimal value is reached, the value is written to address zero in EEPROM, the LED is lit solid, and the Sketch stops running.  Read_from_EEPROM simple reads the value from EEPROM address zero and outputs it to a terminal using NewSoftSerial.


Availability
===========================================================================

A ZIP download is available here...
http://arduino-tiny.googlecode.com/files/TinyTuner-0001.zip

The source code is here...
http://code.google.com/p/arduino-tiny/source/browse/#svn/trunk/libraries/TinyTuner


License
===========================================================================

This library is released under the GNU Lesser General Public License.
