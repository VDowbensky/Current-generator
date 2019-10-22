#ifndef MACROS_H
#define MACROS_H

#define set_bit(reg, bit)  reg |= (1<<(bit))    // ��������� ����.
#define clr_bit(reg, bit)	reg &= (~(1<<(bit))) // ����� ����.
#define switch_bit(reg, bit)  reg ^= (1<<(bit)) // ������������ ����.

#endif