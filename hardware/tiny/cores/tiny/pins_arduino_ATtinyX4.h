#ifndef Pins_Arduino_ATtinyX4_h
#define Pins_Arduino_ATtinyX4_h

#include "core_build_options.h"

#define PORT_A_ID 1
#define PORT_B_ID 2

#define digitalPinToPCICR(p)    (((p) >= 0 && (p) <= 10) ? (&GIMSK) : ((uint8_t *)NULL))
#define digitalPinToPCICRbit(p) (((p) <= 2) ? PCIE1 : PCIE0)
#define digitalPinToPCMSK(p)    (((p) <= 2) ? (&PCMSK1) : (((p) <= 10) ? (&PCMSK0) : ((uint8_t *)NULL)))
#define digitalPinToPCMSKbit(p) (((p) <= 2) ? (p) : (10 - (p)))


#endif
