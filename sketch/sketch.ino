#include "bluetooth.h"
#include <MeMegaPi.h>
#include <ArduinoSTL.h>

using namespace std;

Bluetooth bluetooth;
vector<String> data;
MeRGBLed led(0, 30);

MeMegaPiDCMotor motor1(PORT1B);
MeMegaPiDCMotor motor2(PORT2B);
MeLineFollower lineFinder(PORT_5);


uint8_t motorSpeed = 100; /* value: between -255 and 255. */
int previousState = -1;

bool ledState = false;

void toggleLed(){
   if (ledState){
      digitalWrite(13, HIGH);
   } else {
      digitalWrite(13, LOW);
   }
   ledState = !ledState;
}


void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
  led.setpin(13);
}

void loop() {
  if (bluetooth.recievedData()){
    data = bluetooth.getData();
    toggleLed();
    if (data.size() == 1){
      motor1.run(100);
      motor2.run(-100);
    } else if (data.size() == 2) {
      motor1.stop();
      motor2.stop();
    }
    String text = String("Data recieved (" + String(data.size()) + ") : ");
    for (int i = 0 ; i < data.size() ; i++){
      text += " " + data[i];
    }
    bluetooth.sendData(text);
  }
}
