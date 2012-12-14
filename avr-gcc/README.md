# avr-gcc

You will need one fresher than the stock arduino one.

## OSX

  1. Download & Install Crosspack: http://www.obdev.at/products/crosspack/download.html
  2. Copy files (supposing bash as terminal)

    pushd /usr/local/CrossPack-AVR/ && ( tar cf - * | ( cd /Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/; tar xvpf -) ) ; popd

