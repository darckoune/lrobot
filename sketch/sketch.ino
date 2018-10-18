#include "bluetooth.h"

Bluetooth b;

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
}

void loop() {
  if (b.recievedData()){
    b.sendData("You said : " + b.getData());
  }
}
