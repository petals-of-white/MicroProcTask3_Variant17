#pragma once
#include <stdint.h>
#include <stdbool.h>

// Рік народження
extern const uint16_t birthYear;
extern const uint8_t yearLength;

// Номер індикатора
extern uint8_t Ni;
extern uint8_t ticks;
extern int8_t IND[4];

extern uint8_t offset;

extern bool readyForNextDigits;

// something
extern char *currentPairOfDigits;

// Відображає поточний індикатор
void continueNumberAnimation();

// Очевидно
char *GetTwoDigits(int number, uint8_t offset);

// Наступна пара цифр
void setNextDigitPair();

// Відображає поточний індикатор
void showCurrentIndicator();

// Переходить до наступного індикатора
void nextIndicator();

// Посуває цифри вправо
void moveDigits();