# AVRDude config

You need to add the config section in avrdude.conf to your the avrdude.conf you are using, on OSX it would be

    cp /Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/etc/avrdude.conf /Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/etc/avrdude.conf.backup && cat avrdude_tiny1634.conf >>/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/etc/avrdude.conf

This must be done *after* updating [avr-gcc](../avr-gcc/)

## TODO:

  * Use grep to check if the config is defined before appending
