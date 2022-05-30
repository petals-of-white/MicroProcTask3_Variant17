/*
    Лабораторна робота № 3
    Черкасова Марія
    534 група

    Варіянт 17:
    Виводити на індикатори свій рік народження.
    Час між змінами цифр на індикаторах – 1 сек. Для гасіння індикатору вивести байт 0F.
*/

#include <avr/io.h>
#include "operations.h"

void main()
{
    DDRD = 0x7F;
    setNextDigitPair();

    while (1)
    {
        continueNumberAnimation();
    }
}
