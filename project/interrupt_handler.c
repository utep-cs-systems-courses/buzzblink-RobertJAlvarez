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

void __interrupt_vec(WDT_VECTOR) WDT(){	//250 interrupts/sec
  static char blink_count = 0;
  switch (n_switch_down) {
  case 1:   //Alternate between toggling red & green
    if (++blink_count >= 250) {
      altern_led_pattern();
      blink_count = 0;
    }
    break;
  case 2:   //Dim green light, toggle red light and update buz
    dimmingStateMachines();
    break;
  case 3:
    high_to_low_buzzer();
    break;
  case 4:
  default:  //Turn leds off and stop buzzer
    off_leds_buzzer();
  }
}

