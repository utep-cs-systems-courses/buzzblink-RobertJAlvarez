//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

void change_led();

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

static char led_state = 0;
static char nCalls = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  if (nCalls >= 250) {
    nCalls = 0;
    change_led();
  }
  nCalls++;
}

void change_led()
{
  switch (led_state) {
  case (0):
    P1OUT |= LED_GREEN;
    led_state = 1;
    break;
  case (1):
    P1OUT &= ~LED_GREEN;
    led_state = 0;
    break;
  default:
    led_state = 0;
    break;
  }
}

