#include "bluetooth.h"
#include <string.h>

Bluetooth bluetooth;
String data;

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
}

void loop() {
  if (bluetooth.recievedData()){
    data = bluetooth.getData();
    bluetooth.sendData("You said : " + data);
    Serial.println("Bluetooth said : " + data);
  }
}
