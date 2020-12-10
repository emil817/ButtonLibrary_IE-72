#include "ButtonLibraryIE-72.h"
#include <Arduino.h>


IE-72_Button::IE-72_Button(byte pinInc, uint8_t modeInc)
{
	pin = pinInc;
  	pinMode(pin, modeInc == PULLUP_INTERNAL ? INPUT_PULLUP : INPUT);
  	isPULLUP = (modeInc == PULLDOWN ? false : true);
}

IE-72_Button::uint8_t getState()
{

  uint8_t stateToReturn = 0;

  bool buttonState = digitalRead(pin);

  if (lastButtonState != buttonState)
  {
    if (millis() - debounceTime > debounceTimeValue)
    {
      lastButtonState = buttonState;
      if (buttonState == isPULLUP)
      {
        stateToReturn = 1;
        Hold = 1;
        startHoldTime = millis();
      }
      else
      {
        stateToReturn = 4;
        Hold = 0;
        holdRepeat = 0;
      }
    }
    debounceTime = millis();
  }
  if (buttonState == isPULLUP)
  {
    if (millis() - startHoldTime >= holdTimeValue && Hold == 1)
    {
      Hold = 0;
      stateToReturn = 2;
      startHoldRepeatTime = millis();
      holdRepeat = 1;
    }
    if (millis() - startHoldRepeatTime >= holdRepeatTimeValue && holdRepeat == 1)
    {
      startHoldRepeatTime = millis();
      stateToReturn = 3;
    }
  }
  return stateToReturn;
}

IE-72_Button::void setDebounceTime(byte InTime)
{
  debounceTimeValue = InTime;
}
IE-72_Button::void setHoldTime(byte InTime)
{
  holdTimeValue = InTime;
}
IE-72_Button::void setHoldRepeatTime(byte InTime)
{
  holdRepeatTimeValue = InTime;
}

