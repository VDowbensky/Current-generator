//========================================================================
#ifndef MAIN_DEF_FUNC_H

#define MAIN_DEF_FUNC_H

#include "main_def_func.h"
//========================================================================

//========================================================================
#define F_CPU 16000000UL
//------------------------------------------------------------------------
//#define PROJECT_MODE WORK

//#define WORK 0
//#define DEBUG 1
//------------------------------------------------------------------------
#include <ioavr.h>
#include <intrinsics.h>
#include <stdbool.h>

#include "avrlibtypes.h"
#include "macros.h"

#include "typedef.h"

#include "sys_timer.h" // init_sys_timer, service_timers

#include "events.h"

#include "char_display.h" // drv_char_dsp

#include "tui_service.h"

#include "menu.h"
//========================================================================

//========================================================================
//#define WDTOE WDCE

#define WDTO_15_MS 0
#define WDTO_30_MS 1
#define WDTO_60_MS 2
#define WDTO_120_MS 3
#define WDTO_250_MS 4
#define WDTO_500_MS 5
#define WDTO_1_S 6
#define WDTO_2_S 7

void wdt_enable (u08 a);

void wdt_disable (void);

void enable_interrupt (void);

void disable_interrupt (void);

void ext_int0_init (void);

void sleep_mode_init (void);
void sleep_mode_enable (void);
//========================================================================

//========================================================================
extern void empty_func (void);

#define EMPTY_FUNC 0
//========================================================================

//========================================================================
void wait_50_us (void);
void wait_5_ms (void);
void wait_20_ms (void);
void wait_200_ms (void);
void wait_500_ms (void);
void wait_1_s (void);
//========================================================================

//========================================================================
#define SENS_PWR_PIN   PIND
#define SENS_PWR       2

#define NO_SAVE_EEPROM_PARAMETERS   0
#define SAVE_EEPROM_PARAMETERS      1

//#define chk_sens_pwr_on (!(SENS_PWR_PIN&(1<<SENS_PWR)))
#define chk_sens_pwr_on (SENS_PWR_PIN&(1<<SENS_PWR))
//#define chk_sens_pwr_off (SENS_PWR_PIN&(1<<SENS_PWR))
#define chk_sens_pwr_off (!(SENS_PWR_PIN&(1<<SENS_PWR)))

void proc_sens_pwr (u08 a);
//========================================================================

//========================================================================
#define END_TABLE 0xFF
//========================================================================

//========================================================================
extern void sram_copy (u08 *s_1, u08 *s_2, u08 n);
//========================================================================

//========================================================================
typedef struct tab_state_func
{
   u08 state;
   void (*ptr_func) (void);
} tab_state_func;
//------------------------------------------------------------------------
void proc_fsm_1 (u08 *ptr_state, void __flash *ptr_tab_fsm);
//------------------------------------------------------------------------
#define proc_fsm(a, b ) proc_fsm_1(&a, b)
//========================================================================

//========================================================================
typedef struct tab_key_cod
{
   u08 key; // Какая кнопка нажата.
   u08 key_cod; // Код кнопки.
} tab_key_cod;
//------------------------------------------------------------------------
bool define_key_cod_1 (u08 *ptr_key_curr, u08 *ptr_key_buf, void __flash *ptr_tab_key_cod);
//------------------------------------------------------------------------
#define define_key_cod(a, b, c) define_key_cod_1(&a, &b, c)
//========================================================================

//========================================================================
typedef struct tab_key_curr_next_func
{
   u08 key_cod;
   u08 curr_state;
   u08 next_state;
   void (*ptr_func) (void);
} tab_key_curr_next_func;
//------------------------------------------------------------------------
void check_keys_buf_1 (u08 *ptr_keys_buf, u08 *state, void __flash *ptr_key_func);
//------------------------------------------------------------------------
#define check_keys_buf(a, b, c) check_keys_buf_1(&a, &b, c)
//========================================================================

//========================================================================
typedef struct key_cod_func
{
   u08 key_cod;
   void (*ptr_func) (void);
} key_cod_func;
//========================================================================

//========================================================================
#define ST_PROC_LOGO ST_KBD_1

enum
{
   PROC_LOGO_1 = 0,
   PROC_LOGO_2,
   PROC_LOGO_3,
   PROC_LOGO_4,
};

void logo (void);
//========================================================================

#endif