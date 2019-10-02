// timer.h
// Define a macro which calculates the delta time between two time values.
// NOTE: FOR THIS TO WORK BOTH VALUES MUST BE OF THE SAME TYPE, AND THE TYPE MUST BE UNSIGNED.

#include <stdbool.h>

#define	TMR_DELTA_TIME(current,prev)	( ((current)>=(prev)) ? ((current) - (prev)) : ((current) + ~(prev) + 1U) )

extern void		tmr_init( unsigned long p_interval);
extern unsigned long	tmr_get_timer0( void);

extern bool tmr_poll(void);
