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
  return 1;			/* always changes a led */
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

void led_pattern_state_machine()
{
  static char blink_count = 0;
  if (++blink_count >= 250) {
    altern_led_pattern();
    blink_count = 0;
  }
}

/*
  Dimming led pattern functions
*/
static int blinkLimit = 0;    // state var representing reciprocal of duty cycle 
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
  static unsigned short period_inc = 1000;

  if (++blinkLimit >= 8) {  // but don't let duty cycle go below 1/7.
    blinkLimit = 0;
    if (red_on)
      curr_period = 0;      // reset buzzer period
    change_red();
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

void dimming_state_machines()
{
  blinkUpdate();
  secondUpdate();
}

/*
  Go from a high to low frequency at different rates
*/
void high_to_low_buzzer()
{
  static int count = 0;
  static unsigned short period_inc = 500;
  if (count++ >= curr_rate) { //curr_rate only change when switch 3 is press
    count = 0;
    if (curr_period > 10000)
      curr_period = 0;
    curr_period += period_inc;
    buzzer_set_period(curr_period);
  }
}

/*
  Turn leds off and stop buzzing
*/
void off_leds_buzzer()
{
  led_off();
  buzzer_set_period(100);
}

