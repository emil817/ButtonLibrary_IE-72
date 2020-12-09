#pragma once
#include <Arduino.h>

#define PULLUP 0
#define PULLDOWN 1
#define PULLUP_INTERNAL 2

void begin(uint8_t pinInc, uint8_t modeInc);

uint8_t getState();

void setDebounceTime(byte InTime);
void setHoldTime(byte InTime);
void setHoldRepeatTime(byte InTime);

