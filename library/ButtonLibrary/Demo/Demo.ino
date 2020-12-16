#include <ButtonLibrary.h>

Button Button1(10,PULLUP);

void setup() {
  Button1.setReturnPressBeforeHold(false);
  Button1.setDebounceTime(50);
  Button1.setHoldTime(1000);
  Button1.setHoldRepeatTime(500);
  
  Serial.begin(115200);
  Serial.println("Start");
}

void loop() {
  static uint16_t buttonCount = 0;


  switch (Button1.getState())
  {
    case 0: break;
    case 1: Serial.println("Button pressed " + String(++buttonCount) + " times."); break;
    case 2: Serial.println("Button holded."); break;
    case 3: Serial.println("Hold repeated."); break;
    case 4: Serial.println("Button released."); break;
  }
  /*
   * .isPressNow();
   * .isHoldNow();
   * 
   
   */

}
