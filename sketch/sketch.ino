#include "bluetooth.h"
#include <MeMegaPi.h>
#include <string.h>

Bluetooth bluetooth;
String data;

MeMegaPiDCMotor motor1(PORT1B);
MeMegaPiDCMotor motor2(PORT2B);
MeLineFollower lineFinder(PORT_5);


uint8_t motorSpeed = 100; /* value: between -255 and 255. */
int previousState = -1;

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
}

void loop() {
  if (bluetooth.recievedData()){
    data = bluetooth.getData();
    if (data == "A1"){
      motor1.run(100);
      motor2.run(-100);
    } else if (data == "A0") {
      motor1.stop();
      motor2.stop();
    }
    bluetooth.sendData(data);
  }
}
