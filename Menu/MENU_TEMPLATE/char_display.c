//========================================================================
#include "char_display.h"
//========================================================================

//========================================================================
void lcd_io_in (void)
{
   DATA_DDR = DATA_DDR & 0x0F;
   DATA_PORT = DATA_PORT & 0x0F;
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
void lcd_send_nibble (u08 lcd_data)
{
   set_bit (CMD_PORT, EN);
   DATA_PORT = (DATA_PORT & 0x0F) | (lcd_data & 0xF0);
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   clr_bit (CMD_PORT, EN);
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
   asm("nop");
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
void lcd_send_byte (u08 lcd_data)
{
   DATA_DDR = (DATA_DDR | 0xF0);
   lcd_send_nibble (lcd_data);
   lcd_send_nibble (lcd_data << 4);
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
void lcd_send_com_nibble (u08 lcd_data)
{
   clr_bit (CMD_PORT, RS);
   DATA_DDR = (DATA_DDR | 0xF0);
   lcd_send_nibble (lcd_data);
   lcd_io_in ();
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
void lcd_send_com (u08 lcd_data)

{
   clr_bit (CMD_PORT, RS);
   lcd_send_byte (lcd_data);
   lcd_io_in ();
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
void lcd_send_data (u08 lcd_data)
{
   set_bit (CMD_PORT,RS);
   if (lcd_data >= 0xC0)
   {
      lcd_data = table_rus_chars [lcd_data - 0xC0];
   }
   lcd_send_byte (lcd_data);
   lcd_io_in ();
}
//========================================================================

//========================================================================
 // Инициализация дисплея.

void char_dsp_init (void)
{
   set_bit (EN_DDR, EN);
   set_bit (RS_DDR, RS);

#if (TYPE_DISPLAY == LCD)
   wait_20_ms ();

   lcd_send_com_nibble (0x30); // Установка 8-разрядного интерфейса.
   wait_5_ms ();

   lcd_send_com_nibble (0x30); // Установка 8-разрядного интерфейса.
   wait_5_ms ();

   lcd_send_com_nibble (0x30); // Установка 8-разрядного интерфейса.
   wait_5_ms ();

   lcd_send_com_nibble (0x20); // Установка 4-разрядного интерфейса.
   wait_50_us ();

   lcd_send_com (0x28); // 4-разрядный интерфейс. Двухстрочный режим.
   wait_50_us ();

 lcd_send_com(0x01); // Команда очистки дисплея.
   wait_5_ms ();

   lcd_send_com (0x06); // Инкремент счетчика адреса.
   wait_50_us ();

   lcd_send_com (0x0C); // Включение дисплея.
   wait_50_us ();

#elif (TYPE_DISPLAY == VFD)
   lcd_send_com_nibble (0x30); // Установка 8-разрядного интерфейса.
//   wait_5_ms ();

   lcd_send_com_nibble (0x30); // Установка 8-разрядного интерфейса.
//   wait_5_ms ();

   lcd_send_com_nibble (0x30); // Установка 8-разрядного интерфейса.
//   wait_5_ms ();

   lcd_send_com_nibble (0x20); // Установка 4-разрядного интерфейса.
//   wait_50_us ();

   lcd_send_com (0x28 | 3); // 4-разрядный интерфейс. Двухстрочный режим. Яркость 25 %
//   wait_50_us ();

//   lcd_send_com(0x01); // Команда очистки дисплея.
//   wait_5_ms ();

   lcd_send_com (0x06); // Инкремент счетчика адреса.
//   wait_50_us ();

   lcd_send_com (0x0C); // Включение дисплея.
//   wait_50_us ();
#endif

   def_users_chars (table_users_chars);
}
//========================================================================

//========================================================================
#if (TYPE_DISPLAY == VFD)

extern u08 __flash table_users_chars [8 * QUANT_USERS_CHARS]  = // Таблица пользовательских символов.
{
0x00, 0x04, 0x0E, 0x15, 0x15, 0x0E, 0x04, 0x04, // Ф
0x00, 0x10, 0x10, 0x10, 0x1E, 0x11, 0x11, 0x1E, // Ь
0x00, 0x08, 0x0C, 0x1E, 0x1F, 0x1E, 0x0C, 0x08,
0x00, 0x02, 0x06, 0x0F, 0x1F, 0x0F, 0x06, 0x02,
};

void def_users_chars (u08 __flash *ptr)
{
   lcd_send_com (1<<6);

   u08 a;
   u08 b;

   for (a = QUANT_USERS_CHARS; a > 0; a--)
   {
      for (b = 8; b > 0; b--)
      {
         lcd_send_data (*ptr);
         ptr++;
      }
   }
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
extern u08 __flash table_rus_chars [32] = // Таблица кириллицы. VFD поддерживает только
// заглавные русские буквы. И не все. Ф и Ь в таблице пользовательских символов.
{
//АБВГДЕЖЗ
0x41, 0x80, 0x42, 0x92, 0x81, 0x45, 0x82, 0x83,
//ИЙКЛМНОП
0x84, 0x85, 0x4B, 0x86, 0x4D, 0x48, 0x4F, 0x87,
//РСТУФХЦЧ
0x50, 0x43, 0x54, 0x88, 0x00, 0x58, 0x89, 0x8A,
//ШЩЪЫЬЭЮЯ
0x8B, 0x8C, 0x8D, 0x8E, 0x01, 0x8F, 0xAC, 0xAD,
};

/*
#elif (TYPE_DISPLAY == LCD)
void lcd_putc(unsigned char c) 
{
    if ( c == 0xA8) {     //буква 'Ё'
      c = 0xA2; 
    }
    else if ( c ==0xB8) { //буква 'ё'
      c = 0xB5; 
    }
    else if ( c >= 0xC0 ) {
      c = lcd_codepage[ c - 0xC0 ];
    }
    lcd_write( c );
}
 
unsigned  char  lcd_codepage[]=
{
  0x41,0xa0,0x42,0xa1,0xe0,0x45,0xa3,0xa4,
  0xa5,0xa6,0x4b,0xa7,0x4d,0x48,0x4f,0xa8,
  0x50,0x43,0x54,0xa9,0xaa,0x58,0xe1,0xab,
  0xac,0xe2,0xad,0xae,0x62,0xaf,0xb0,0xb1,
  0x61,0xb2,0xb3,0xb4,0xe3,0x65,0xb6,0xb7,
  0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0x6f,0xbe,
  0x70,0x63,0xbf,0x79,0xe4,0x78,0xe5,0xc0,
  0xc1,0xe6,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,
};
*/

#endif
//========================================================================

//========================================================================
// Очистка буфера дисплея.

u08 dsp_buf [POSITION_MAX_X * POSITION_MAX_Y];

void clr_dsp_buf (void)
{
   u08 i;

   for (i = 0; i < POSITION_MAX_X * POSITION_MAX_Y; i++)
      dsp_buf [i] = 0x20;

   init_dsp_buf ();
}
//========================================================================

//========================================================================
// Очистка определенного участка буфера дисплея. Формат:
// Номер строки, номер знакоместа, кол-во очищаемых знакомест.

void _clr_string (u08 x, u08 n)
{
   while (n--) dsp_buf [x++] = ' ';

   init_dsp_buf ();
}
//========================================================================

//========================================================================
// Переинициализация модуля вывода информации из буфера на дисплей.
// Чтобы обновление дисплея началось заново.

void init_dsp_buf (void)
{
   position_x = POSITION_MAX_X;
   position_y = POSITION_MAX_Y;
   _drv_char_dsp = DRV_CHAR_DSP_INIT_2;
}
//========================================================================

//========================================================================
u08 _drv_char_dsp;
static u08 next_state;

static const u08 lines [4] = {0x80, 0xC0, 0x94, 0xD4};

u08 position_x;
u08 position_y;

void drv_char_dsp (void)
{
   u08 data;

   switch (_drv_char_dsp)
   {
      case DRV_CHAR_DSP_INIT_1:
         char_dsp_init ();

         clr_dsp_buf ();

      case DRV_CHAR_DSP_INIT_2:
         position_x = 0;
         position_y = 0;

         next_state = DRV_CHAR_DSP_SEND_ADDR;
         _drv_char_dsp = DRV_CHAR_DSP_SET_NEXT_STATE;
         break;

      case DRV_CHAR_DSP_SEND_ADDR:
         if (wait (ST_DRV_CHAR_DSP))
         {
            lcd_send_com (lines [position_y]);

            next_state = DRV_CHAR_DSP_SEND_CHAR;
            _drv_char_dsp = DRV_CHAR_DSP_SET_NEXT_STATE;
         }
         break;

      case DRV_CHAR_DSP_SEND_CHAR:
         if (wait (ST_DRV_CHAR_DSP))
         {
            while (position_x < POSITION_MAX_X)
            {
               data = dsp_buf [(position_y * POSITION_MAX_X) + position_x];

               if (data >= 0xC0)
               {
                  data = table_rus_chars [data - 0xC0];
               }

               lcd_send_data (data);
               position_x++;
            }

            position_x = 0;
            position_y++;

            if (position_y >= POSITION_MAX_Y)
            {
               position_y = 0;

//               char_dsp_init ();
            }

            next_state = DRV_CHAR_DSP_SEND_ADDR;
            _drv_char_dsp = DRV_CHAR_DSP_SET_NEXT_STATE;
         }
         break;

      case DRV_CHAR_DSP_SET_NEXT_STATE:
         set_timer (ST_DRV_CHAR_DSP, NO_RERUN_TIMER, 1);
         _drv_char_dsp = next_state;
         break;

      default:
         _drv_char_dsp = DRV_CHAR_DSP_INIT_1;
         break;
   }
}
//========================================================================