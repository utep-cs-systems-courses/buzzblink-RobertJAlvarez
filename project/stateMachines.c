#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

/*
  Alternate led pattern functions
*/
char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}

void altern_led_pattern()  /* alternate between toggling red & green */
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
}

/*
  Dimming led pattern functions
*/
void greenControl(int on)
{
  if (on) {
    P1OUT |= LED_GREEN;
  } else {
    P1OUT &= ~LED_GREEN;
  }
}

// blink state machine
static int blinkLimit = 5;    // state var representing reciprocal of duty cycle 
void blinkUpdate()            // called every 1/250s to blink with duty cycle 1/blinkLimit
{
  static int blinkCount = 0;  // state var representing blink state
  if (blinkCount++ >= blinkLimit) {
    blinkCount = 0;
    greenControl(1);
  } else
    greenControl(0);
}

void oncePerSecond() // repeatedly start bright and gradually lower duty cycle, one step/sec
{
  static unsigned short period_inc = 2000;
  static unsigned short curr_period = 0;

  if (++blinkLimit >= 8) {  // but don't let duty cycle go below 1/7.
    blinkLimit = 0;
    curr_period = 0;
  }
  curr_period += period_inc;
  buzzer_set_period(curr_period);
}

void secondUpdate()  // called every 1/250 sec to call oncePerSecond once per second
{
  static int secondCount = 0; // state variable representing repeating time 0…1s
  if (secondCount++ >= 250) { // once each second
    secondCount = 0;
    oncePerSecond();
  }
}

void dimmingStateMachines() // called every 1/250 sec
{
  blinkUpdate();
  secondUpdate();
}

