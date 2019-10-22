//========================================================================
#include "sys_timer.h"
//========================================================================

//========================================================================
u08 sys_tick;
//========================================================================

//========================================================================
#pragma vector = TIMER0_COMP_vect
__interrupt void Timer0Comp(void)
{
	ST_OCR += 250;
	sys_tick |= 1<<SYS_TICK_FLG;
}
//========================================================================

//========================================================================
void init_sys_timer (void)
{
	sys_tick = 0;
	ST_TCNT = 0;
	ST_TIMSK |= 1<<ST_OCIE;
	ST_OCR = 250;
	ST_TCCR |= (1<<CS0) | (1<<CS1);
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
struct tmrs_queue Timers_Queue [TMRS_QUANTITY];

void service_timers(void)
{
	if (sys_tick & (1<<SYS_TICK_FLG))
	{
		sys_tick &= ~ (1<<SYS_TICK_FLG);

		struct tmrs_queue *p_tmrs_queue = Timers_Queue;

      for (p_tmrs_queue = Timers_Queue; p_tmrs_queue < Timers_Queue + TMRS_QUANTITY; p_tmrs_queue++)
      {
         if (p_tmrs_queue -> tmr_flags & (1<<TMR_UNLOCK_FLG))
         {
            p_tmrs_queue -> tmr_cnt--;

            if (p_tmrs_queue -> tmr_cnt == 0)
               p_tmrs_queue -> tmr_flags |= (1<<TIME_OUT_FLG);
         }
      }
	}
}

//------------------------------------------------------------------------

//------------------------------------------------------------------------
void set_timer(u08 num_tmr, u08 flags, u16 time)
{
	struct tmrs_queue *p_tmrs_queue = Timers_Queue+num_tmr;
	p_tmrs_queue -> tmr_flags = flags | (1<<TMR_UNLOCK_FLG);
	p_tmrs_queue -> tmr_cnt = time;
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
u08 wait(u08 num_tmr)

{
	struct tmrs_queue *p_tmrs_queue = Timers_Queue+num_tmr;
	if(p_tmrs_queue -> tmr_flags & (1<<TIME_OUT_FLG))
	{
		p_tmrs_queue -> tmr_flags &= ~ (1<<TIME_OUT_FLG);
		return 1;
	}
		else
		return 0;
}
//========================================================================
