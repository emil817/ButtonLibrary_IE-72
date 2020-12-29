#pragma once
#include <Arduino.h>

#define PULLUP 0
#define PULLDOWN 1
#define PULLUP_INTERNAL 2

class Button {
  public:
    Button(byte pinInc, uint8_t modeInc);
    uint8_t getState();

    void setDebounceTime(byte InTime);
    void setHoldTime(int InTime);
    void setHoldRepeatTime(int byte InTime);
    void setReturnPressBeforeHold(bool In);
    void setReturnReleaseAfterPress(bool In);
    
    bool isPressNow();
    bool isHoldNow();

  private:
    uint8_t pin;
    uint8_t isPULLUP;

    uint8_t debounceTimeValue = 50;
    uint16_t holdTimeValue = 500;
    uint16_t holdRepeatTimeValue = 500;
    bool ReturnPressBeforeHold = false;
    bool ReturnReleaseAfterPressV = false;

    uint32_t debounceTime = 0;

    bool holding = 0;
    bool startHold = 0;
    uint32_t startHoldTime = 0;
    bool holdRepeat = 0;
    uint32_t startHoldRepeatTime = 0;

    bool lastButtonState = false;

};
