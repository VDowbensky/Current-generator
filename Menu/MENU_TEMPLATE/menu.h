//========================================================================
#ifndef MENU_H

#define MENU_H

#include "menu.h"
//========================================================================

//========================================================================
#include <pgmspace.h>
#include <stdbool.h>

#include "avrlibtypes.h"
#include "kbd_drv.h"
//========================================================================

//========================================================================
// Typedefs:
typedef void (*FuncPtr)(void);
//========================================================================

//========================================================================
typedef struct menu_item
{
   void         *Parent;
   void         *Child;
   void         *Next;
   void         *Prev;
   FuncPtr       NumFunc;
   FuncPtr       EnterFunc;
   FuncPtr       MenuFunc;
   char __flash *Text;
} menu_item;
//========================================================================

// Externs:
//========================================================================
extern menu_item __flash *CurrMenuItem; // Текущий пункт меню.
extern menu_item __flash *BeginCurrMenuLevel; // Начало массива текущего уровня меню.

extern __flash menu_item Null_Menu;

extern char Menu_Str_Buf []; // Буфер для вывода текста.

extern void (*MenuFuncPtr)(void);
//========================================================================

// Defines and Macros:
//========================================================================
#define NULL_ENTRY Null_Menu
#define NULL_FUNC  (void*)0
#define NULL_TEXT  0x00
#define PAGE_MENU  3
//========================================================================

//========================================================================
#define MAKE_MENU(Name, Parent, Child, Next, Prev, NumFunc, EnterFunc, MenuFunc, Text) \
extern menu_item __flash Parent;                                                       \
extern menu_item __flash Child;                                                        \
extern menu_item __flash Next;                                                         \
extern menu_item __flash Prev;                                                         \
       menu_item __flash Name =                                                        \
{                                                                                      \
      (menu_item*)      &Parent,                                                       \
      (menu_item*)      &Child,                                                        \
      (menu_item*)      &Next,                                                         \
      (menu_item*)      &Prev,                                                         \
                         NumFunc,                                                      \
                         EnterFunc,                                                    \
                         MenuFunc,                                                     \
                        {Text}                                                         \
}
//========================================================================

//========================================================================
#define PARENT     *((menu_item __flash*) (CurrMenuItem->Parent))
#define CHILD      *((menu_item __flash*) (CurrMenuItem->Child))
#define NEXT       *((menu_item __flash*) (CurrMenuItem->Next))
#define PREV       *((menu_item __flash*) (CurrMenuItem->Prev))
#define NUM_FUNC   *((FuncPtr)   (CurrMenuItem->NumFunc))
#define ENTER_FUNC *((FuncPtr)   (CurrMenuItem->EnterFunc))
#define MENU_FUNC  *((FuncPtr)   (CurrMenuItem->MenuFunc))
//========================================================================

//========================================================================
#define SET_MENU_LEVEL(x) \
   Set_Menu_Level(&x)

#define SET_MENU_ITEM(x) \
   Set_Menu_Item(&x)
	
#define GO_MENU_FUNC(x)  \
	MenuFunc((FuncPtr*)&x)
	
#define EXTERN_MENU(Name) \
    extern menu_item __flash Name;
//========================================================================

//========================================================================
enum
{
   SET_LEVEL = 0,
   SET_NEXT,
   SET_PREV,
};
//========================================================================

// Prototypes:
//========================================================================
void Set_Menu_Level (menu_item __flash *NewMenu);
void Set_Menu_Item (menu_item __flash *NewMenu);
void MenuFunc(FuncPtr* Function);
//========================================================================

//========================================================================
EXTERN_MENU (L_OUT_MODE);
//========================================================================

//========================================================================
void Out_Menu_Items_Init (void);
void Out_Menu_Items (void);
//========================================================================

//========================================================================
bool proc_menu_keys (void);
//========================================================================

//========================================================================
void out_name_level (void);
u08 count_chars (char __flash *data);
void make_page_menu (void);
void inc_pos_y_curs (void);
void dec_pos_y_curs (void);
void set_pos_curs (void);
//========================================================================

#endif