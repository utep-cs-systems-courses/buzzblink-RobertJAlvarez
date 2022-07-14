#include "switches.h"
#include "stateMachines.h"
#include "select_SM.h"

void select_SM()
{
  switch (n_switch_down) {
  case 1:   //Alternate between toggling red & green
    led_pattern_state_machine();
    break;
  case 2:   //Dim green light, toggle red light and update buzz
    dimming_state_machines();
    break;
  case 3:   //Go from a high to low frequency at different rates
    high_to_low_buzzer();
    break;
  case 4:   //Turn leds off and stop buzzer
  default:
    off_leds_buzzer();
  }
}

