typedef enum menu_states
{
#define MENU(name, parent, child, next, prev, plus_func, minus_func, enter_func, num_func, menu_func) name,
#include "_menu.h"
#undef MENU

MENU_STATES

} menu_states;
//========================================================================

//========================================================================
struct menu_item __flash table_menu [MENU_STATES] =
{
#define MENU(name, parent, child, next, prev, plus_func, minus_func, enter_func, num_func, menu_func) \
parent, child, next, prev, plus_func, minus_func, enter_func, num_func, menu_func,
#include "_menu.h"
#undef MENU
};
//========================================================================


//========================================================================
/*
set_menu:
_menu = x
ptr_func = menu_func
*/
//------------------------------------------------------------------------
void set_menu (u08 x)
{
   if (x) _menu = x;

   go_menu_func (x);
}
//------------------------------------------------------------------------
void set_parent (void)
{
   if (table_menu [_menu].Parent) set_menu (table_menu [_menu].Parent);
}
//------------------------------------------------------------------------
void  set_child (void)
{
   if (table_menu [_menu].Child) set_menu (table_menu [_menu].Child);
}
//------------------------------------------------------------------------
void set_next (void)
{
   if (table_menu [_menu].Next) set_menu (table_menu [_menu].Next);
}
//------------------------------------------------------------------------
void set_prev (void)
{
   if (table_menu [_menu].Prev) set_menu (table_menu [_menu].Prev);
}

void go_plus_func (void)
{
   void (*ptr_func) (void);

   ptr_func = EMPTY_FUNC;

   ptr_func = table_menu [_menu].plus_func;

   if ((ptr_func)) (*ptr_func) ();
}

void go_minus_func (void)
{
   void (*ptr_func) (void);

   ptr_func = EMPTY_FUNC;

   ptr_func = table_menu [_menu].minus_func;

   if ((ptr_func)) (*ptr_func) ();
}
//------------------------------------------------------------------------
void go_enter_func (void)
{
   if (table_menu [_menu].enter_func)
   {
      void (*ptr_func) (void);

      ptr_func = EMPTY_FUNC;

      ptr_func = table_menu [_menu].enter_func;

      if ((ptr_func)) (*ptr_func) ();

      return;
   }

   set_child ();
}

void go_num_func (void)
{
   void (*ptr_func) (void);

   ptr_func = EMPTY_FUNC;

   ptr_func = table_menu [_menu].num_func;

   if ((ptr_func)) (*ptr_func) ();
}
//------------------------------------------------------------------------
void go_menu_func (u08 x)
{
   void (*ptr_func) (void);

   ptr_func = EMPTY_FUNC;

   ptr_func = table_menu [x].menu_func;

   if ((ptr_func)) (*ptr_func) ();
}
//========================================================================

//========================================================================
bool proc_menu_keys (void)
{
   bool a = false;
   u08 key;

   if (Get_Event (EV_ID_KEY_PRESSED))
   {
      key = GetKeyCode ();

      switch (key)
      {
         case KEY_ESC_COD:
            set_parent ();
            a = true;
            break;

         case KEY_ENTER_COD:
            go_enter_func ();
            a = true;
            break;

         case KEY_NEXT_COD:
            set_next ();
            a = true;
            break;

         case KEY_PREV_COD:
            set_prev ();
            a = true;
            break;

         case KEY_PLUS_COD:
            go_plus_func ();
            a = true;
            break;

         case KEY_MINUS_COD:
            go_minus_func ();
            a = true;
            break;

         default:
            break;
      }

      if (key < 10)
      {
         go_num_func (); // Ввод числовых параметров.
         a = true;
      }
   }

   if (a) return true;

   else return false;
}
//========================================================================


//========================================================================
#define NULL_ENTRY Null_Menu
#define NULL_FUNC  (void*)0
#define NULL_TEXT  0x00

#define MAKE_MENU(Name, Next, Child, Select, Enter, Text) \
   extern const menuItem   Next;               \
   extern const menuItem   Child;               \
   const menuItem         Name = {(void*)&Next,    \
      (void*)            &Child,             \
      (FuncPtr)         Select,             \
      (FuncPtr)         Enter,                \
      { Text }}

#define NEXT       ((menuItem*)(selectedMenuItem->Next))
#define CHILD      ((menuItem*)(selectedMenuItem->Child))
#define SELECTFUNC   ((FuncPtr)(selectedMenuItem->SelectFunc))
#define ENTERFUNC   ((FuncPtr)(selectedMenuItem->EnterFunc))
   
// Typedefs:
typedef void (*FuncPtr)(void);
   
typedef struct
{
   void      *Next;
   void      *Child;
   FuncPtr     SelectFunc;   // i?ia?aiia aey ioia?a?aiey a naiii iai?
   FuncPtr     EnterFunc;   // i?ia?aiia ?aaiou, aucuaaaiay i?e ia?aoee Enter a iai?
   const char  Text[20];
} menuItem;

extern const menuItem m_s1i1;

void MenuChange (const menuItem *);
//========================================================================


// объявления локальных программ
void menu (void);
void viev_volt (void);
void display_result (void);
void change_acc (void);
void capacity_add (void);
void capacity_sub (void);
void view_capacity (void);
void acc_measure (void);

void view_acc (void);



extern menuItem* selectedMenuItem; // текущий пункт меню

// для начала — пустой элемент. Который NULL на рисунке
menuItem   Null_Menu = {(void*)0, (void*)0, NULL_FUNC, NULL_FUNC, {NULL_TEXT}};

/* Программа find_less_by_sample
Что делает: ищет индекс ближайшего меньшего значения в массиве по образцу
Входные данные: uint16_t sample - образец
REFERENCE *ref - указатель на структуру
Возвращаемое значение: индекс элемента в структуре или 0xFF, если не нашёл
*/

/*
uint8_t find_less_by_sample(uint16_t sample, const REFERENCE *ref)
{
    uint8_t i;
   
    if (ref->size > 0)
    {
        if ((sample <= ref->refstr[0].volt) && (sample >= ref->refstr[ref->size - 1].volt))
        {
         for (i = 0; i < ref->size; i++)
         {
            if (ref->refstr[i].volt <= sample)
               break;
         }
         return i;   
        }
    }
    return (0xFF);
}
*/

void MenuChange (const menuItem *NewMenu)
{
   if ((void*)NewMenu != (void*)&Null_Menu)
   {
// запись нового пункта в переменную состояния
      selectedMenuItem = (menuItem *)NewMenu;   // изменять меню по отпусканию кнопки
// вывод информации на дисплей   
//      L = (char *)NewMenu->Text;
//      LCD_Gatekeeper (L);
   }
}

// программа для отображения напряжения для калибровки
void viev_volt (void)
{
//...
}

// программа отображения результата предыдущего измерения
void display_result (void)
{
//...
}

// программа изменения типа аккумулятора (выбор референсной таблицы)
void change_acc (void)
{
//...
}

// добавить единицу к паспортной ёмкости аккумулятора
void capacity_add (void)
{
//...
}

// уменьшить на единицу паспортную ёмкость аккумулятора
void capacity_sub (void)
{
//...
}

// вывести на экран паспортную ёмкость аккумулятора
void view_capacity (void)
{
//...
}

// показать тип аккумулятора
void view_acc (void)
{
//...
}

// программа измерения ёмкости аккумулятора
void acc_measure (void)
{
//...
}

//                     NEXT,   CHILD,   SelectFunc,   EnterFunc
// меню измерение
MAKE_MENU (m_s1i1,         m_s1i2,   m_s2i1,   NULL_FUNC,   NULL_FUNC,   "\fMeasure");
   // подменю Измерение
   MAKE_MENU (m_s2i1,      m_s2i2,   m_s1i1,   NULL_FUNC,   acc_measure,   "Measure Start ");
   MAKE_MENU (m_s2i2,      m_s2i1,   m_s1i1,   display_result,   NULL_FUNC,   "Measure Result");
// меню установки
MAKE_MENU (m_s1i2,         m_s1i3,   m_s3i2,   NULL_FUNC,   NULL_FUNC,   "\fSetup");
   // подменю Настройка
   MAKE_MENU (m_s3i1,      m_s3i2,   m_s4i1,   NULL_FUNC,   NULL_FUNC,   "\fSetup Capacity  ");
      // подменю Ёмкость
      MAKE_MENU (m_s4i1,   m_s4i2,   m_s1i2,   view_capacity,   capacity_add,   "Setup Capacity +");
      MAKE_MENU (m_s4i2,   m_s4i1,   m_s1i2,   view_capacity,   capacity_sub,   "Setup Capacity -");
   // подменю тип АСС
   MAKE_MENU (m_s3i2,      m_s3i1,   m_s1i2,   view_acc,   change_acc,   "\fSetup Model     ");
// меню калибровки
MAKE_MENU (m_s1i3,         m_s1i4,   m_s6i1,   NULL_FUNC,   NULL_FUNC,   "\fCalibrate");
   // подменю Калибровка
   MAKE_MENU (m_s6i1,      m_s6i2,   m_s1i3,   viev_volt,   NULL_FUNC,   "\fCalibrate Volts");
   MAKE_MENU (m_s6i2,      m_s6i1,   m_s7i1,   view_current,   NULL_FUNC,   "\fCalibrate Ampers");
      // подменю Ток
      MAKE_MENU (m_s7i1,   m_s7i2,   m_s1i3,   view_current,   add_current,"Calibr. Ampers +");
      MAKE_MENU (m_s7i2,   m_s7i1,   m_s1i3,   view_current,   sub_current,"Calibr. Ampers -");
// меню контрольного разряда аккумулятора
MAKE_MENU (m_s1i4,         m_s1i1,   m_s8i1,   NULL_FUNC,   NULL_FUNC,   "\fDischarging    ");
   // подменю Начало разрядки аккумулятора
   MAKE_MENU (m_s8i1,      m_s8i2,   m_s1i4,   NULL_FUNC,   acc_discharging,   "Discharge Start ");
   MAKE_MENU (m_s8i2,      m_s8i1,   m_s1i4,   disch_result,   NULL_FUNC,      "Discharge Result");






/*


//========================================================================
typedef struct Menu_Item
{
	void     *Parent;
   void     *Child;
	void     *Next;
   void     *Previous;
	FuncPtr  plus_func;
	FuncPtr  minus_func;
	FuncPtr  num_func;
	FuncPtr  enter_func;
	FuncPtr  menu_func;
   char Text[];
} Menu_Item;
//========================================================================

//========================================================================
#define MAKE_MENU(Name, Parent, Child, Next, Previous, plus_func, minus_func, num_func, enter_func, menu_func, Text) \
   Menu_Item Parent;   \
	Menu_Item Child;    \
	Menu_Item Next;     \
	Menu_Item Previous; \
   plus_func; \
   minus_func; \
   num_func;\
   enter_func;\
   menu_func;\
   Text;\
	Menu_Item Name = {(void*)&Parent, (void*)&Child, (void*)&Next, (void*)&Previous, (FuncPtr)plus_func, (FuncPtr)minus_func, (FuncPtr)num_func, (FuncPtr)enter_func, (FuncPtr)menu_func, {Text}}
//========================================================================

//========================================================================
// Externs:
extern WriteFuncPtr*    WriteFunc;
extern Menu_Item        Null_Menu;
extern Menu_Item*       CurrMenuItem;

// Defines and Macros:
#define NULL_ENTRY Null_Menu
#define NULL_FUNC  (void*)0
#define NULL_TEXT  0x00
//------------------------------------------------------------------------
#define PARENT     *((Menu_Item*)(&CurrMenuItem->Parent))
#define CHILD      *((Menu_Item*)(&CurrMenuItem->Child))
#define NEXT       *((Menu_Item*)(&CurrMenuItem->Next))
#define PREVIOUS   *((Menu_Item*)(&CurrMenuItem->Previous))

#define PLUS_FUNC  *((FuncPtr*)(&CurrMenuItem->plus_func))
#define MINUS_FUNC *((FuncPtr*)(&CurrMenuItem->minus_func))
#define NUM_FUNC   *((FuncPtr*)(&CurrMenuItem->num_func))
#define ENTER_FUNC *((FuncPtr*)(&CurrMenuItem->enter_func))
#define MENU_FUNC  *((FuncPtr*)(&CurrMenuItem->menu_func))
//========================================================================
*/






//   strcpy_P (Menu_Str_Buf, CurrMenuItem->Text);