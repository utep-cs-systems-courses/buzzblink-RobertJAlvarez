#include <msp430.h>
#include "led.h"

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  P1OUT &= ~LEDS;   // leds initially off
  led_changed = 1;
  led_update();
}

void led_update()
{
  if (led_changed) {
    char ledFlags = redVal[red_on] | greenVal[green_on];
    
    P1OUT &= (0xff^LEDS) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;		     // set bit for on leds
    led_changed = 0;
  }
}

