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

bool autoPilot = true;
uint8_t maxMotorValue = 255;
int previousSensorState = -1;
float colorThreshold = 1;
int colorDetected = 0;
int detectionThreshold = 2;

int motor1target = 0;
int motor2target = 0;
int motor1actual = 0;
int motor2actual = 0;
int motor3target = 0;
int motor3actual = 0;
int motor4target = 0;
int motor4actual = 0;
bool restartMotorsAfterDelay = false;
int delayForMotorRestart = 75;

uint8_t motorValue(float speed) {
  float secondsPerMinute = 60;
  float wheelDiameter = 60;
  float maxMotorSpeed = 185;
  
  return (secondsPerMinute * speed * maxMotorValue) / (wheelDiameter * PI * maxMotorSpeed);
}

//////////// Robot control functions ///////////////////////

void autoPilotStop() {
  autoPilot = false;
  motor1target = 0;
  motor2target = 0;
  led.setColor(0, 0, 0);
  led.show();
  colorDetected = 0;
}

void manageAutopilot(){
  if (autoPilot) {
    int sensorState = lineFinder.readSensors();
    
    if (sensorState != previousSensorState) {
      switch(sensorState) {
        case S1_IN_S2_IN:
          motor1target = maxMotorValue;
          motor2target = -maxMotorValue;
          break;
        case S1_IN_S2_OUT:
          motor1target = -maxMotorValue;
          motor2target = -maxMotorValue;
          break;
        case S1_OUT_S2_IN:
          motor1target = maxMotorValue;
          motor2target = maxMotorValue;
          break;
        case S1_OUT_S2_OUT:
          bluetooth.sendData("Au secours");
          motor1target = -maxMotorValue;
          motor2target = +maxMotorValue;
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
  
    /*if (colorValue > colorThreshold * oppositeColorValue) {
      colorDetected++;

      if (colorDetected >= detectionThreshold) {
        autoPilotStop();
      }
    }
    else {
      colorDetected = 0;
    }*/
  }
}

void manageCommands(){
  if (bluetooth.recievedData()){
    data = bluetooth.getData();
    String text = String("Data recieved (" + String(data.size()) + ") : ");
    for (int i = 0 ; i < data.size() ; i++){
      proceedCommand(data[i]);
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
    
    motor1target = -power - turn;
    motor2target = power - turn;

    bluetooth.sendData(String(motor1target));
    bluetooth.sendData(String(motor2target));
  }
  if (command.substring(0,1) == String("C")){
    switch (command[1]) {
      case 'S':
        motor3target = 0;
        bluetooth.sendData("CRANE STOP");
        break;
      case 'L':
        motor3target = 50;
        bluetooth.sendData("CRANE LOWER");
        break;
      case 'R':
        motor3target = -50;
        bluetooth.sendData("CRANE RAISE");
        break;
      default:
        break;
    }
  }
  if (command.substring(0,1) == String("P")){
    switch (command[1]) {
      case 'S':
        motor4target = 0;
        bluetooth.sendData("PLIERS STOP");
        break;
      case 'O':
        motor4target = 150;
        bluetooth.sendData("PLIERS OPEN");
        break;
      case 'C':
        motor4target = -150;
        bluetooth.sendData("PLIERS CLOSE");
        break;
      default:
        break;
    }
  }
}

void updateMotors(){
  if (motor1target != motor1actual){
    if (motor1target == 0){
      motor1.stop();
    } else {
      motor1.run(motor1target);
    }
  }

  if (motor2target != motor2actual){
    if (motor2target == 0){
      motor2.stop();
    } else {
      motor2.run(motor2target);
    }
  }

  if (motor3target != motor3actual){
    if (motor3target == 0){
      motor3.stop();
    } else {
      motor3.run(motor3target);
    }
  }

  if (motor4target != motor4actual){
    if (motor4target == 0){
      motor4.stop();
    } else {
      motor4.run(motor4target);
    }
  }

  // Si un moteur de chenille a changé de sens
  if ((motor1target * motor1actual < 0) || (motor2target * motor2actual < 0)){
    motor1.stop(); // On arrête les moteurs des chenilles
    motor2.stop();
    restartMotorsAfterDelay = true; // Et on signale qu'il faut les redémarrer
  }

  motor1actual = motor1target;
  motor2actual = motor2target;
  motor3actual = motor3target;
  motor4actual = motor4target;
}

void restartMotorsIfNeeded(){
  if(restartMotorsAfterDelay){
    delay(delayForMotorRestart);
    if (motor1actual == 0){
      motor1.stop();
    } else {
      motor1.run(motor1actual);
    }
    if (motor2actual == 0){
      motor2.stop();
    } else {
      motor2.run(motor2actual);
    }
  }
}


//////////// ARDUINO RESERVED SETUP & LOOP FUNCTIONS /////////////////////

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
  bluetooth.sendData("Booting");
}

void loop() {
  restartMotorsIfNeeded();

  manageCommands();

  manageAutopilot();

  updateMotors();
}
