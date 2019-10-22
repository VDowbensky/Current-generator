//========================================================================
#ifndef TUI_SERVICE_H

#define TUI_SERVICE_H

#include "tui_service.h"
//========================================================================

//========================================================================
#include "avrlibtypes.h"
#include "macros.h"

#include "main_def_func.h"

#include "char_display.h"

#include "menu.h"

#include "kbd_drv.h"

#include "bcd.h"

#include "proc_termoplast.h"
//========================================================================

//========================================================================
extern u08 tui_service_flags;

enum
{
   ENTER_VAL_FLG = 0, // Флаг-признак, что введено какое-то число.
   TUI_ERROR_FLG,
};

extern u08 tui_service_blink_colon;
extern u08 tui_service_blink_string;

extern u08 pos_curs;
//========================================================================

//========================================================================
#define sMode   1
#define sMess   2
//========================================================================

//========================================================================
void clr_sMess (void);

void clr_sMode (void);
//========================================================================

//========================================================================
extern void _PrintChar (u08 x, u08 a);
#define PrintChar(y, x, a) _PrintChar(((y)-1)*POSITION_MAX_X+((x)-1), (a))
//========================================================================

//========================================================================
//extern void _PrintFStr (u08 x, u08 __flash *ptr );
//#define PrintFStr(y, x, ptr) _PrintFStr(((y)-1)*MaxX+((x)-1), (ptr))
//------------------------------------------------------------------------
extern void _Print_Buf (u08 x, char __flash *data);
#define Print_Buf(y, x, data) _Print_Buf(((y)-1)*POSITION_MAX_X+((x)-1), (data))
//========================================================================

//************************************************************************
//************************ Главный автомат *******************************
//************************************************************************

//========================================================================
typedef enum tui_service_main_states
{
#define STATE(name, func) name,
#include "_tui_service_main.h"
#undef STATE

TUI_SERVICE_MAIN_STATES

} tui_service_main_states;
//------------------------------------------------------------------------
extern __flash VECTORS tui_service_func [TUI_SERVICE_MAIN_STATES];
//------------------------------------------------------------------------
void tui_service (void);
//------------------------------------------------------------------------
void Tui_Service_Main_Init (void);
void Tui_Service_Main_Out_Mode (void);
void Tui_Service_Main_Parameters (void);
//========================================================================

//========================================================================
enum
{
   TUI_SERVICE_OUT_MODE = 0,
   TUI_SERVICE_WAIT_ENTER_MENU,
   SERVICE_MENU_SHOW_PRESET_TEMP,
   SERVICE_MENU_SHOW_CURR_TEMP,
   SERVICE_MENU_SHOW_COUNTER,
};
//========================================================================

//========================================================================
void out_mode_init (void);
//------------------------------------------------------------------------
void show_mode (void);
//========================================================================

//========================================================================
void show_service_menu (void);
//========================================================================

//========================================================================
void clr_service_dsp_array (void);
//========================================================================

//########################################################################
enum
{
   TUI_SERVICE_I2_I1_TEMP = 0,
   TUI_SERVICE_I2_I2_TIME,
   TUI_SERVICE_I2_I3_SPEED,
   TUI_SERVICE_I2_I4_PRESSURE,
   TUI_SERVICE_I2_I5_INJECTION,
   TUI_SERVICE_I2_I6_FORM,
   TUI_SERVICE_I2_I7_EJECTOR,
   TUI_SERVICE_I2_I8_COUNTER,
};
//========================================================================

//========================================================================
void menu_parameters_init (void);

void _i2_i1_temp_init (void);

void i2_i1_temp_init (void);
void i2_i2_time_init (void);
void i2_i3_speed_init (void);

void _i2_i4_pressure_init (void);

void i2_i4_pressure_init (void);
void i2_i5_injection_unit_init (void);
void i2_i6_form_init (void);

void _i2_i7_ejector_init (void);

void i2_i7_ejector_init (void);
void i2_i8_counter_init (void);
//########################################################################

#endif