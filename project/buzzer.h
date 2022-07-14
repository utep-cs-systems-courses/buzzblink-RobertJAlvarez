#ifndef buzzer_included
#define buzzer_included

void buzzer_init();
void buzzer_set_period(unsigned short cycles);

extern unsigned short curr_rate;
extern unsigned short curr_period;

#endif // included
