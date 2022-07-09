#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "buzzer.h"
#include "led.h"

char n_switch_down;

int main(void) {
  configureClocks();		  /* setup master oscillator, CPU & peripheral clocks */
  switch_init();
  led_init();
  enableWDTInterrupts();  /* enable periodic interrupt */

  buzzer_init();
  buzzer_set_period(100); //start buzzing! 2MHz/1000 = 2kHz

  or_sr(0x18);		/* CPU off, GIE on */
}

