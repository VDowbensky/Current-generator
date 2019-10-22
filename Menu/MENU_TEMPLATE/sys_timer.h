#ifndef SYS_TIMER_H

#define SYS_TIMER_H

#include "sys_timer.h"

#include <ioavr.h>

#include "avrlibtypes.h"

//========================================================================
#define ST_TCNT         TCNT0
#define ST_TIMSK        TIMSK
#define ST_OCIE         OCIE0
#define ST_OCR          OCR0
#define ST_TCCR         TCCR0
#define CS0             CS00
#define CS1             CS01
#define CS2             CS02
//========================================================================

//========================================================================
#define SYS_TICK_TIME   1 // Период системного таймера 1 мс
//========================================================================

//========================================================================
#define ST_SIZE         2
//========================================================================

//========================================================================
//--------------------- Флаги системных таймеров -------------------------
#define SYS_TICK_FLG    0
//------------------------------------------------------------------------

//------------------------------------------------------------------------
#define NO_RERUN_TIMER  0

#define TMR_UNLOCK      0 // Флаг активности таймера.
#define RERUN_TIMER     1
#define TIME_OUT        2 // Время вышло.

#define TMR_UNLOCK_FLG  1<<TMR_UNLOCK // Флаг активности таймера.
#define RERUN_TIMER_FLG 1<<RERUN_TIMER
#define TIME_OUT_FLG    1<<TIME_OUT // Время вышло.
//========================================================================

//========================================================================
extern u08 sys_tick;
//========================================================================

#define TMRS_QUANTITY   25

// typedef struct tmrs_queue {u08 st_flags; u16 st_cnt} tmrs_queue;
typedef struct tmrs_queue
{
   u08 tmr_flags;
   u16 tmr_cnt;
   u16 tmr_period;
} tmrs_queue;

extern struct tmrs_queue Timers_Queue [];

enum
{
   ST_KBD_1 = 0,
   ST_KBD_2,

   ST_PROC_KEYS_WORK_1,
   ST_PROC_KEYS_WORK_2,

   ST_DRV_CHAR_DSP,

   ST_TUI_SERVICE_COLON,
   ST_TUI_SERVICE_2,

   ST_PROC_SENS_PWR,

   ST_PROC_EMERG_STOP,

   ST_PROC_IN_OUT,

   ST_PROC_EDS_HEAT,
   ST_PROC_EDS_FORMOVKA,
   ST_PROC_EDS_PNEVMOSYEM,

   ST_PROC_EDS_T_OUT_SENS_1,
   ST_PROC_EDS_T_OUT_SENS_2,
   ST_PROC_EDS_T_OUT_SENS_3,
   ST_PROC_EDS_T_OUT_SENS_4,
};

void init_sys_timer (void);

void service_timers (void);

u08 wait (u08 num_tmr);

void set_timer (u08 num_tmr, u08 flags, u16 time);

#endif
