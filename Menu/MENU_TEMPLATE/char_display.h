#ifndef CHAR_DISPLAY_H

#define CHAR_DISPLAY_H

#include "char_display.h"

#include <ioavr.h>

#include "avrlibtypes.h"
#include "macros.h"
#include "main_def_func.h"

//========================================================================
#define LCD             0
#define VFD             1

#define TYPE_DISPLAY    VFD // LCD // 
//========================================================================

//========================================================================
 // LCD Data Port
#define DATA_PORT       PORTA
#define DATA_PIN        PINA
#define DATA_DDR        DDRA

#define CMD_PORT        PORTA // LCD Control Port
#define CMD_PIN         PINA
#define CMD_DDR         DDRA

 // Строб.
#define EN_PORT         PORTA
#define EN_DDR          DDRA

#define EN              2

 // Команда\данные.
#define RS_PORT         PORTA
#define RS_DDR          DDRA

#define RS              3
//========================================================================

//========================================================================
#define Line1           0x80 // Адрес первой строки.
#define Line2           0xC0 // Адрес второй строки.
#define Line3           0x94 // Адрес третьей строки.
#define Line4           0xD4 // Адрес четвертой строки.
//========================================================================

//========================================================================
#define DRV_LCD_TIME    1
//========================================================================

//========================================================================
#if (TYPE_DISPLAY==VFD)
extern u08 bright; // Значение яркости VFD.
// 3 - 25%
// 2 - 75%
// 1 - 50%
// 0 - 100%

#define QUANT_USERS_CHARS 4

#define ARROW_RIGHT 2
#define ARROW_LEFT 3

extern u08 __flash table_users_chars [];

extern u08 __flash table_rus_chars [];
#endif
//========================================================================

//========================================================================
void lcd_io_in (void);
void lcd_send_nibble (u08 lcd_data);
void lcd_send_byte (u08 lcd_data);
void lcd_send_com_nibble (u08 lcd_data);
void lcd_send_com (u08 lcd_data);
void lcd_send_data (u08 lcd_data);
//========================================================================

//========================================================================
void char_dsp_init (void);
//========================================================================

//========================================================================
void def_users_chars (u08 __flash *ptr);
//========================================================================

//========================================================================
extern u08 _drv_char_dsp;
//------------------------------------------------------------------------
enum
{
   DRV_CHAR_DSP_INIT_1 = 0,
   DRV_CHAR_DSP_INIT_2,
   DRV_CHAR_DSP_SET_NEXT_STATE,
   DRV_CHAR_DSP_SEND_ADDR,
   DRV_CHAR_DSP_SEND_CHAR,
};
//------------------------------------------------------------------------
extern u08 position_x;
extern u08 position_y;
//------------------------------------------------------------------------
void drv_char_dsp (void);
//========================================================================

//========================================================================
#define POSITION_MAX_X    20   // Количество символов в строке.
#define POSITION_MAX_Y    4    // Количество строк дисплея.

extern u08 dsp_buf [];

#define LineBuf1          dsp_buf
#define LineBuf2          dsp_buf+POSITION_MAX_X
#define LineBuf3          dsp_buf+(POSITION_MAX_X*2)
#define LineBuf4          dsp_buf+(POSITION_MAX_X*3)
//========================================================================

//========================================================================
extern void clr_dsp_buf (void);

extern void init_dsp_buf (void);

#define clr_string(y, x, n) _clr_string(((y)-1)*POSITION_MAX_X+((x)-1), (n))
void _clr_string (u08 x, u08 n);
//========================================================================

#endif