#ifndef MACROS_H
#define MACROS_H

#define set_bit(reg, bit)  reg |= (1<<(bit))    // Установка бита.
#define clr_bit(reg, bit)	reg &= (~(1<<(bit))) // Сброс бита.
#define switch_bit(reg, bit)  reg ^= (1<<(bit)) // Переключение бита.

#endif