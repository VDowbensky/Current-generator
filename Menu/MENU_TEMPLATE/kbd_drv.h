#ifndef KBD_DRV_H

#define KBD_DRV_H

#include "kbd_drv.h"

#include <ioavr.h>

#include "avrlibtypes.h"
#include "macros.h"

#include "main_def_func.h"

#include "sys_timer.h"

//========================================================================
#define DEBOUNCE_DELAY 20
#define HOLD_DELAY 1500
#define REPEAT_DELAY 125
//#define HOLD YES
//========================================================================

//========================================================================
#define TYPE_KEYS MATRIX

#define BUTTONS 0
#define MATRIX  1
//========================================================================

#if (TYPE_KEYS==BUTTONS)
//========================================================================
#define KEYS_PIN           PINA
#define KEYS_DDR           DDRA
#define KEYS_PORT          PORTA
//========================================================================
#define KEYS_DDR_ESC       DDRA
#define KEYS_DDR_ENTER     DDRA
#define KEYS_DDR_UP        DDRA
#define KEYS_DDR_DOWN      DDRA
#define KEYS_DDR_PLUS      DDRA
#define KEYS_DDR_MINUS     DDRA
#define KEYS_DDR_6         DDRA
#define KEYS_DDR_7         DDRA
//------------------------------------------------------------------------
#define KEYS_PORT_ESC      PORTA
#define KEYS_PORT_ENTER    PORTA
#define KEYS_PORT_UP       PORTA
#define KEYS_PORT_DOWN     PORTA
#define KEYS_PORT_PLUS     PORTA
#define KEYS_PORT_MINUS    PORTA
#define KEYS_PORT_6        PORTA
#define KEYS_PORT_7        PORTA
//------------------------------------------------------------------------
#define KEYS_PIN_ESC       PINA
#define KEYS_PIN_ENTER     PINA
#define KEYS_PIN_UP        PINA
#define KEYS_PIN_DOWN      PINA
#define KEYS_PIN_PLUS      PINA
#define KEYS_PIN_MINUS     PINA
#define KEYS_PIN_6         PINA
#define KEYS_PIN_7         PINA
//------------------------------------------------------------------------
#define KEY_ESC_PIN        0
#define KEY_ENTER_PIN      1
#define KEY_UP_PIN         2
#define KEY_DOWN_PIN       3
#define KEY_PLUS_PIN       4
#define KEY_MINUS_PIN      5
//------------------------------------------------------------------------
#define KEY_ESC_BIT        1<<KEY_ESC_PIN
#define KEY_ENTER_BIT      1<<KEY_ENTER_PIN
#define KEY_UP_BIT         1<<KEY_UP_PIN
#define KEY_DOWN_BIT       1<<KEY_DOWN_PIN
#define KEY_PLUS_BIT       1<<KEY_PLUS_PIN
#define KEY_MINUS_BIT      1<<KEY_MINUS_PIN

#define KEY_ESC_COD        0
#define KEY_ENTER_COD      1
#define KEY_UP_COD         2
#define KEY_DOWN_COD       3
#define KEY_PLUS_COD       4
#define KEY_MINUS_COD      5
//========================================================================

//========================================================================
#define KEYS_MASK          (KEY_ESC_BIT | KEY_ENTER_BIT | KEY_UP_BIT | KEY_DOWN_BIT | KEY_PLUS_BIT | KEY_MINUS_BIT)
//========================================================================

#elif (TYPE_KEYS==MATRIX)
//========================================================================
#define COL_DDR            DDRC
#define ROW_DDR            DDRC

#define COL_PIN            PINC
#define ROW_PIN            PINC
//------------------------------------------------------------------------
#define COL_MASK           (1<<COL_1)+(1<<COL_2)+(1<<COL_3)+(1<<COL_4)
#define ROW_MASK           (1<<ROW_1)+(1<<ROW_2)+(1<<ROW_3)+(1<<ROW_4)
//------------------------------------------------------------------------
/*
// STK-500
#define COL_1              3
#define COL_2              2
#define COL_3              1
#define COL_4              0

#define ROW_1              7
#define ROW_2              6
#define ROW_3              5
#define ROW_4              4
*/

// Плата управления.
#define COL_1              4
#define COL_2              5
#define COL_3              6
#define COL_4              7

#define ROW_1              0
#define ROW_2              1
#define ROW_3              2
#define ROW_4              3
//------------------------------------------------------------------------
#define KEY_ONE            0xEE // 1
#define KEY_TWO            0xED // 2
#define KEY_THREE          0xEB // 3
#define KEY_FOUR           0xDE // 4
#define KEY_FIVE           0xDD // 5
#define KEY_SIX            0xDB // 6
#define KEY_SEVEN          0xBE // 7
#define KEY_EIGHT          0xBD // 8
#define KEY_NINE           0xBB // 8
#define KEY_ZERO           0x7D // 0

#define KEY_A              0xE7 // A
#define KEY_ESC            KEY_A

#define KEY_B              0xD7 // B
#define KEY_ENTER          KEY_B

#define KEY_C              0xB7 // C
#define KEY_PREV           KEY_C

#define KEY_D              0x77 // D
#define KEY_NEXT           KEY_D

#define KEY_STAR           0x7E // *
#define KEY_PLUS           KEY_STAR

#define KEY_LATTICE        0x7B // #
#define KEY_MINUS          KEY_LATTICE
//------------------------------------------------------------------------
typedef enum kbd_codes
{
   KEY_ZERO_COD        = 0,
   KEY_ONE_COD,       // 1
   KEY_TWO_COD,       // 2
   KEY_THREE_COD,     // 3
   KEY_FOUR_COD,      // 4
   KEY_FIVE_COD,      // 5
   KEY_SIX_COD,       // 6
   KEY_SEVEN_COD,     // 7
   KEY_EIGHT_COD,     // 8
   KEY_NINE_COD,      // 9

   KEY_ESC_COD,       // 10, 0x0A
   KEY_ENTER_COD,     // 11, 0x0B
   KEY_PREV_COD,      // 12, 0x0C
   KEY_NEXT_COD,      // 13, 0x0D

   KEY_PLUS_COD,      // 14, 0x0E
   KEY_MINUS_COD,     // 15, 0x0F
} kbd_codes;
//========================================================================
#endif

//========================================================================
//#define KEY1_PRESSED() ((KEYS1_PIN & (1<<BIT_KEY1) == 0)
//#define KEY1_UNPRESSED() ((KEYS1_PIN & (1<<BIT_KEY1) == 1)
//========================================================================

//========================================================================
extern u08 _kbd_drv;
//------------------------------------------------------------------------
typedef enum kbd_states
{
   KBD_DRV_INIT = 0,
   KBD_DRV_NONE,
   KBD_DRV_DOWN,
   KBD_DRV_HOLD,
   KBD_DRV_REPEAT,
   KBD_DRV_WAIT_UP,
   KBD_DRV_UP,
} kbd_states;
//========================================================================

enum
{
   KEYS_PRESSED_FLG = 0,
};

//extern u08 keys_buf;

void scan_keys (void);

void kbd_drv (void);

extern struct tab_key_cod __flash tab_kbd_drv_keys_cod [];

extern u08 GetKeyCode (void);

#endif
