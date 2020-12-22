#include <ButtonLibrary.h>

// Setup buttons
Button incrementButton(8, PULLUP_INTERNAL);
Button decrementButton(9, PULLUP_INTERNAL);
Button randomButton(10, PULLUP_INTERNAL);
Button zeroButton(11, PULLUP_INTERNAL);

void setup()
{
  incrementButton.setHoldTime(500);
  incrementButton.setHoldRepeatTime(50);
  decrementButton.setHoldTime(500);
  decrementButton.setHoldRepeatTime(50);
  // Port D (pins 0-7) set as output
  DDRD = B11111111;
  // Turn Off all LEDs
  PORTD = B00000000;
}

void loop()
{
  static byte value = 0;

  if (zeroButton.getState() == 1) PORTD = 0;
  if (randomButton.getState() == 1) PORTD = random(0, 255);

  switch (incrementButton.getState())
  {
    case 1: PORTD++; break;
    case 2: PORTD++; break;
    case 3: PORTD++; break;
  }

  switch (decrementButton.getState())
  {
    case 1: PORTD--; break;
    case 2: PORTD--; break;
    case 3: PORTD--; break;
  }
}
