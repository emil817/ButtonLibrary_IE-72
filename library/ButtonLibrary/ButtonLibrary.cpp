#include "ButtonLibrary.h"
#include <Arduino.h>


Button::Button(byte pinInc, uint8_t modeInc)
{
  pin = pinInc;
  pinMode(pin, modeInc == PULLUP_INTERNAL ? INPUT_PULLUP : INPUT);
  isPULLUP = (modeInc == PULLDOWN ? false : true);
}

uint8_t Button::getState()
{

  uint8_t stateToReturn = 0;
  bool buttonState = isPULLUP ? !digitalRead(pin) : digitalRead(pin);

  if (lastButtonState != buttonState)
  {
    if (millis() - debounceTime > debounceTimeValue)
    {
      lastButtonState = buttonState;
      if (buttonState == true)
      {
        if (ReturnPressBeforeHold)
        {
          stateToReturn = 1;
        }
        startHold = 1;
        startHoldTime = millis();
      }
      else
      {
        if ((holding == 1) || (ReturnReleaseAfterPressV == 1))
        {
          stateToReturn = 4;
        }
        else if (ReturnPressBeforeHold != true)
        {
          stateToReturn = 1;
        }
        startHold = 0;
        holding = 0;
        holdRepeat = 0;
      }
    }
    debounceTime = millis();
  }
  if (buttonState == true)
  {
    if ((millis() - startHoldTime >= holdTimeValue) && startHold == 1)
    {
      startHold = 0;
      holding = 1;
      stateToReturn = 2;
      startHoldRepeatTime = millis();
      holdRepeat = 1;
    }
    if ((millis() - startHoldRepeatTime >= holdRepeatTimeValue) && holdRepeat == 1)
    {
      startHoldRepeatTime = millis();
      stateToReturn = 3;
    }
  }
  return stateToReturn;
}

void Button::setDebounceTime(byte InTime)
{
  debounceTimeValue = InTime;
}
void Button::setHoldTime(int InTime)
{
  holdTimeValue = InTime;
}
void Button::setHoldRepeatTime(int InTime)
{
  holdRepeatTimeValue = InTime;
}

void Button::setReturnPressBeforeHold(bool In)
{
  ReturnPressBeforeHold = In;
}

void Button::setReturnReleaseAfterPress(bool In)
{
  ReturnReleaseAfterPressV = In;
}


bool Button::isPressNow()
{
  if (holding == 1 || startHold == 1)
  {
    return  true;
  }
  else
  {
    return false;
  }
}

bool Button::isHoldNow()
{
  if (holding == 1)
  {
    return  true;
  }
  else
  {
    return false;
  }
}
