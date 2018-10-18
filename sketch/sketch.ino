#include "bluetooth.h"

Bluetooth b;

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
}

void loop() {
  if (b.recievedData()){
    Serial3.println("You said : " + b.getData());
  }
}
