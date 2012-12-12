#ifndef Pins_Arduino_ATtinyX5_h
#define Pins_Arduino_ATtinyX5_h

#include "core_build_options.h"

#define PORT_B_ID 1

#define digitalPinToPCICR(p)    (((p) >= 0 && (p) <= 5) ? (&GIMSK) : ((uint8_t *)NULL))
#define digitalPinToPCICRbit(p) (PCIE)
#define digitalPinToPCMSK(p)    (((p) >= 0 && (p) <= 5) ? (&PCMSK) : ((uint8_t *)NULL))
#define digitalPinToPCMSKbit(p) (p)


#endif