#include <msp430.h>
#include "led.h"
#include "switches.h"

unsigned char red_on = 0, green_on = 0;
unsigned char led_changed = 0;

static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  led_changed = 1;
  led_update();
}

void led_update()
{
  if (led_changed) {
    char ledFlags = redVal[red_on] | greenVal[green_on];
    
    P1OUT &= (0xff^LEDS) | ledFlags;  // clear bit for off leds
    P1OUT |= ledFlags;		            // set bit for on leds
    led_changed = 0;
  }
}

void greenControl(int on)
{
  if (on) {
    P1OUT |= LED_GREEN;   //Turn on green light
    green_on = 1;
  } else {
    P1OUT &= ~LED_GREEN;  //Turn off green light
    green_on = 0;
  }
}

void change_red()
{
  P1OUT ^= LED_RED;
  red_on ^= 1;
}

void led_off()
{
  red_on = 0;
  green_on = 0;
  led_changed = 1;
  led_update();
}

