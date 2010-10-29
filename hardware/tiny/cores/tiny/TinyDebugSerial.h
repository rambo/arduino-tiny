#ifndef TinyDebugSerial_h
#define TinyDebugSerial_h

#include <inttypes.h>

#include "binary.h"
#include "Stream.h"


class TinyDebugSerialWriter;
class TinyDebugSerial;


class TinyDebugSerialWriter
{
  protected:

    virtual void init( void )
    {
    }

    virtual void write( uint8_t )
    {
    }

  friend class TinyDebugSerial;
};

void TinyDebugSerialWriterInternalBug( void ) __attribute__((error("Serial (TinyDebugSerial) has an internal problem.  Contact the developer.")));

static inline void TinyDebugSerialWriterBangOneByte( uint8_t value, uint8_t SER_REG, uint8_t SER_BIT, uint8_t lom, uint8_t him, uint8_t oloops, uint8_t iloops, uint8_t nops ) __attribute__((always_inline, unused));
static inline void TinyDebugSerialWriterBangOneByte( uint8_t value, uint8_t SER_REG, uint8_t SER_BIT, uint8_t lom, uint8_t him, uint8_t oloops, uint8_t iloops, uint8_t nops )
{
  if ( __builtin_constant_p( SER_REG ) 
      && __builtin_constant_p( SER_BIT ) 
      && __builtin_constant_p( lom ) 
      && __builtin_constant_p( him )
      && __builtin_constant_p( oloops ) 
      && __builtin_constant_p( iloops ) 
      && __builtin_constant_p( nops ) )
  {
      uint8_t i;
      uint8_t j;
      uint8_t ol;
      uint8_t il;
      uint8_t b;  // Initialized to the low bits
      uint8_t hib;
      uint8_t m;
      
      b   = ((value << 1) & 0x1F);
      hib = ((value >> 4) & 0x1F) | 0x10;
      
      asm volatile
      (
        "ldi   %[j], 2"                           "\n\t"
        "ldi   %[i], 5"                           "\n\t"
        "ldi   %[m], %[lom]"                      "\n\t"

        // Note: 8 MHz, 9600 baud ---> disabling interrupts does not appear to be necessary

        "cli"                                     "\n\t"

        "rjmp  L%=ntop"                           "\n\t"

      "L%=btop: "
        "nop"                                     "\n\t"      // ---> 7
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //

      "L%=ntop: "
        "ror   %[b]"                              "\n\t"      // ---> 1
        
        "brcs  L%=bxh"                            "\n\t"      // 1  (not taken) 
        "cbi   %[serreg], %[serbit]"              "\n\t"      // 2
        "rjmp  L%=bxz"                            "\n\t"      // 2 
        
      "L%=bxh: "                                              // 2  (taken) 
        "sbi   %[serreg], %[serbit]"              "\n\t"      // 2
        "nop"                                     "\n\t"      // 1 

                                                              // ---> 5
      "L%=bxz: "

        "ror   %[m]"                              "\n\t"      // ---> 3 or 4 
        "brcc  L%=bnoe"                           "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
      "L%=bnoe: "

                                                              // ---> 1
      ".if %[oloops] >= 1"                        "\n\t"      // if oloops >= 1 then...
        "ldi   %[ol], %[oloops]"                  "\n\t"      // 4*oloops + oloops*(3*iloops) or oloops*((3*iloops)+4)
      "L%=odelay: "                               "\n\t"
      ".endif"                                    "\n\t"
        "ldi   %[il], %[iloops]"                  "\n\t"      // if oloops == 0 then...
      "L%=idelay: "                               "\n\t"      // (3*iloops)
        "dec   %[il]"                             "\n\t"
        "brne  L%=idelay"                         "\n\t"
        "nop"                                     "\n\t"
      ".if %[oloops] >= 1"                        "\n\t"
        "dec   %[ol]"                             "\n\t"
        "brne  L%=odelay"                         "\n\t"
        "nop"                                     "\n\t"
      ".endif"                                    "\n\t"

      ".if %[nops] >= 1"                          "\n\t"
        "nop"                                     "\n\t"      //
      ".endif"                                    "\n\t"
      ".if %[nops] >= 2"                          "\n\t"
        "nop"                                     "\n\t"      //
      ".endif"                                    "\n\t"

        "dec   %[i]"                              "\n\t"      // ---> 3
        "brne  L%=btop"                           "\n\t"      //
        "nop"                                     "\n\t"      //

        "dec   %[j]"                              "\n\t"      // ---> 7
        "breq  L%=bfin"                           "\n\t"      //
        "ldi   %[i], 5"                           "\n\t"      //
        "mov   %[b], %[hib]"                      "\n\t"      //
        "ldi   %[m], %[him]"                      "\n\t"      //
        "rjmp  L%=ntop"                           "\n\t"      //

      "L%=bfin: "

        "sei"                                     "\n\t"
        : 
          [i] "=&r" ( i ),
          [j] "=&r" ( j ),
          [ol] "=&r" ( ol ),
          [il] "=&r" ( il ),
          [m] "=&r" ( m )
        : 
          [b] "r" ( b ),
          [hib] "r" ( hib ),
          [serreg] "I" ( SER_REG ),
          [serbit] "M" ( SER_BIT ),
          [lom] "M" ( lom ),
          [him] "M" ( him ),
          [oloops] "M" ( oloops ),
          [iloops] "M" ( iloops ),
          [nops] "M" ( nops )
        :
          "r31",
          "r30"
      );
  }
  else
  {
    TinyDebugSerialWriterInternalBug();
  }
}


template
  <
    uint8_t SER_REG,
    uint8_t SER_BIT
  >
class TinyDebugSerialWriter_1_9600 : public TinyDebugSerialWriter
{
  protected:

    virtual void init( void )
    {
      asm volatile
      (
        "sbi   %[serreg]-1, %[serbit]"            "\n\t"
        "sbi   %[serreg], %[serbit]"              "\n\t"
        : 
        : 
          [serreg] "I" ( SER_REG ),
          [serbit] "I" ( SER_BIT )
        :
      );
    }

    virtual void write( uint8_t value )
    {
      TinyDebugSerialWriterBangOneByte( value, SER_REG, SER_BIT, B00100, B00010, 0, 28, 2 );
/* rmv
      uint8_t i;
      uint8_t j;
      uint8_t k;
      // rmv uint8_t lob;
      uint8_t b;  // Initialized to the low bits
      uint8_t hib;
      // rmv uint8_t lom;
      // rmv uint8_t him;
      uint8_t m;
      
      // rmv lob = ((value << 1) & 0x1F);
      b   = ((value << 1) & 0x1F);
      hib = ((value >> 4) & 0x1F) | 0x10;
      
      // rmv lom = B00100;
      // rmv him = B00010;
      
      asm volatile
      (
        "ldi   %[j], 2"                           "\n\t"
        "ldi   %[i], 5"                           "\n\t"
//rmv   "mov   %[b], %[lob]"                      "\n\t"
        "ldi   %[m], %[lom]"                      "\n\t"

//rmv   "ldi   r31, hi8( .L%=bnopj )"             "\n\t"
//rmv   "ldi   r30, lo8( .L%=bnopj )"             "\n\t"
//rmv   "lsr   r31"                               "\n\t"
//rmv   "ror   r30"                               "\n\t"
//rmv   "adiw  r30, 1"                            "\n\t"

        "cli"                                     "\n\t"

        "rjmp  L%=ntop"                           "\n\t"

      "L%=btop: "
        "nop"                                     "\n\t"      // ---> 7
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //

      "L%=ntop: "
        "ror   %[b]"                              "\n\t"      // ---> 1
        
        "brcs  L%=bxh"                            "\n\t"      // 1  (not taken) 
//rmv   "nop"                                     "\n\t"      // 1 
        "cbi   %[serreg], %[serbit]"              "\n\t"      // 2
        "rjmp  L%=bxz"                            "\n\t"      // 2 
        
      "L%=bxh: "                                              // 2  (taken) 
        "sbi   %[serreg], %[serbit]"              "\n\t"      // 2
//rmv   "nop"                                     "\n\t"      // 1 
        "nop"                                     "\n\t"      // 1 

                                                              // ---> 5  // rmv 6
      "L%=bxz: "

        "ror   %[m]"                              "\n\t"      // ---> 3 or 4 
        "brcc  L%=bnoe"                           "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
      "L%=bnoe: "

        "ldi   %[k], %[iloops]"                    "\n\t"      // ---> 1
      "L%=idelay: "
        "dec   %[k]"                              "\n\t"      // always 3 per loop
        "brne  L%=idelay"                         "\n\t"      //
        "nop"                                     "\n\t"      //

//rmv  "ijmp"                                    "\n\t"      // ---> 2
//rmv".L%=bnopj: "
//rmv   "nop"                                     "\n\t"      // two extra
//rmv   "nop"                                     "\n\t"      //
                                                              // 3*27 + 2 = 83 cycles
      ".if %[nops] >= 1"                          "\n\t"
        "nop"                                     "\n\t"      //
      ".endif"                                    "\n\t"
      ".if %[nops] >= 2"                          "\n\t"
        "nop"                                     "\n\t"      //
      ".endif"                                    "\n\t"

        "nop"                                     "\n\t"      // rmv
        "nop"                                     "\n\t"      // rmv
        "nop"                                     "\n\t"      // rmv
        "nop"                                     "\n\t"      // rmv
        "nop"                                     "\n\t"      // rmv
        "nop"                                     "\n\t"      // rmv

//      "nop"                                     "\n\t"      // rmv

        "dec   %[i]"                              "\n\t"      // ---> 3
        "brne  L%=btop"                           "\n\t"      //
        "nop"                                     "\n\t"      //

        "dec   %[j]"                              "\n\t"      // ---> 7
        "breq  L%=bfin"                           "\n\t"      //
        "ldi   %[i], 5"                           "\n\t"      //
        "mov   %[b], %[hib]"                      "\n\t"      //
        "ldi   %[m], %[him]"                      "\n\t"      //
        "rjmp  L%=ntop"                           "\n\t"      //

      "L%=bfin: "

        "sei"                                     "\n\t"
        : 
          [i] "=&r" ( i ),
          [j] "=&r" ( j ),
          [k] "=&r" ( k ),
//rmv     [b] "=&r" ( b ),
          [m] "=&r" ( m )
        : 
          [serreg] "I" ( SER_REG ),
          [serbit] "I" ( SER_BIT ),
//rmv     [lob] "r" ( lob ),
          [b] "r" ( b ),
          [hib] "r" ( hib ),
          [iloops] "I" ( 28 ),
          [nops] "I" ( 2 ),
          [lom] "I" ( B00100 ),
          [him] "I" ( B00010 )
        :
          "r31",
          "r30"
      );
*/
    }
};


template
  <
    uint8_t SER_REG,
    uint8_t SER_BIT
  >
class TinyDebugSerialWriter_1_38400 : public TinyDebugSerialWriter
{
  protected:

    virtual void init( void )
    {
      asm volatile
      (
        "sbi   %[serreg]-1, %[serbit]"            "\n\t"
        "sbi   %[serreg], %[serbit]"              "\n\t"
        : 
        : 
          [serreg] "I" ( SER_REG ),
          [serbit] "I" ( SER_BIT )
        :
      );
    }

    virtual void write( uint8_t value )
    {
      TinyDebugSerialWriterBangOneByte( value, SER_REG, SER_BIT, B00000, B00000, 0, 2, 0 );
/*rmv
      uint8_t i;
      uint8_t j;
      uint8_t k;
      uint8_t lob;
      uint8_t hib;
      uint8_t b;
      uint8_t lom;
      uint8_t him;
      uint8_t m;
      
      lob = ((value << 1) & 0x1F);
      hib = ((value >> 4) & 0x1F) | 0x10;
      
      lom = B00000;
      him = B00000;
      
      asm volatile
      (
        "ldi   %[j], 2"                           "\n\t"
        "ldi   %[i], 5"                           "\n\t"
        "mov   %[b], %[lob]"                      "\n\t"
        "mov   %[m], %[lom]"                      "\n\t"

        "cli"                                     "\n\t"

        "rjmp  L%=ntop"                           "\n\t"

      "L%=btop: "
        "nop"                                     "\n\t"      // ---> 7
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //

      "L%=ntop: "
        "ror   %[b]"                              "\n\t"      // ---> 1
        
        "brcs  L%=bxh"                            "\n\t"      // 1  (not taken) 
        "nop"                                     "\n\t"      // 1 
        "cbi   %[serreg], %[serbit]"              "\n\t"      // 2
        "rjmp  L%=bxz"                            "\n\t"      // 2 
        
      "L%=bxh: "                                              // 2  (taken) 
        "sbi   %[serreg], %[serbit]"              "\n\t"      // 2
        "nop"                                     "\n\t"      // 1 
        "nop"                                     "\n\t"      // 1 

                                                              // ---> 6
      "L%=bxz: "

        "ror   %[m]"                              "\n\t"      // ---> 3 or 4 
        "brcc  L%=bnoe"                           "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      //
      "L%=bnoe: "

        "ldi   %[k], 1"                           "\n\t"      // ---> 1
      "L%=idelay: "
        "dec   %[k]"                              "\n\t"      // always 3 per loop
        "brne  L%=idelay"                         "\n\t"      //
        "nop"                                     "\n\t"      //
        "nop"                                     "\n\t"      // two extra
        "nop"                                     "\n\t"      //
                                                              // 3*27 + 2 = 83 cycles

        "dec   %[i]"                              "\n\t"      // ---> 3
        "brne  L%=btop"                           "\n\t"      //
        "nop"                                     "\n\t"      //

        "dec   %[j]"                              "\n\t"      // ---> 7
        "breq  L%=bfin"                           "\n\t"      //
        "ldi   %[i], 5"                           "\n\t"      //
        "mov   %[b], %[hib]"                      "\n\t"      //
        "mov   %[m], %[him]"                      "\n\t"      //
        "rjmp  L%=ntop"                           "\n\t"      //

      "L%=bfin: "

        "sei"                                     "\n\t"
        : 
        : 
          [i] "r" ( i ),
          [j] "r" ( j ),
          [k] "r" ( k ),
          [lob] "r" ( lob ),
          [hib] "r" ( hib ),
          [b] "r" ( b ),
          [lom] "r" ( lom ),
          [him] "r" ( him ),
          [m] "r" ( m ),
          [serreg] "I" ( SER_REG ),
          [serbit] "I" ( SER_BIT )
        :
      );
*/
    }
};


template
  <
    uint8_t SER_REG,
    uint8_t SER_BIT
  >
class TinyDebugSerialWriter_1_115200 : public TinyDebugSerialWriter
{
  protected:

    virtual void init( void )
    {
      asm volatile
      (
        "sbi   %[serreg]-1, %[serbit]"            "\n\t"
        "sbi   %[serreg], %[serbit]"              "\n\t"
        : 
        : 
          [serreg] "I" ( SER_REG ),
          [serbit] "I" ( SER_BIT )
        :
      );
    }

    virtual void write( uint8_t value )
    {
      asm volatile
      (
        "cli"                                     "\n\t"

        "cbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- 0 */
        "ror   %[value]"                          "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
        
        "brcs  L%=b0h"                            "\n\t"      /* 1  (not taken) */
        "nop"                                     "\n\t"      /* 1 */
        "cbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- st is 9 cycles */
        "rjmp  L%=b0z"                            "\n\t"      /* 2 */
      "L%=b0h: "                                              /* 2  (taken) */
        "sbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- st is 9 cycles */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
      "L%=b0z: "
        "ror   %[value]"                          "\n\t"      /* 1 */

        "nop"                                     "\n\t"      /* 1 */

        "brcs  L%=b1h"                            "\n\t"      /* 1  (not taken) */
        "nop"                                     "\n\t"      /* 1 */
        "cbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b0 is 8 cycles */
        "rjmp  L%=b1z"                            "\n\t"      /* 2 */
      "L%=b1h: "                                              /* 2  (taken) */
        "sbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b0 is 8 cycles */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
      "L%=b1z: "
        "ror   %[value]"                          "\n\t"      /* 1 */

        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */

        "brcs  L%=b2h"                            "\n\t"      /* 1  (not taken) */
        "nop"                                     "\n\t"      /* 1 */
        "cbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b1 is 9 cycles */
        "rjmp  L%=b2z"                            "\n\t"      /* 2 */
      "L%=b2h: "                                              /* 2  (taken) */
        "sbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b1 is 9 cycles */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
      "L%=b2z: "
        "ror   %[value]"                          "\n\t"      /* 1 */

        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */

        "brcs  L%=b3h"                            "\n\t"      /* 1  (not taken) */
        "nop"                                     "\n\t"      /* 1 */
        "cbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b2 is 9 cycles */
        "rjmp  L%=b3z"                            "\n\t"      /* 2 */
      "L%=b3h: "                                              /* 2  (taken) */
        "sbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b2 is 9 cycles */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
      "L%=b3z: "
        "ror   %[value]"                          "\n\t"      /* 1 */

        "nop"                                     "\n\t"      /* 1 */

        "brcs  L%=b4h"                            "\n\t"      /* 1  (not taken) */
        "nop"                                     "\n\t"      /* 1 */
        "cbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b3 is 8 cycles */
        "rjmp  L%=b4z"                            "\n\t"      /* 2 */
      "L%=b4h: "                                              /* 2  (taken) */
        "sbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b3 is 8 cycles */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
      "L%=b4z: "
        "ror   %[value]"                          "\n\t"      /* 1 */

        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */

        "brcs  L%=b5h"                            "\n\t"      /* 1  (not taken) */
        "nop"                                     "\n\t"      /* 1 */
        "cbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b4 is 9 cycles */
        "rjmp  L%=b5z"                            "\n\t"      /* 2 */
      "L%=b5h: "                                              /* 2  (taken) */
        "sbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b4 is 9 cycles */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
      "L%=b5z: "
        "ror   %[value]"                          "\n\t"      /* 1 */

        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */

        "brcs  L%=b6h"                            "\n\t"      /* 1  (not taken) */
        "nop"                                     "\n\t"      /* 1 */
        "cbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b5 is 9 cycles */
        "rjmp  L%=b6z"                            "\n\t"      /* 2 */
      "L%=b6h: "                                              /* 2  (taken) */
        "sbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b5 is 9 cycles */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
      "L%=b6z: "
        "ror   %[value]"                          "\n\t"      /* 1 */

        "nop"                                     "\n\t"      /* 1 */

        "brcs  L%=b7h"                            "\n\t"      /* 1  (not taken) */
        "nop"                                     "\n\t"      /* 1 */
        "cbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b6 is 8 cycles */
        "rjmp  L%=b7z"                            "\n\t"      /* 2 */
      "L%=b7h: "                                              /* 2  (taken) */
        "sbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b6 is 8 cycles */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
      "L%=b7z: "
        "nop"                                     "\n\t"      /* 1 */

        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */

        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
        "sbi   %[serreg], %[serbit]"              "\n\t"      /* 2  <--- b7 is 9 cycles */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
        "nop"                                     "\n\t"      /* 1 */
                                                              /*    <---sp is 9 cycles */

        "sei"                                     "\n\t"

        : 
        : 
          [value] "r" ( value ),
          [serreg] "I" ( SER_REG ),
          [serbit] "I" ( SER_BIT )
      );
    }
};


template
  <
    uint8_t SER_REG,
    uint8_t SER_BIT
  >
class TinyDebugSerialWriter_8_9600 : public TinyDebugSerialWriter
{
  protected:

    virtual void init( void )
    {
      asm volatile
      (
        "sbi   %[serreg]-1, %[serbit]"            "\n\t"
        "sbi   %[serreg], %[serbit]"              "\n\t"
        : 
        : 
          [serreg] "I" ( SER_REG ),
          [serbit] "I" ( SER_BIT )
        :
      );
    }

    virtual void write( uint8_t value )
    {
      TinyDebugSerialWriterBangOneByte( value, SER_REG, SER_BIT, B01001, B00100, 3, 89, 0 );
    }
};


template
  <
    uint8_t SER_REG,
    uint8_t SER_BIT
  >
class TinyDebugSerialWriter_8_38400 : public TinyDebugSerialWriter
{
  protected:

    virtual void init( void )
    {
      asm volatile
      (
        "sbi   %[serreg]-1, %[serbit]"            "\n\t"
        "sbi   %[serreg], %[serbit]"              "\n\t"
        : 
        : 
          [serreg] "I" ( SER_REG ),
          [serbit] "I" ( SER_BIT )
        :
      );
    }

    virtual void write( uint8_t value )
    {
      TinyDebugSerialWriterBangOneByte( value, SER_REG, SER_BIT, B01001, B00100, 0, 62, 2 );
    }
};


template
  <
    uint8_t SER_REG,
    uint8_t SER_BIT
  >
class TinyDebugSerialWriter_8_115200 : public TinyDebugSerialWriter
{
  protected:

    virtual void init( void )
    {
      asm volatile
      (
        "sbi   %[serreg]-1, %[serbit]"            "\n\t"
        "sbi   %[serreg], %[serbit]"              "\n\t"
        : 
        : 
          [serreg] "I" ( SER_REG ),
          [serbit] "I" ( SER_BIT )
        :
      );
    }

    virtual void write( uint8_t value )
    {
      TinyDebugSerialWriterBangOneByte( value, SER_REG, SER_BIT, B01010, B10100, 0, 16, 1 );
    }
};


#if F_CPU == 1000000L
  typedef TinyDebugSerialWriter_1_9600<0x18,3> TinyDebugSerialWriter_9600;
  typedef TinyDebugSerialWriter_1_38400<0x18,3> TinyDebugSerialWriter_38400;
  typedef TinyDebugSerialWriter_1_115200<0x18,3> TinyDebugSerialWriter_115200;
#elif F_CPU == 8000000L
  typedef TinyDebugSerialWriter_8_9600<0x18,3> TinyDebugSerialWriter_9600;
  typedef TinyDebugSerialWriter_8_38400<0x18,3> TinyDebugSerialWriter_38400;
  typedef TinyDebugSerialWriter_8_115200<0x18,3> TinyDebugSerialWriter_115200;
#elif F_CPU == 16000000L
#error 16 MHz is not support for two reasons: The default pin for Serial is also a pin used for the crystal.  The developer has not had time to test at 16 MHz.
/*
  9600...
    6, 90, 2
    7, 77, 1
  38400...
    1, 130, 2
    5, 25, 1
    18, 6, 0
  115200...
    0, 39, 1
    1, 38, 0
    2, 18, 2
    9, 3, 1
*/
#endif

extern TinyDebugSerialWriter_9600 tdsw9600;
extern TinyDebugSerialWriter_38400 tdsw38400;
extern TinyDebugSerialWriter_115200 tdsw115200;


void TinyDebugSerialBadBaud( void ) __attribute__((error("Serial (TinyDebugSerial) supports three baud rates: 9600, 38400, or 115200.")));
void TinyDebugSerialBaudMustBeConstant( void ) __attribute__((error("The baud rate for Serial (TinyDebugSerial) cannot be changed at run-time.  Use 9600, 38400, or 115200.")));


class TinyDebugSerial : public Stream
{
  protected:

    TinyDebugSerialWriter* _writer;

    void useStub( void );

  public:
    
    TinyDebugSerial( void );

    inline void begin( long baud )
    {
      if ( __builtin_constant_p( baud ) )
      {
        if ( baud == 9600 )
        {
          _writer = &tdsw9600;
        }
        else if ( baud == 38400 )
        {
          _writer = &tdsw38400;
        }
        else if ( baud == 115200 )
        {
          _writer = &tdsw115200;
        }
        else
        {
          TinyDebugSerialBadBaud();
        }
      }
      else
      {
        TinyDebugSerialBaudMustBeConstant();
      }
      _writer->init();
    }

    void end( void )
    {
      useStub();
    }

    virtual int available( void )
    {
      return( 0 );
    }

    virtual int peek( void )
    {
      return( -1 );
    }

    virtual int read( void )
    {
      return( -1 );
    }

    virtual void flush( void )
    {
    }

    virtual void write( uint8_t c )
    {
      _writer->write( c );
    }

    using Print::write; // pull in write(str) and write(buf, size) from Print
};

extern TinyDebugSerial Serial;


#endif
