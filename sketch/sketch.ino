#include "bluetooth.h"
#include <MeMegaPi.h>
#include <ArduinoSTL.h>
#include <math.h>

using namespace std;

Bluetooth bluetooth;
vector<String> data;

MeMegaPiDCMotor motor1(PORT1B);
MeMegaPiDCMotor motor2(PORT2B);
MeMegaPiDCMotor motor3(PORT3B);
MeMegaPiDCMotor motor4(PORT4B);
MeLineFollower lineFinder(PORT_5);
MeLightSensor lightSensor(PORT_6);
MeRGBLed led(PORT_7);

bool autoPilot = false;
uint8_t maxMotorValue = 255;
int previousSensorState = -1;
float colorThreshold = 1;
int colorDetected = 0;
int detectionThreshold = 2;

uint8_t motorValue(float speed) {
  float secondsPerMinute = 60;
  float wheelDiameter = 60;
  float maxMotorSpeed = 185;
  
  return (secondsPerMinute * speed * maxMotorValue) / (wheelDiameter * PI * maxMotorSpeed);
}

void autoPilotStop() {
  autoPilot = false;
  motor1.stop();
  motor2.stop();
  led.setColor(0, 0, 0);
  led.show();
  colorDetected = 0;
}

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
          motor1.run(motorValue(80));
          motor2.run(-motorValue(80));
          break;
        case S1_IN_S2_OUT:
          motor1.run(-maxMotorValue);
          motor2.run(-maxMotorValue);
          break;
        case S1_OUT_S2_IN:
          motor1.run(maxMotorValue);
          motor2.run(maxMotorValue);
          break;
        case S1_OUT_S2_OUT:
          motor1.run(-motorValue(80));
          motor2.run(motorValue(80));
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
    int oppositeColorValue = lightSensor.read();
  
    if (colorValue > colorThreshold * oppositeColorValue) {
      colorDetected++;

      if (colorDetected >= detectionThreshold) {
        autoPilotStop();
      }
    }
    else {
      colorDetected = 0;
    }
  }
}

void proceedCommand(String command){
  bluetooth.sendData("Proceeding command... (" + command +")");
  if (command.substring(0,2) == String("A")){
    if (autoPilot){
      autoPilotStop();
      bluetooth.sendData("SWITCH !");
    } else {
      autoPilot = true;
    }
  }
  if (command.substring(0,1) == String("M")){
    bluetooth.sendData("MOVING");
    int power = - (int) command[1];
    int turn = (int) command[2];
    
    int motor1power = -power - turn;
    int motor2power = power - turn;

    bluetooth.sendData(String(motor1power));
    bluetooth.sendData(String(motor2power));
    
    bluetooth.sendData(String(power));
    if (motor2power != 0){
      motor2.run(motor2power);
    } else {
      motor2.stop();
    }
    if (motor1power != 0){
      motor1.run(motor1power);
    } else {
      motor1.stop();
    }
  }
  if (command.substring(0,1) == String("C")){
    switch (command[1]) {
      case 'S':
        motor3.stop();
        bluetooth.sendData("CRANE STOP");
        break;
      case 'L':
        motor3.run(50);
        bluetooth.sendData("CRANE LOWER");
        break;
      case 'R':
        motor3.run(-50);
        bluetooth.sendData("CRANE RAISE");
        break;
      default:
        break;
    }
  }
  if (command.substring(0,1) == String("P")){
    switch (command[1]) {
      case 'S':
        motor4.stop();
        bluetooth.sendData("PLIERS STOP");
        break;
      case 'O':
        motor4.run(50);
        bluetooth.sendData("PLIERS OPEN");
        break;
      case 'C':
        motor4.run(-50);
        bluetooth.sendData("PLIERS CLOSE");
        break;
      default:
        break;
    }
  }
}
