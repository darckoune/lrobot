#include "bluetooth.h"
#include <MeMegaPi.h>
#include <ArduinoSTL.h>

using namespace std;

Bluetooth bluetooth;
vector<String> data;

MeMegaPiDCMotor motor1(PORT1B);
MeMegaPiDCMotor motor2(PORT2B);
MeLineFollower lineFinder(PORT_5);
MeLightSensor lightSensor(PORT_6);
MeRGBLed led(PORT_7);

uint8_t motorSpeed = 100; /* value: between -255 and 255. */
int previousSensorState = -1;
bool autoPilot = true;

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
}

void loop() {
  if (bluetooth.recievedData()){
    data = bluetooth.getData();
    if (data.size() == 1){
      motor1.run(100);
      motor2.run(-100);
    } else if (data.size() == 2) {
      motor1.stop();
      motor2.stop();
    }
    String text = String("Data recieved (" + String(data.size()) + ") : ");
    for (int i = 0 ; i < data.size() ; i++){
      proceedCommand(data[i]);
    }
  }

  if (autoPilot) {
    int sensorState = lineFinder.readSensors();
    
    if (sensorState != previousSensorState) {
      switch(sensorState) {
        case S1_IN_S2_IN:
          motor1.run(motorSpeed);
          motor2.run(-motorSpeed);
          break;
        case S1_IN_S2_OUT:
          motor1.stop();
          motor2.run(-2*motorSpeed);
          break;
        case S1_OUT_S2_IN:
          motor1.run(2*motorSpeed);
          motor2.stop();
          break;
        case S1_OUT_S2_OUT:
          motor1.run(-motorSpeed);
          motor2.run(motorSpeed);
          break;
        default:
          break;
      }
      
      previousSensorState = sensorState;
    }
    
    led.setColor(255, 0, 0);
    led.show();
    int colorValue = lightSensor.read();
    led.setColor(0, 255, 255);
    led.show();
    int oppositeValue = lightSensor.read();
  
    if (colorValue > oppositeValue) {
      autoPilot = false;
      motor1.stop();
      motor2.stop();
      led.setColor(0, 0, 0);
      led.show();
    }
  }
}

void proceedCommand(String command){
  bluetooth.sendData("Proceeding command... (" + command +")");
  if (command.substring(0,2) == String("A")){
    autoPilot = !autoPilot;
    motor1.stop();
    motor2.stop();
    bluetooth.sendData("SWITCH !");
  }
}
