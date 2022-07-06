#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"


#define SW1 BIT3		  /* switch1 is p1.3 */
#define SWITCHES SW1	/* only 1 switch on this board */

void switch_init() {
  P1REN |= SWITCHES;	/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;	/* pull-ups for switches */
  P1DIR &= ~SWITCHES;	/* set switches' bits for input */
}

void wdt_init() {
  configureClocks();		  /* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
}

void main(void) 
{  
  switch_init();
  led_init();
  configureClocks();		  /* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */

  buzzer_init();
  buzzer_set_period(10000);
  //buzzer_set_period(1000); //start buzzing! 2MHz/100 = 2kHz

  or_sr(0x18);  // CPU off, GIE on
} 

