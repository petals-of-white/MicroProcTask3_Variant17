#include <avr/io.h>
#include <avr/delay.h>
#include <stdlib.h>
#include "operations.h"
const uint16_t birthYear = 2002;
const uint8_t yearLength = 4;

uint8_t Ni = 0;
uint8_t ticks = 0;
int8_t IND[4] = {-1, -1, -1, -1};

uint8_t offset = 0;

bool readyForNextDigits = false;

char *currentPairOfDigits;

char *GetTwoDigits(int number, uint8_t offset)
{
    char *result = (char *)malloc(3);
    result[0] = '\0';

    if (offset > 0)
        number = number / (pow(10, offset));

    uint8_t reshta = number % 100;

    if (reshta > 9)
        sprintf(result, "%d", reshta);

    else
    {
        strcat(result, "0");

        char buffer[2];

        sprintf(buffer, "%d", reshta);

        strcat(result, buffer);
    }

    return result;
}

void showCurrentIndicator()
{
    if (IND[Ni] == -1)
        PORTD = 0x0F; // Вимкнено
    else
        PORTD = IND[Ni] | (Ni << 4);

    _delay_ms(5);
}

void moveDigits()
{
    static int position = -2;

    switch (position)
    {
    case -2:
        for (int i = 0; i < (yearLength - offset); i++)
        {
            IND[i] = -1; // вимикаємо індикатор
        }

        break;

    case -1:

        IND[0] = currentPairOfDigits[1];

        for (int i = 1; i < (yearLength - offset); i++)
            IND[i] = -1; // вимикаємо індикатор

    case 0:
        IND[0] = currentPairOfDigits[0];
        IND[1] = currentPairOfDigits[1];

        for (int i = 2; i < (yearLength - offset); i++)
            IND[i] = -1; // вимикаємо індикатор
    }

    position++;

    if ((position) == (yearLength - offset - 1))
    {
        readyForNextDigits = true;
        position = -2;
    }
}

void nextIndicator()
{
    Ni = (Ni + 1) & 3;
    ticks++;
}

// Задає бере наступні дві цифри (справа наліво) з числа-року
void setNextDigitPair()
{
    offset++;

    if (currentPairOfDigits != NULL)
    {
        free(currentPairOfDigits);
        currentPairOfDigits = NULL;
    }

    currentPairOfDigits = GetTwoDigits(birthYear, offset);
}

void continueNumberAnimation()
{

    showCurrentIndicator();
    nextIndicator();

    if (offset < 4)
    {
        if (readyForNextDigits)
        {
            setNextDigitPair();
            offset++;
        }

        bool timeToMove = ticks > 200; // one second has passed

        if (timeToMove)
        {
            ticks = 0;
            moveDigits();
        }
    }
}