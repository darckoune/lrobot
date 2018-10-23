#include "MeMegaPi.h"

MeRGBLed myled(PORT_5);

void setup() {
  Serial.begin(9600);
}

void loop() {
  uint8_t red = 255;
  uint8_t green = 0;
  uint8_t blue = 255;
  myled.setColor(red, green, blue);
  myled.show();

}
