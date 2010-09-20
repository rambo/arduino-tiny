/* Tone.cpp

  A Tone Generator Library

  Written by Brett Hagman

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

Version Modified By Date     Comments
------- ----------- -------- --------
0001    B Hagman    09/08/02 Initial coding
0002    B Hagman    09/08/18 Multiple pins
0003    B Hagman    09/08/18 Moved initialization from constructor to begin()
0004    B Hagman    09/09/26 Fixed problems with ATmega8
0005    B Hagman    09/11/23 Scanned prescalars for best fit on 8 bit timers
                    09/11/25 Changed pin toggle method to XOR
                    09/11/25 Fixed timer0 from being excluded
0006    D Mellis    09/12/29 Replaced objects with functions
0007    B Cook      10/05/03 Rewritten to only work with Timer1 and support direct hardware output

*************************************************/

#define DEBUG_TONE 1

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stddef.h>
#include <wiring.h>
#include <pins_arduino.h>

#if DEBUG_TONE
uint16_t debug_tone_last_OCR1A;
uint8_t debug_tone_last_TCCR1A;
uint8_t debug_tone_last_TCCR1B;
#endif


// timerx_toggle_count:
//  > 0 - duration specified
//  = 0 - stopped
//  < 0 - infinitely (until stop() method called, or new play() called)


static volatile long timer1_toggle_count;
static volatile uint8_t *timer1_pin_register;
static volatile uint8_t timer1_pin_mask;

static uint8_t tone_pin = 255;

static const uint8_t ToneClockSelectMask = ~ ( (1<<CS12) | (1<<CS11) | (1<<CS10) );


void tone( uint8_t _pin, unsigned int frequency, unsigned long duration )
{
  #if ( F_CPU > 1000000 )
    uint16_t ocr;
    uint8_t cs;
  #endif

  if ( tone_pin == 255 )
  {
    /* Start with all interrupts turned off */

    TIMSK1 = (0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (0<<TOIE1);

    /* 
      Compare Output Mode = Normal port operation, OC1A/OC1B disconnected.
      Waveform Generation Mode = 4; 0100; CTC; (Clear Timer on Compare); OCR1A; Immediate; MAX
      Clock Select = No clock source (Timer/Counter stopped).
      Note: Turn off the clock first to avoid ticks and scratches.
    */
    TCCR1B = (0<<ICNC1) | (0<<ICES1) | (0<<WGM13)|(1<<WGM12) | (0<<CS12)|(0<<CS11)|(0<<CS10);

    /* If the tone pin can be driven directly from the timer */

    if ( _pin == CORE_OC1A_PIN )
    {
      /* Pin toggling is handled by the hardware */
      timer1_pin_register = NULL;
      timer1_pin_mask = 0;

      /* Compare Output Mode = Toggle OC1A on Compare Match. */
      TCCR1A = (0<<COM1A1)|(1<<COM1A0) | (0<<COM1B1)|(0<<COM1B0) | (0<<WGM11)|(0<<WGM10);
    }
    else
    {
      /* Save information needed by the interrupt service routine */
      timer1_pin_register = portOutputRegister( digitalPinToPort( _pin ) );
      timer1_pin_mask = digitalPinToBitMask( _pin );

      /* Compare Output Mode = Normal port operation, OC1A disconnected. */
      TCCR1A = (0<<COM1A1)|(0<<COM1A0) | (0<<COM1B1)|(0<<COM1B0) | (0<<WGM11)|(0<<WGM10);
    }

    /* Ensure the pin is configured for output */
    pinMode( _pin, OUTPUT );

    tone_pin = _pin;
  }

  if ( tone_pin == _pin )
  {
    /* Stop the clock while we make changes. */

    TCCR1B = (TCCR1B & ToneClockSelectMask) | (0<<CS12) | (0<<CS11) | (0<<CS10);

    /* Start the counter at zero to reduce ticks and scratches. */

    TCNT1 = 0;

    if ( frequency > 0 )
    {
      /* Set the Output Compare Register (rounding up) */

      #if ( F_CPU <= 1000000 )
        OCR1A = ( (2L * F_CPU) / (frequency * 2L * 1L) + 1L ) / 2L;
      #elif ( F_CPU <= 8000000 )
        if ( frequency > 60 )
        {
          ocr = ( (2L * F_CPU) / (frequency * 2L * 1L) + 1L ) / 2L;
          cs = (0<<CS12) | (0<<CS11) | (1<<CS10);
        }
        else
        {
          /* fix: untested */
          ocr = ( (2L * F_CPU) / (frequency * 2L * 64L) + 1L ) / 2L;
          cs = (0<<CS12) | (1<<CS11) | (1<<CS10);
        }
        OCR1A = ocr;
      #elif ( F_CPU <= 16000000 )
        /* fix: untested */
        if ( frequency > 122 )
        {
          ocr = ( (2L * F_CPU) / (frequency * 2L * 1L) + 1L ) / 2L;
          cs = (0<<CS12) | (0<<CS11) | (1<<CS10);
        }
        else
        {
          ocr = ( (2L * F_CPU) / (frequency * 2L * 256L) + 1L ) / 2L;
          cs = (1<<CS12) | (0<<CS11) | (0<<CS10);
        }
        OCR1A = ocr;
      #else
        #error "Unsupported clock frequency.  Please add code here.  See 'Arduino - Buzzer Evaluation.xlsx' for details."
      #endif

      /* Does the caller want a specific duration? */
      if ( duration > 0 )
      {
        /* Determine how many times the value toggles */
        timer1_toggle_count = (2 * frequency * duration) / 1000;

        /* Output Compare A Match Interrupt Enable */
        TIMSK1 |= (1<<OCIE1A);
      }
      else
      {
        /* Indicate to the interrupt service routine that we'll be running until further notice */
        timer1_toggle_count = -1;

        /* All pins but the OC1A pin have to be driven by software */
        if ( _pin != CORE_OC1A_PIN )
        {
          /* Output Compare A Match Interrupt Enable */
          TIMSK1 |= (1<<OCIE1A);
        }
      }

      #if DEBUG_TONE
        debug_tone_last_OCR1A = OCR1A;
      #endif

      /* Start the clock... */

      #if ( F_CPU <= 1000000 )
        /* Clock Select = 1; clkI/O/1 (No prescaling) */
        TCCR1B = (TCCR1B & ToneClockSelectMask) | (0<<CS12) | (0<<CS11) | (1<<CS10);
      #elif ( F_CPU <= 8000000 )
        /* Clock Select = 1 or 3; clkI/O/1 (No prescaling) or clkI/O/64 (From prescaler) */
        TCCR1B = (TCCR1B & ToneClockSelectMask) | cs;
      #elif ( F_CPU <= 16000000 )
        /* Clock Select = 1 or 4; clkI/O/1 (No prescaling) or clkI/O/256 (From prescaler) */
        TCCR1B = (TCCR1B & ToneClockSelectMask) | cs;
      #else
        #error "Unsupported clock frequency.  Please add code here.  See 'Arduino - Buzzer Evaluation.xlsx' for details."
      #endif

      #if DEBUG_TONE
        debug_tone_last_TCCR1A = TCCR1A;
        debug_tone_last_TCCR1B = TCCR1B;
      #endif
    }
    else
    {
      /* To be on the safe side, turn off all interrupts */
      TIMSK1 = (0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (0<<TOIE1);

      /* Clock is stopped.  Counter is zero.  The only thing left to do is turn off the output. */
      digitalWrite( _pin, 0 );
    }
  }
}


static void noToneInternal( void )
{
  /* Turn off all interrupts */
  TIMSK1 = (0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (0<<TOIE1);

  /* Stop the clock while we make changes. */
  TCCR1B = (TCCR1B & ToneClockSelectMask) | (0<<CS12)|(0<<CS11)|(0<<CS10);

  // Set Timer 1 exactly the same as init did...

	// put timer 1 in 8-bit phase correct pwm mode
	TCCR1A = (0<<COM1A1)|(0<<COM1A0) | (0<<COM1B1)|(0<<COM1B0) | (0<<WGM11)|(1<<WGM10);

  // set timer 1 prescale factor to 64
  // and start the timer
  TCCR1B = (0<<ICNC1) | (0<<ICES1) | (0<<WGM13)|(0<<WGM12) | (0<<CS12)|(1<<CS11)|(1<<CS10);

  /* Set the output low */
  if ( timer1_pin_register != NULL )
  {
    *timer1_pin_register &= ~(timer1_pin_mask);
  }
}


void noTone( uint8_t _pin )
{
  if ( tone_pin == _pin )
  {
    noToneInternal();
  
    if ( timer1_pin_register == NULL )
    {
      digitalWrite( _pin, LOW );
    }

    tone_pin = 255;
  }
}


ISR( TIM1_COMPA_vect )
{
  if ( timer1_toggle_count != 0 )
  {
    if ( timer1_toggle_count > 0 )
    {
      --timer1_toggle_count;

      if ( timer1_toggle_count == 0 )
      {
        /* Shutdown the hardware */
        noToneInternal();

        /* Skip the rest.  We're finished. */
        return;
      }
    }
    *timer1_pin_register ^= timer1_pin_mask;
  }
  else
  {
    /* Shutdown the hardware */
    noToneInternal();
  }
}
