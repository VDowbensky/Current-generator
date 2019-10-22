//========================================================================
#include "main_def_func.h"
//========================================================================

//========================================================================
void wdt_enable (u08 a)
{
   __watchdog_reset ();

   WDTCR = (1<<WDTOE) | (1<<WDE) | a;
}

void wdt_disable (void)
{
   __watchdog_reset ();

   WDTCR |= (1<<WDTOE) | (1<<WDE);

   WDTCR = 0x00;
}
//------------------------------------------------------------------------
void ext_int0_init (void)
{
   MCUCR |= (1<<ISC01); // Прерывание по спаду фронта.
   GICR |= (1<<INT0);
}
//------------------------------------------------------------------------
void sleep_mode_init (void)
{
   MCUCR |= (1<<SE);
}

void sleep_mode_enable (void)
{
   asm("SLEEP");
   asm("NOP");
}
//========================================================================

//========================================================================
extern void empty_func (void)
{
}
//========================================================================

//========================================================================
void wait_50_us (void)
{
   u16 cnt_1 = 50;
   u16 cnt_2 = 50;

   while (cnt_1)
   {
      __watchdog_reset ();

      while (cnt_2)
      {
         cnt_2--;
      }
      cnt_1--;
   }
}

void wait_5_ms (void)
{
   u16 cnt_1 = 5000;
   u16 cnt_2 = 5000;

   while (cnt_1)
   {
      __watchdog_reset ();

      while (cnt_2)
      {
         cnt_2--;
      }
      cnt_1--;
   }
}

void wait_20_ms (void)
{
   u08 cnt = 4;

   while (cnt--)
   {
      wait_5_ms ();
   }
}

void wait_200_ms (void)
{
   u08 cnt = 10;

   while (cnt--)
   {
      wait_20_ms ();
   }
}

void wait_500_ms (void)
{
   u08 cnt = 25;

   while (cnt--)
   {
      wait_20_ms ();
   }
}

void wait_1_s (void)
{
   u08 cnt = 50;

   while (cnt--)
   {
      wait_20_ms ();
   }
}
//========================================================================

//========================================================================
void proc_sens_pwr (u08 a)
{
   if chk_sens_pwr_on
   {
      __disable_interrupt ();

         switch (a)
         {
            case NO_SAVE_EEPROM_PARAMETERS:
               break;

            case SAVE_EEPROM_PARAMETERS:
//               _oe_disable ();

               wdt_enable (WDTO_500_MS);

//               save_parameters_eeprom ();

               wdt_enable (WDTO_15_MS);
               break;

            default:
               break;
         }

         while (1) {};
   }
}
//========================================================================

//========================================================================
extern void sram_copy (u08 *s_1, u08 *s_2, u08 n)
{
   while (n--)
   {
      *s_1++ = *s_2++;
   }
}
//========================================================================

//========================================================================
u08 events;
//------------------------------------------------------------------------
void set_event (u08 a)
{
   events = a;
}
//========================================================================

//========================================================================
void proc_fsm_1 (u08 *ptr_state, void __flash *ptr_tab_fsm)
{
   void (*ptr_func) (void);

   ptr_func = EMPTY_FUNC;

   struct tab_state_func __flash *ptr = ptr_tab_fsm;

   for (; ptr -> state != 0xFF; ptr++)
   {
      if (ptr -> state == *ptr_state)
         {
            ptr_func = ptr -> ptr_func;
            break;
         }
   }
   if ((ptr_func)) (*ptr_func) ();
}
//========================================================================

//========================================================================
bool define_key_cod_1 (u08 *ptr_key_curr, u08 *ptr_key_buf, void __flash *ptr_tab_key_cod) // Функция определения кода нажатой кнопки.
{
   struct tab_key_cod __flash *ptr = ptr_tab_key_cod;

   // Если конец таблицы, то выход.
   for (; ptr -> key != 0xFF; ptr++)
   {
      // Если маска нажатой кнопки соответствует
      //значению из таблицы, то считываем код кнопки и записываем его в keys_buf.
      if (ptr -> key == *ptr_key_curr)
      {
         *ptr_key_buf = ptr -> key_cod;
         return true;
      }
   }
   return false;
}
//========================================================================

//========================================================================
void check_keys_buf_1 (u08 *ptr_keys_buf, u08 *state, void __flash *ptr_key_func)
{
   if (*ptr_keys_buf != 0xFF)
   {
      void (*ptr_func) (void);

      ptr_func = EMPTY_FUNC;

      struct tab_key_curr_next_func __flash *ptr = ptr_key_func;

      for (; ptr -> key_cod != 0xFF; ptr++)
      {
         if (ptr -> key_cod == *ptr_keys_buf && ptr -> curr_state == *state)
            {
               *ptr_keys_buf = 0xFF;
               *state = ptr -> next_state;
               ptr_func = ptr -> ptr_func;
               break;
            }
      }
      if ((ptr_func)) (*ptr_func) ();
   }
}
//========================================================================
