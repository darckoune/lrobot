#include "bluetooth.h"

Bluetooth bluetooth;

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
}

void loop() {
  if (bluetooth.recievedData()){
    bluetooth.sendData("You said : " + bluetooth.getData());
  }
}
