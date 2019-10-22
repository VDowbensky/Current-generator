//========================================================================
#include "events.h"
//========================================================================

//========================================================================
u08 Events [MAX_ID_EVENTS];
//========================================================================

//========================================================================
void Init_Events (void)
{
   u08 i = 0;

   while (i < MAX_ID_EVENTS)
   {
      Events [i++] = 0;
   }
}

bool Get_Event (u08 event)
{
   if (Events [event] == 2)
   {
      Events [event] = 0;
      return true;
   }
   return false;
}

void Set_Event (u08 event, u08 status)
{
   if (Events [event] == 0)
      Events [event] = status;
}

void Process_Events (void)
{
   u08 i = 0;

   while (i < MAX_ID_EVENTS)
   {
      if (Events [i] == 2)
         Events [i] = 0;
      if (Events [i] == 1)
         Events [i] = 2;

      i++;
   }
}
//========================================================================