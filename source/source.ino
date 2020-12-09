#define PULLUP 0
#define PULLDOWN 1
#define PULLUP_INTERNAL 2

void setup()
{
  Serial.begin(115200);
  begin(38, PULLDOWN);
}

uint8_t pin;
uint8_t isPULLUP;

uint8_t debounceTimeValue = 50;
uint16_t holdTimeValue = 500;
uint16_t holdRepeatTimeValue = 500;

void begin(uint8_t pinInc, uint8_t modeInc)
{
  pin = pinInc;
  pinMode(pin, modeInc == PULLUP_INTERNAL ? INPUT_PULLUP : INPUT);
  isPULLUP = (modeInc == PULLDOWN ? false : true);
}

void loop()
{
  static uint16_t buttonCount = 0;
  switch (getState())
  {
    case 0: break;
    case 1: Serial.println("Button pressed " + String(++buttonCount) + " times."); break;
    case 2: Serial.println("Button holded."); break;
    case 3: Serial.println("Hold repeated."); break;
    case 4: Serial.println("Button released."); break;
  }
}

uint8_t getState()
{
  uint8_t stateToReturn = 0;
  static uint32_t debounceTime = 0;
  
  static bool Hold = 0;
  static uint32_t startHoldTime = 0;
  static bool holdRepeat = 0;
  static uint32_t startHoldRepeatTime = 0;

  static bool lastButtonState = true;

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

void setDebounceTime(byte InTime)
{
  debounceTimeValue = InTime;
}
void setHoldTime(byte InTime)
{
  holdTimeValue = InTime;
}
void setHoldRepeatTime(byte InTime)
{
  holdRepeatTimeValue = InTime;
}
