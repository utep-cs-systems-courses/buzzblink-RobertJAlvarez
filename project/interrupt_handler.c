#include <msp430.h>
#include "switches.h"
#include "stateMachines.h"

// Switch on S2
void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      // did a button cause this interrupt?
    P2IFG &= ~SWITCHES;		      // clear pending sw interrupts
    switch_interrupt_handler();	// single handler for all switches
  }
}

extern char n_switch_down;

void __interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  switch (n_switch_down) {
  case 0:
    if (++blink_count >= 250) {
      state_advance();
      blink_count = 0;
    }
    break;
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  default:
    break;
  }
}
