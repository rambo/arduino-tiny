#ifndef WProgram_h
#define WProgram_h

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <avr/interrupt.h>

#include "wiring.h"

#ifdef __cplusplus
#include "WString.h"
#include "TinyDebugSerial.h"

uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration = 0);
void noTone(uint8_t _pin);

// WMath prototypes
long random(long);
long random(long, long);
void randomSeed(unsigned int);
long map(long, long, long, long, long);

const static uint8_t A0 = 11;
const static uint8_t A1 = 12; 
const static uint8_t A2 = 13;
const static uint8_t A3 = 14;
const static uint8_t A4 = 15;
const static uint8_t A5 = 16;
const static uint8_t A6 = 17;
const static uint8_t A7 = 18;

#endif

#endif
