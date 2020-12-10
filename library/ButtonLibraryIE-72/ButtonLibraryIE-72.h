#pragma once
#include <Arduino.h>

#define PULLUP 0
#define PULLDOWN 1
#define PULLUP_INTERNAL 2

class IE-72_Button {
public:
	IE-72_Button(byte pinInc, uint8_t modeInc);
	uint8_t getState();

	void setDebounceTime(byte InTime);
	void setHoldTime(byte InTime);
	void setHoldRepeatTime(byte InTime);
private:
	uint8_t pin;
	uint8_t isPULLUP;

	uint8_t debounceTimeValue = 50;
	uint16_t holdTimeValue = 500;
	uint16_t holdRepeatTimeValue = 500;
	
	uint32_t debounceTime = 0;
  
  	bool Hold = 0;
  	uint32_t startHoldTime = 0;
  	bool holdRepeat = 0;
  	uint32_t startHoldRepeatTime = 0;

  	bool lastButtonState = true;

}


