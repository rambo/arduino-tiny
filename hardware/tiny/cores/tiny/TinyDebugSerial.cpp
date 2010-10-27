#include "TinyDebugSerial.h"

static TinyDebugSerialWriter stub;

void TinyDebugSerial::useStub( void )
{
  _writer = &stub;
  _writer->init();
}

TinyDebugSerial::TinyDebugSerial( void )
{
  useStub();
}

TinyDebugSerial Serial;
