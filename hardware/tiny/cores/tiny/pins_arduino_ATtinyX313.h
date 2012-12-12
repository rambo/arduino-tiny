#ifndef Pins_Arduino_ATtinyX313_h
#define Pins_Arduino_ATtinyX313_h

#define PORT_A_ID 1
#define PORT_B_ID 2
#define PORT_D_ID 4

#define digitalPinToPCX(p,s1,s2,s3,s4,s5) \
    (((p) >= 0) \
        ? (((p) <=  1) ? (s1)  /*  0 -  1  ==>  D0 - D1 */  \
        : (((p) <=  3) ? (s2)  /*  2 -  3  ==>  A1 - A0 */  \
        : (((p) <=  8) ? (s3)  /*  4 -  8  ==>  D2 - D6 */  \
        : (((p) <= 16) ? (s4)  /*  9 - 16  ==>  B0 - B7 */  \
        : (s5))))) \
        : (s5))
//                                                   s1 D     s2 A     s3 D     s4 B
#define digitalPinToPCICR(p)    digitalPinToPCX( p, &GIMSK,  &GIMSK,  &GIMSK,  &GIMSK,  NULL )
#define digitalPinToPCICRbit(p) digitalPinToPCX( p, PCIE2,   PCIE1,   PCIE2,   PCIE0,   0    )
#define digitalPinToPCMSK(p)    digitalPinToPCX( p, &PCMSK2, &PCMSK1, &PCMSK2, &PCMSK0, NULL )
#define digitalPinToPCMSKbit(p) digitalPinToPCX( p, p,       3-p,     p-2,     p-9,     0    )

#endif