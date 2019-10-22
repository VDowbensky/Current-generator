//========================================================================
#ifndef EVENTS_H
#define EVENTS_H

#include "events.h"

#include "avrlibtypes.h"

#include "main_def_func.h"
//========================================================================

//========================================================================
extern u08 Events [];

typedef enum num_event
{
   EV_ID_KEY_PRESSED,
   EV_ID_1,
   EV_ID_2,
   EV_ID_3,
   EV_ID_4,
   MAX_ID_EVENTS,
} num_event;

#define SET_CLR_EVENT      1
#define SET_USER_CLR_EVENT 3
//------------------------------------------------------------------------
void set_event (u08 a);
//========================================================================

extern void Init_Events (void);
extern bool Get_Event (u08 event);
extern void Set_Event (u08 event, u08 status);
extern void Process_Events (void);

#endif