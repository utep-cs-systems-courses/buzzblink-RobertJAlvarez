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
  switch (n_switch_down) {
  case 1:   //Alternate between toggling red & green
    led_pattern_state_machine();
    break;
  case 2:   //Dim green light, toggle red light and update buz
    dimming_state_machines();
    break;
  case 3:
    high_to_low_buzzer();
    break;
  case 4:
  default:  //Turn leds off and stop buzzer
    off_leds_buzzer();
  }
}

