#ifndef switches_included
#define switches_included

#define SWITCHES 15	// All switches from 0-3

void switch_init();
void switch_interrupt_handler();

extern unsigned short n_switch_down;

#endif // included
