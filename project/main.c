#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "wdInterruptHandler.h"
#include "buzzer.h"

void main(void) 
{  
  switch_init();
  led_init();
  wdt_init();
  buzzer_init();

  buzzer_set_period(10000);
  //buzzer_set_period(1000); //start buzzing! 2MHz/100 = 2kHz

  or_sr(0x18);  // CPU off, GIE on
} 

