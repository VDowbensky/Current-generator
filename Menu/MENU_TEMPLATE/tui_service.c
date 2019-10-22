//========================================================================
#include "tui_service.h"

#include "typedef.h"
//========================================================================

//========================================================================
// Модуль отображения информации на дисплее. Основная идея в этом модуле :
// Параллельность с другими процессами. Считываются нужные переменные из
// других модулей и на основании значений этих переменных выводится
// соответствующая информация.
// Примечание:
// Нужно сделать механизм получения значений переменных из других модулей.
//========================================================================

//========================================================================
u08 tui_service_flags;

u08 tui_service_blink_colon;
u08 tui_service_blink_string;

u08 pos_curs;
//========================================================================

//========================================================================
// Очистка участка буфера, куда выводится режим станка.
void clr_sMode (void)
{
   clr_string (sMode, 1, POSITION_MAX_X);
}

// Очистка строки sMess (2).
void clr_sMess (void)
{
   clr_string (sMess, 1, POSITION_MAX_X);
}
//========================================================================

//========================================================================
// Вывод символа. Формат:
// Номер строки, номер знакоместа, символ.
void _PrintChar (u08 x, u08 a)
{
   dsp_buf [x] = a;
//   init_dsp_buf (); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
//========================================================================

//========================================================================
void _Print_Buf (u08 x, char __flash *data)
{
   u08 i = 0;

   while (data [i])
   {
      dsp_buf [x++] = data [i++];
   }

   init_dsp_buf ();
}
//========================================================================

//========================================================================
static u08 _tui_service_main;
static u08 _tui_service_slave;

static u08 tui_termoplast_mode;
//========================================================================

//########################################################################
//************************ Главный автомат *******************************
//########################################################################
__flash VECTORS tui_service_func [TUI_SERVICE_MAIN_STATES] =
{
#define STATE(name, func) func,
#include "_tui_service_main.h"
#undef STATE
};
//------------------------------------------------------------------------
void tui_service (void)
{
   if (_tui_service_main < TUI_SERVICE_MAIN_STATES)
   {
      if (_drv_char_dsp != DRV_CHAR_DSP_INIT_1)
      {
         if (_tui_service_main != TUI_SERVICE_MAIN_INIT)
         {
            kbd_drv ();
         }

         tui_service_func [_tui_service_main] ();
      }
   }
// Обработка ошибки значения состояния.
}
//========================================================================

//========================================================================
void Tui_Service_Main_Init ()
{
   SET_MENU_LEVEL (L_OUT_MODE);
}
//========================================================================

//========================================================================
void Tui_Service_Main_Out_Mode ()
{
   if (proc_menu_keys ()) return;
//------------------------------------------------------------------------
   switch (_tui_service_slave)
   {
      case TUI_SERVICE_OUT_MODE:
         break;

      case SERVICE_MENU_SHOW_PRESET_TEMP:
         break;

      case SERVICE_MENU_SHOW_CURR_TEMP:
         break;

      default:
         break;
   }
//------------------------------------------------------------------------
   show_mode ();                                      // Вывод режима станка.
}
//========================================================================

//========================================================================
void out_mode_init (void)
{
   tui_service_blink_colon = 0;
   tui_service_blink_string = 0;

   tui_termoplast_mode = 0xFF;

   _tui_service_main = TUI_SERVICE_MAIN_OUT_MODE;
   _tui_service_slave = TUI_SERVICE_OUT_MODE;
}
//========================================================================

//========================================================================
//--------------------- Отображение режима -------------------------------
//========================================================================
void show_mode (void)
{
   if (termoplast_mode != tui_termoplast_mode)
   {
      tui_termoplast_mode = termoplast_mode;

      switch (termoplast_mode)
      {
         case MODE_STOP:
            clr_sMode ();
            Print_Buf (sMode, 9, "СТОП");
            break;

         case MODE_MANUAL:
            clr_sMode ();
            Print_Buf (sMode, 8, "НАЛАДКА");
            break;

         case MODE_AUTOMAT:
            clr_sMode ();
            Print_Buf (sMode, 8, "АВТОМАТ");
            break;

         case MODE_STOPPING:
            clr_sMode ();
            Print_Buf (sMode, 7, "ОСТАНОВКА");
            break;

         case MODE_EMERG_STOP:
            clr_sMode ();
            Print_Buf (sMode, 4, "АВАРИЙНЫЙ СТОП!");
            break;

         default:
         	break;
      }
   }
}
//========================================================================

//========================================================================
void show_service_menu (void)
{
   u08 num = GetKeyCode ();

   switch (num)
   {
      case 0:
         clr_service_dsp_array ();
         _tui_service_slave = TUI_SERVICE_OUT_MODE;
         break;

      case 1:
         clr_service_dsp_array ();
         Print_Buf (2, 1, "ЗАДАННАЯ ТЕМПЕРАТУРА");
         Print_Buf (3, 1, "  1    2    3    4  ");
         Print_Buf (4, 1, " 160  165  170  175 ");
         _tui_service_slave = SERVICE_MENU_SHOW_PRESET_TEMP;
         break;

      case 2:
         clr_service_dsp_array ();
         Print_Buf (2, 2, "ТЕКУЩАЯ ТЕМПЕРАТУРА");
         Print_Buf (3, 1, "  1    2    3    4  ");
         Print_Buf (4, 1, " 100  105  110  115 ");
         _tui_service_slave = SERVICE_MENU_SHOW_CURR_TEMP;
         break;

      case 3:
         clr_service_dsp_array ();
         Print_Buf (2, 8, "СЧЕТЧИК");
         Print_Buf (3, 1, "ГОТОВО        ЗАДАНО");
         Print_Buf (4, 1, "000003        999999");
         _tui_service_slave = SERVICE_MENU_SHOW_COUNTER;
         break;

      default:
         break;
   }
}
//========================================================================

//========================================================================
void clr_service_dsp_array (void)
{
   clr_string (2, 1, POSITION_MAX_X);
   clr_string (3, 1, POSITION_MAX_X);
   clr_string (4, 1, POSITION_MAX_X);
}
//########################################################################

//########################################################################
void Tui_Service_Main_Parameters (void)
{
   if (proc_menu_keys ()) return;

   if ((MenuFuncPtr)) (*MenuFuncPtr)();
}
//========================================================================

//========================================================================
void menu_parameters_init (void)
{
   MenuFuncPtr = EMPTY_FUNC;

   _tui_service_main = TUI_SERVICE_MAIN_PARAMETERS;
}
//########################################################################

//=======================================================================================================================================================================================================================================================
//         NAME                       PARENT                CHILD                 NEXT                       PREV                       NUM_FUNCE          ENTER_FUNC            MENU_FUNC       TEXT
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MAKE_MENU (L_OUT_MODE,                NULL_ENTRY,           L1_I1_TEMP,           NULL_ENTRY,                NULL_ENTRY,                show_service_menu, out_mode_init,        NULL_FUNC, "ПАРАМЕТРЫ");
MAKE_MENU (L1_I1_TEMP,                L_OUT_MODE,           L2_I1_TEMP,           L1_I2_TIME,                NULL_ENTRY,                NULL_FUNC,         menu_parameters_init, NULL_FUNC, "ТЕМПЕРАТУРА");
MAKE_MENU (L1_I2_TIME,                L_OUT_MODE,           TIME_I1_COOLING,      L1_I3_SPEED,               L1_I1_TEMP,                NULL_FUNC,         menu_parameters_init, NULL_FUNC, "ВРЕМЯ");
MAKE_MENU (L1_I3_SPEED,               L_OUT_MODE,           SPEED_I1_CLOSE,       L1_I4_PRESSURE,            L1_I2_TIME,                NULL_FUNC,         menu_parameters_init, NULL_FUNC, "СКОРОСТЬ");
MAKE_MENU (L1_I4_PRESSURE,            L_OUT_MODE,           L2_I4_PRESSURE,       L1_I5_INJECTION_UNIT,      L1_I3_SPEED,               NULL_FUNC,         menu_parameters_init, NULL_FUNC, "ДАВЛЕНИЕ");
MAKE_MENU (L1_I5_INJECTION_UNIT,      L_OUT_MODE,           L2_I5_INJECTION_UNIT, L1_I6_FORM,                L1_I4_PRESSURE,            NULL_FUNC,         menu_parameters_init, NULL_FUNC, "УЗЕЛ ВПРЫСКА");
MAKE_MENU (L1_I6_FORM,                L_OUT_MODE,           L2_I6_FORM,           L1_I7_EJECTOR,             L1_I5_INJECTION_UNIT,      NULL_FUNC,         menu_parameters_init, NULL_FUNC, "ФОРМА");
MAKE_MENU (L1_I7_EJECTOR,             L_OUT_MODE,           EJECTOR,              L1_I8_COUNTER,             L1_I6_FORM,                NULL_FUNC,         menu_parameters_init, NULL_FUNC, "ВЫТАЛКИВАТЕЛЬ");
MAKE_MENU (L1_I8_COUNTER,             L_OUT_MODE,           L2_I8_COUNTER,        NULL_ENTRY,                L1_I7_EJECTOR,             NULL_FUNC,         menu_parameters_init, NULL_FUNC, "СЧЕТЧИК ИЗДЕЛИЙ");
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
MAKE_MENU (L2_I1_TEMP,                L1_I1_TEMP,           NULL_ENTRY,           NULL_ENTRY,                NULL_ENTRY,                NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  NULL_TEXT);
MAKE_MENU (L2_I4_PRESSURE,            L1_I4_PRESSURE,       NULL_ENTRY,           NULL_ENTRY,                NULL_ENTRY,                NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  NULL_TEXT);
MAKE_MENU (L2_I5_INJECTION_UNIT,      L1_I5_INJECTION_UNIT, NULL_ENTRY,           NULL_ENTRY,                NULL_ENTRY,                NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  NULL_TEXT);
MAKE_MENU (L2_I6_FORM,                L1_I6_FORM,           NULL_ENTRY,           NULL_ENTRY,                NULL_ENTRY,                NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  NULL_TEXT);

MAKE_MENU (L2_I8_COUNTER,             L1_I8_COUNTER,        NULL_ENTRY,           NULL_ENTRY,                NULL_ENTRY,                NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  NULL_TEXT);
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Время.
MAKE_MENU (TIME_I1_COOLING,           L1_I2_TIME,           NULL_ENTRY,           TIME_I2_2_LEVEL_INJECTION, NULL_ENTRY,                NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  "ОХЛАЖДЕНИЕ");
MAKE_MENU (TIME_I2_2_LEVEL_INJECTION, L1_I2_TIME,           NULL_ENTRY,           TIME_I3_PAUSE_CYCLES,      TIME_I1_COOLING,           NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  "2СТ.ВПРЫСКА");
MAKE_MENU (TIME_I3_PAUSE_CYCLES,      L1_I2_TIME,           NULL_ENTRY,           TIME_I4_INJECTION,         TIME_I2_2_LEVEL_INJECTION, NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  "МЕЖДУ ЦИКЛАМИ");
MAKE_MENU (TIME_I4_INJECTION,         L1_I2_TIME,           NULL_ENTRY,           TIME_I5_LOADING,           TIME_I3_PAUSE_CYCLES,      NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  "ВПРЫСК");
MAKE_MENU (TIME_I5_LOADING,           L1_I2_TIME,           NULL_ENTRY,           NULL_ENTRY,                TIME_I4_INJECTION,         NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  "ЗАГРУЗКА");
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Скорость.
MAKE_MENU (SPEED_I1_CLOSE,            L1_I3_SPEED,          NULL_ENTRY,           SPEED_I2_OPEN,             NULL_ENTRY,                NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  "СМЫКАНИЕ");
MAKE_MENU (SPEED_I2_OPEN,             L1_I3_SPEED,          NULL_ENTRY,           SPEED_I3_INJECTION,        SPEED_I1_CLOSE,            NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  "РАЗМЫКАНИЕ");
MAKE_MENU (SPEED_I3_INJECTION,        L1_I3_SPEED,          NULL_ENTRY,           SPEED_I4_LOADING,          SPEED_I2_OPEN,             NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  "ВПРЫСК");
MAKE_MENU (SPEED_I4_LOADING,          L1_I3_SPEED,          NULL_ENTRY,           NULL_ENTRY,                SPEED_I3_INJECTION,        NULL_FUNC,         NULL_FUNC,            NULL_FUNC,  "ЗАГРУЗКА");
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Выталкиватель.
MAKE_MENU (EJECTOR,                   L1_I7_EJECTOR,        NULL_ENTRY,           NULL_ENTRY,                NULL_ENTRY,                NULL_FUNC,         NULL_FUNC,            NULL_FUNC,   NULL_TEXT);
//=======================================================================================================================================================================================================================================================