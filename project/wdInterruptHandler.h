#include <msp430.h>

#define SW1 BIT3		  /* switch1 is p1.3 */
#define SWITCHES SW1	/* only 1 switch on this board */

void switch_init();

void wdt_init();

/* Switch on P1 (S2) */
static int buttonDown;

void switch_interrupt_handler();

void __interrupt_vec(PORT1_VECTOR) Port_1();

void __interrupt_vec(WDT_VECTOR) WDT(); /* 250 interrupts/sec */

