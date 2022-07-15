## Description
This directory contains code for a simple toy that demonstrate I/O using timer, button interrupts and sound.

Bottom number: Program                 | Description
-------------------------------------- | ----------------------------------------
1: Led pattern                         | Start a led pattern with the red and green leds.
2: Dimming led w/ buzzer               | Dim green led, toggle red light and constantly lower buzz until reset.
3: High to low buzz at different rates | Buzz from high to low frequency, rate change as the third bottom get repress or release.
4: Turn off the leds and stop buzzing  | Turn off the leds and stop buzzing.

## How to Use

The Makefile in this directory contains rules to run the Makefile. Run `make` to generate two executables, one contains C code only and the other use C and assembly code. To load the program into the MSP430 you can run `make load-c` which used C code, or `make load-s` that used C and assembly code. Run `make clean` to clean unnecessary files like object files, executables, and two libraries, 'h' and 'lib'.

You may use **mspdebug rf2500 "erase"** to clear a program from the MSP430.

