#include <ButtonLibraryIE-72.h>

IE_72_Button Button(38,PULLDOWN);

void setup() {
  Serial.begin(11520);
}

void loop() {
  static uint16_t buttonCount = 0;
  switch (Button.getState())
  {
    case 0: break;
    case 1: Serial.println("Button pressed " + String(++buttonCount) + " times."); break;
    case 2: Serial.println("Button holded."); break;
    case 3: Serial.println("Hold repeated."); break;
    case 4: Serial.println("Button released."); break;
  }

}
