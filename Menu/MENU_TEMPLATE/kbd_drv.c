//========================================================================
#include "kbd_drv.h"
//========================================================================

//========================================================================
u08 _kbd_drv;

static u08 keys_flags;

static u08 keys_prev;
static u08 keys_curr;

static u08 keys_buf;
//========================================================================

#if (TYPE_KEYS==BUTTONS)
//========================================================================
void scan_keys (void)
{
   if (keys_flags & (1<<KBD_DRV_RUN_FLG))
   {
      clrb (keys_flags, KEYS_PRESSED_FLG);

      u08 a;

      a = ~KEYS_PIN;
      a &= KEYS_MASK;

      if (a != 0)
      {
         setb (keys_flags, KEYS_PRESSED_FLG);
      }

      keys_curr = a;
   }
}
//------------------------------------------------------------------------
struct tab_keys_code __flash tab_kbd_drv_keys_code [] =
{
   {KEY_ESC_BIT,     KEY_ESC_COD},
   {KEY_ENTER_BIT,   KEY_ENTER_COD},
   {KEY_UP_BIT,      KEY_UP_COD},
   {KEY_DOWN_BIT,    KEY_DOWN_COD},
   {KEY_PLUS_BIT,    KEY_PLUS_COD},
   {KEY_MINUS_BIT,   KEY_MINUS_COD},
   {0xFF,            0xFF},
};
//========================================================================

#elif (TYPE_KEYS==MATRIX)
//========================================================================
void scan_keys (void)
{
   if (_kbd_drv != KBD_DRV_INIT)
   {
      clr_bit (keys_flags, KEYS_PRESSED_FLG);

      u08 a = 0xFF;

      COL_DDR = COL_MASK;
   	asm("nop");
   	asm("nop");
   	asm("nop");
   	asm("nop");
   	asm("nop");
   	asm("nop");
   	asm("nop");
   	asm("nop");

   	if (!(ROW_PIN & (1<<ROW_1)))
         a &= (~(1<<7));
   	if (!(ROW_PIN & (1<<ROW_2)))
         a &= (~(1<<6));
   	if (!(ROW_PIN & (1<<ROW_3)))
         a &= (~(1<<5));
   	if (!(ROW_PIN & (1<<ROW_4)))
         a &= (~(1<<4));

      ROW_DDR = ROW_MASK;
   	asm("nop");
   	asm("nop");
   	asm("nop");
   	asm("nop");
   	asm("nop");
   	asm("nop");
   	asm("nop");
   	asm("nop");

   	if (!(COL_PIN & (1<<COL_1)))
         a &= (~(1<<3));
   	if (!(COL_PIN & (1<<COL_2)))
         a &= (~(1<<2));
   	if (!(COL_PIN & (1<<COL_3)))
         a &= (~(1<<1));
   	if (!(COL_PIN & (1<<COL_4)))
         a &= (~(1<<0));

      if (a != 0xFF)
         set_bit (keys_flags, KEYS_PRESSED_FLG);

      keys_curr = a;
   }
}
//------------------------------------------------------------------------
struct tab_key_cod __flash tab_kbd_drv_keys_cod [] =
{
   {KEY_ONE,     KEY_ONE_COD},
   {KEY_TWO,     KEY_TWO_COD},
   {KEY_THREE,   KEY_THREE_COD},
   {KEY_FOUR,    KEY_FOUR_COD},
   {KEY_FIVE,    KEY_FIVE_COD},
   {KEY_SIX,     KEY_SIX_COD},
   {KEY_SEVEN,   KEY_SEVEN_COD},
   {KEY_EIGHT,   KEY_EIGHT_COD},
   {KEY_NINE,    KEY_NINE_COD},
   {KEY_ZERO,    KEY_ZERO_COD},

   {KEY_A,       KEY_ESC_COD},
   {KEY_B,       KEY_ENTER_COD},
   {KEY_C,       KEY_PREV_COD},
   {KEY_D,       KEY_NEXT_COD},

   {KEY_STAR,    KEY_MINUS_COD},
   {KEY_LATTICE, KEY_PLUS_COD},
   {0xFF,        0xFF},
};
//========================================================================
#endif

//========================================================================
void kbd_drv (void)
{
   scan_keys ();

   switch (_kbd_drv)
   {
      case KBD_DRV_INIT:
         #if (TYPE_KEYS==BUTTONS)
         KEYS_PIN = KEYS_MASK;
         #endif

         keys_prev = 0xFF;
//         keys_buf = 0xFF;

         _kbd_drv = KBD_DRV_NONE;
         break;

      case KBD_DRV_NONE:
         if (keys_flags & (1<<KEYS_PRESSED_FLG))
         {
            keys_prev = keys_curr;
            set_timer (ST_KBD_1, NO_RERUN_TIMER, DEBOUNCE_DELAY);
            _kbd_drv = KBD_DRV_DOWN;
         }
         break;

      case KBD_DRV_DOWN:
         if (wait (ST_KBD_1))
         {
            if (keys_flags & (1<<KEYS_PRESSED_FLG) && keys_prev == keys_curr)
            {
               if (define_key_cod (keys_curr, keys_buf, tab_kbd_drv_keys_cod))
                  Set_Event (EV_ID_KEY_PRESSED, SET_CLR_EVENT);

               set_timer (ST_KBD_1, NO_RERUN_TIMER, HOLD_DELAY);
               _kbd_drv = KBD_DRV_HOLD; // KBD_DRV_WAIT_UP;
            }
            else
            _kbd_drv = KBD_DRV_NONE;
         }
         break;

      case KBD_DRV_HOLD:
      case KBD_DRV_REPEAT:
         if (!(keys_flags & (1<<KEYS_PRESSED_FLG)))
         {
            _kbd_drv = KBD_DRV_WAIT_UP;
            return;
         }

         if (keys_prev != keys_curr)
         {
            _kbd_drv = KBD_DRV_NONE;
            return;
         }

         if (wait (ST_KBD_1))
         {
            if (define_key_cod (keys_curr, keys_buf, tab_kbd_drv_keys_cod))
               Set_Event (EV_ID_KEY_PRESSED, SET_CLR_EVENT);

            set_timer (ST_KBD_1, NO_RERUN_TIMER, REPEAT_DELAY);
            _kbd_drv = KBD_DRV_REPEAT;
         }
         break;

      case KBD_DRV_WAIT_UP:
         if (!(keys_flags & (1<<KEYS_PRESSED_FLG)))
         {
             set_timer (ST_KBD_1, NO_RERUN_TIMER, DEBOUNCE_DELAY);
             _kbd_drv = KBD_DRV_UP;
         }
         break;

      case KBD_DRV_UP:
         if (wait (ST_KBD_1))
         {
            if (!(keys_flags & (1<<KEYS_PRESSED_FLG)))
               _kbd_drv = KBD_DRV_NONE;
         else
               _kbd_drv = KBD_DRV_WAIT_UP;
         }
         break;

      default:
         break;
   }
}
//========================================================================

//========================================================================
/*
u08 get_key (u08 key)
{
   u08 tmp_key = keys_buf;

   if (tmp_key != 0xFF)
   {
      if (tmp_key == key)
      {
         keys_buf = 0xFF;
         return 1;
      }
   }

   return 0;
}
*/

u08 GetKeyCode (void)
{
   return keys_buf;
}
//========================================================================