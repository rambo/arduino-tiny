#ifndef Pins_Arduino_ATtiny1634_h
#define Pins_Arduino_ATtiny1634_h

#include "core_build_options.h"


#define PORT_A_ID 1
#define PORT_B_ID 2
#define PORT_C_ID 3

#define digitalPinToPCX(p,s1,s2,s3,s4,s5,s6) \
    (((p) >= 0) \
        ? (((p) <   1) ? (s1)  /*  0  -  0  ==>  B0      */  \
        : (((p) <=  8) ? (s2)  /*  1  -  8  ==>  A7 - A0 */  \
        : (((p) <= 10) ? (s3)  /*  9  - 10  ==>  C5 - C4 */  \
        : (((p) <= 13) ? (s4)  /*  11 - 13  ==>  C2 - C0 */  \
        : (((p) <= 16) ? (s5)  /*  14 - 16  ==>  B3 - B1 */  \
        : (s6))))) \
        : (s6))
//                                                   s1 b     s2 A     s3 C     s3 C     s5 B
#define digitalPinToPCICR(p)    digitalPinToPCX( p, &GIMSK,  &GIMSK,  &GIMSK,  &GIMSK,  &GIMSK,  NULL )
#define digitalPinToPCICRbit(p) digitalPinToPCX( p, PCIE1,   PCIE0,   PCIE2,   PCIE2,   PCIE1,   0    )
#define digitalPinToPCMSK(p)    digitalPinToPCX( p, &PCMSK1, &PCMSK0, &PCMSK2, &PCMSK2, &PCMSK1, NULL )
#define digitalPinToPCMSKbit(p) digitalPinToPCX( p, p,       8-p,     14-p,    13-p,    17-p,    0    )



#endif