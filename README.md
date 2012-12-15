# Instructions for the ATtiny1634 branch

Since this branch is still under development I suggest cloning the repository
rather than downloading a [zip](https://github.com/rambo/arduino-tiny/zipball/attiny1634)

Remember to change your actibe branch to "attiny1634" after cloning.

## Installing

  1. See the [readme.txt](readme.txt) for upstream instructions but do not follow them yet.
  2. Get a copy of the repo (clone recommended, zip works too)
  3. Locate/Create the "hardware" directory as in upstream instructions, then copy or link
     (depending on if you have zipped copy or cloned repo) the repo hardware/tiny and hardware/tools
     under the sketchbook "hardware" directory.
  4. Locate/Create "libraries" directory under your Arduino sketchbook, copy/link the libraries
     from this repo there should you think you need them.
  5. Update the compiler toolchain in your Arduino IDE, see [avr-gcc -directory](https://github.com/rambo/arduino-tiny/tree/attiny1634/avr-gcc/)
  6. Update avrdude configuration  in your Arduino IDE, see [avrdude -directory](https://github.com/rambo/arduino-tiny/tree/attiny1634/avrdude/)
  
Remember that the Arduino IDE must not be running when you do this.

