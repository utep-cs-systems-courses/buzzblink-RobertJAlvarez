#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "buzzer.h"
#include "led.h"

int main(void) {
  configureClocks();		  /* setup master oscillator, CPU & peripheral clocks */
  switch_init();
  led_init();
  enableWDTInterrupts();  /* enable periodic interrupt */
  buzzer_init();

  or_sr(0x18);		/* CPU off, GIE on */
}

