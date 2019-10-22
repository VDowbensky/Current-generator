//========================================================================
#include "menu.h"
//========================================================================

//========================================================================
static u08 quant_items;
static u08 pos_y_curs;
//========================================================================

//==============================================================================================================================================
menu_item __flash *CurrMenuItem; // ������� ����� ����.

menu_item __flash *BeginCurrMenuLevel; // ������ ������� �������� ������ ����.

menu_item __flash *temp_menu;

menu_item __flash  Null_Menu = {(void*)0, (void*)0, (void*)0, (void*)0, NULL_FUNC, NULL_FUNC, NULL_FUNC, {NULL_TEXT}};

void (*MenuFuncPtr)(void);
//==============================================================================================================================================

//========================================================================
void Set_Menu_Level (menu_item __flash *NewMenu)
{
   if ((void*)NewMenu == (void*)&NULL_ENTRY)
      return;

   CurrMenuItem = NewMenu;

   Out_Menu_Items_Init (); // ��� ��� ����� �������, ������������� ����������.
   Out_Menu_Items (); // ����� �������� ������ ���� � ������� ����, �������.

   GO_MENU_FUNC (ENTER_FUNC);
}
//========================================================================

//========================================================================
void Set_Menu_Item (menu_item __flash *NewMenu)
{
   if ((void*)NewMenu == (void*)&NULL_ENTRY)
      return;

   CurrMenuItem = NewMenu;

   Out_Menu_Items (); // ����� �������� ������ ���� � ������� ����, �������.

   GO_MENU_FUNC (ENTER_FUNC);
}
//========================================================================

//========================================================================
void MenuFunc (FuncPtr* Function)
{
   if ((void*) Function == (void*) NULL_FUNC)
      return;

   ((FuncPtr) Function)();
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
            SET_MENU_LEVEL (PARENT);
            a = true;
            break;

         case KEY_ENTER_COD:
            SET_MENU_LEVEL (CHILD);
            a = true;
            break;

         case KEY_NEXT_COD:
            inc_pos_y_curs ();
            SET_MENU_ITEM (NEXT);
            a = true;
            break;

         case KEY_PREV_COD:
            dec_pos_y_curs ();
            SET_MENU_ITEM (PREV);
            a = true;
            break;

         default:
            break;
      }

      if (key < 10)
      {
         GO_MENU_FUNC (NUM_FUNC); // ��������� ����. ���� �������� ����������.
         a = true;
      }
   }

   if (a) return true;
   else   return false;
}
//========================================================================

/*
������, ������, ����� - ��� ��������� ���������.
��� ��� ��� �������� �� ���� ��������� � ���������, �� �������� ���������� � ����������� ����������� �� ����.
*/

//========================================================================
void Out_Menu_Items_Init (void)
{
   quant_items = 1;
   pos_y_curs = 1;

// ��������� ������ ������ ������� ������ ����.
   BeginCurrMenuLevel = CurrMenuItem;
   temp_menu = (menu_item __flash *)(CurrMenuItem->Prev);

   while (1)
   {
      if ((void*)temp_menu == (void*)&NULL_ENTRY)
      {
         break;
      }
      else
      {
         BeginCurrMenuLevel = temp_menu;
         temp_menu = (menu_item __flash *)(temp_menu->Prev);
      }
   }

// ��������� ���������� ������� ����.
   temp_menu = (menu_item __flash *)(BeginCurrMenuLevel->Next);

   while (1)
   {
      if ((void*)temp_menu == (void*)&NULL_ENTRY)
      {
         break;
      }

      temp_menu = (menu_item __flash *)(temp_menu->Next);
      quant_items++;
   }

// ������� �������.
   if (quant_items > 1)
   {
      temp_menu = BeginCurrMenuLevel;

      while (1)
      {
         if ((void*)temp_menu == (void*)&NULL_ENTRY)
            return;

         if (temp_menu == CurrMenuItem)
            return;
         else
            pos_y_curs++;

         temp_menu = (menu_item __flash *)(temp_menu->Next);
      }
   }
}

void Out_Menu_Items (void)
{
   clr_dsp_buf ();

   out_name_level (); // ����� �������� ������ ����.

   make_page_menu (); // ����� ������� ����.

   set_pos_curs ();   // ��������� ������� � ����� �������.
}
//========================================================================

//========================================================================
// ����� �������� ������ ����.
void out_name_level (void)
{
   temp_menu = (menu_item __flash *)(CurrMenuItem->Parent); // ���������� �������� ������ ���� �� ������ ���� � ������� ������.

   if ((void*)temp_menu != (void*)&NULL_ENTRY)
   {
      char __flash *data = temp_menu->Text;

      u08 i = count_chars (data); // ������� ���-�� �������� � ������.

// ������������ ������ ���������� ������ �������.

      u08 a = i;

      i = (20 - i); // ������� 20x4. �������� �� 20 ����� ��������.

      i >>= 1; // ����� ������� �� 2.

      if (a & (1<<0))
         i += 2; // ���� ����� ��������.
      else
         i++; // ���� ����� ������.

      Print_Buf (1, i, temp_menu->Text);
   }
}
//========================================================================

//========================================================================
// ������� ���-�� �������� � ������.
u08 count_chars (char __flash *data)
{
   u08 i = 0;

   while (data [i])
   {
      i++;
   }
   return i;
}
//========================================================================

//========================================================================
void make_page_menu (void)
{
   signed char tmp_pos_y_curs;
   u08 i; // ������� �������.
   u08 j; // �������� ����.

   if (quant_items > 1) // ���� ������� ���� ������ 1, ������ ���� ��� ��������.
   {
      temp_menu = BeginCurrMenuLevel;

      if (pos_y_curs > PAGE_MENU)
      {
         tmp_pos_y_curs = pos_y_curs;

         i = 0; // ������� �������.

         while (tmp_pos_y_curs > 0)
         {
            tmp_pos_y_curs -= PAGE_MENU;
            i++;
         }
         tmp_pos_y_curs += PAGE_MENU;

         j = PAGE_MENU; // �������� ����.

         while (i-- > 1)
         {
            while (j--)
            {
               temp_menu = (menu_item __flash *)(temp_menu->Next); // ��������� ����� ����.
            }
            j = PAGE_MENU; // �������� ����.
         }
      }

      u08 pos_y_text_item = 2; // 
      j = PAGE_MENU; // �������� ����.

      while (j--)
      {
         Print_Buf (pos_y_text_item, 2, temp_menu->Text); // ����� �������� ������ ����.

         temp_menu = (menu_item __flash *)(temp_menu->Next); // ��������� ����� ����.

         if ((void*)temp_menu == (void*)&NULL_ENTRY) // ���� ������� Next
            return;                                  // ������, �� �����.
         else
            pos_y_text_item++;
      }
   }
}
//========================================================================

//========================================================================
void inc_pos_y_curs (void)
{
   if (quant_items > 1)
   {
      if (pos_y_curs < quant_items) pos_y_curs++;
   }
}

void dec_pos_y_curs (void)
{
   if (quant_items > 1)
   {
      if (pos_y_curs > 1) pos_y_curs--;
   }
}
//========================================================================

//========================================================================
void set_pos_curs (void)
{
   if (quant_items > 1)
   {
      signed char tmp = pos_y_curs;

      while (tmp > 0)
      {
         tmp -= PAGE_MENU;
      }

      if (tmp <= 0) tmp += PAGE_MENU;

      PrintChar (tmp + 1, 1, ARROW_RIGHT);
   }
}
//========================================================================