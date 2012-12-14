# avr-gcc

You will need one fresher than the stock Arduino one.

## OSX

  1. Download & Install Crosspack: http://www.obdev.at/products/crosspack/download.html
  2. Copy files (supposing bash as terminal)

        rm -rf /Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/* && pushd /usr/local/CrossPack-AVR/ && ( tar cf - * | ( cd /Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/; tar xvpf -) ) && popd

  3. Fix [issue #604](http://code.google.com/p/arduino/issues/detail?id=604&start=200) by patching wiring.h 

        for file in $( find /Applications/ -path '*/hardware/*/cores/*/wiring.h' ); do patch $file < round.patch; done;

## Linux

See above, adapt as neccessary.

## Windows

See above for the general idea, you will have to figure out how to handle the copying and patching by yourself.
