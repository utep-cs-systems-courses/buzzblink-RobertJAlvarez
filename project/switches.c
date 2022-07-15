#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void switch_init()		/* setup switch */
{
  P2REN |= SWITCHES;	/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;	/* pull-ups for switches */
  P2DIR &= ~SWITCHES;	/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

unsigned short n_switch_down = 0;
void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  char n_switch = 1;
  char prev_switch = n_switch_down;
  //Get switch that was press down
  for (int i=0; i < 4; i++) {
    if ((p2val & n_switch) ? 0 : 1) { // 0 when n_switch is up
      n_switch_down = i+1;
      buzzer_set_period(100); //No buzzing!
    }
    n_switch = n_switch << 1;
  }
  //Only when bottom press the first time or when release
  if (((n_switch_down == 3) && (prev_switch != n_switch_down)) || 
      ((prev_switch == 3) && (p2val & (1 << 2)))) {
    curr_rate -= 25;
    if (curr_rate <= 25)
      curr_rate = 125;
  }
}

