#define PULLUP 0
#define PULLDOWN 1
#define PULLUP_INTERNAL 2

void setup()
{
  Serial.begin(115200);
  begin(8, PULLUP);
}

uint8_t pin;
uint8_t isPULLUP;

uint8_t debounceTimeValue = 50;
uint16_t holdTimevalue = 500;
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
  static uint32_t startHoldTime = 0;
  bool Hold = 0;
  bool buttonState = digitalRead(8);
  static bool lastButtonState = true;
  if (lastButtonState != buttonState)
  {
    if (millis() - debounceTime > debounceTimeValue)
    {
      lastButtonState = buttonState;
      if (buttonState == true)
      {
        stateToReturn = 1;
        if (Hold == 0) {
          startHoldTime = millis();
          Hold = 1;
        }
        else
        {
          if (millis() - startHoldTime >= holdTimevalue)
          {
            Hold = 0;
            stateToReturn = 2;
          }
        }
      }
      else
      {
        stateToReturn = 4;
        Hold = 0;
      }
    }
    debounceTime = millis();
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
