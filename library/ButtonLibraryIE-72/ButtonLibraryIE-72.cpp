#include "ButtonLibraryIE-72.h"
#include <Arduino.h>


IE_72_Button::IE_72_Button(byte pinInc, uint8_t modeInc)
{
	pin = pinInc;
  	pinMode(pin, modeInc == PULLUP_INTERNAL ? INPUT_PULLUP : INPUT);
  	isPULLUP = (modeInc == PULLDOWN ? false : true);
}

uint8_t IE_72_Button::getState()
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

void IE_72_Button::setDebounceTime(byte InTime)
{
  debounceTimeValue = InTime;
}
void IE_72_Button::setHoldTime(byte InTime)
{
  holdTimeValue = InTime;
}
void IE_72_Button::setHoldRepeatTime(byte InTime)
{
  holdRepeatTimeValue = InTime;
}

bool IE_72_Button::isPress()
{
	if(IE_72_Button::getState() == 1)
	{
	return  true;
	}
	else
	{
	return false;
	}
}

bool IE_72_Button::isHold()
{
	if(IE_72_Button::getState() == 2)
	{
	return  true;
	}
	else
	{
	return false;
	}
}

bool IE_72_Button::isRelease()
{
	if(IE_72_Button::getState() == 4)
	{
	return  true;
	}
	else
	{
	return false;
	}
}