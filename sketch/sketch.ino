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

int motor1Target = 0;
int motor1Actual = 0;
int motor2Target = 0;
int motor2Actual = 0;
int motor3Target = 0;
int motor3Actual = 0;
int motor4Target = 0;
int motor4Actual = 0;
long waitedTime = 0;
bool restartMotorsAfterDelay = false;
int delayForMotorRestart = 100;

uint8_t motorValue(float speed) {
  float secondsPerMinute = 60;
  float wheelDiameter = 60;
  float maxMotorSpeed = 185;
  
  return (secondsPerMinute * speed * maxMotorValue) / (wheelDiameter * PI * maxMotorSpeed);
}

//////////// Robot control functions ///////////////////////

void autoPilotStop() {
  bluetooth.sendData("Disable autopilot");
  autoPilot = false;
  motor1Target = 0;
  motor2Target = 0;
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
          motor1Target = maxMotorValue;
          motor2Target = -maxMotorValue;
          break;
        case S1_IN_S2_OUT:
          motor1Target = -maxMotorValue;
          motor2Target = -maxMotorValue;
          break;
        case S1_OUT_S2_IN:
          motor1Target = maxMotorValue;
          motor2Target = maxMotorValue;
          break;
        case S1_OUT_S2_OUT:
          motor1Target = -maxMotorValue/3;
          motor2Target = +maxMotorValue/3;
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
    bluetooth.sendData("SWITCH !");
    if (autoPilot){
      autoPilotStop();
    } else {
      autoPilot = true;
    }
  }
  if(autoPilot){
    return;
  }
  if (command.substring(0,1) == String("M")){
    bluetooth.sendData("MOVING");
    int power = - (int) command[1];
    int turn = (int) command[2];
    
    motor1Target = -power - turn;
    motor2Target = power - turn;

    bluetooth.sendData("Y : " + String(power));
    bluetooth.sendData("X : " + String(turn));

    bluetooth.sendData(String(motor1Target));
    bluetooth.sendData(String(motor2Target));
  }
  if (command.substring(0,1) == String("C")){
    switch (command[1]) {
      case 'S':
        motor3Target = 0;
        bluetooth.sendData("CRANE STOP");
        break;
      case 'L':
        motor3Target = 50;
        bluetooth.sendData("CRANE LOWER");
        break;
      case 'R':
        motor3Target = -50;
        bluetooth.sendData("CRANE RAISE");
        break;
      default:
        break;
    }
  }
  if (command.substring(0,1) == String("P")){
    switch (command[1]) {
      case 'S':
        motor4Target = 0;
        bluetooth.sendData("PLIERS STOP");
        break;
      case 'O':
        motor4Target = 150;
        bluetooth.sendData("PLIERS OPEN");
        break;
      case 'C':
        motor4Target = -150;
        bluetooth.sendData("PLIERS CLOSE");
        break;
      default:
        break;
    }
  }
  if (command.substring(0,1) == String("R")){
    int way = 0;
    switch (command[1]) {
      case 'R':
        way = -1;
        break;
      case 'L':
        way = 1;
        break;
      default:
        way = 0;
        break;
    }
    motor1.run(way * maxMotorValue);
    motor2.run(way * maxMotorValue);
    waitedTime = millis() + 4000;
    restartMotorsAfterDelay = true;
    motor1Target = 0;
    motor2Target = 0;
    motor1Actual = 0;
    motor2Actual = 0;
  }
}

void updateMotors(){
  if(waitedTime < millis()){
    if (motor1Target != motor1Actual){
      if (motor1Target == 0){
        motor1.run(0);
      } else {
        motor1.run(motor1Target);
        bluetooth.sendData("New motor speed : " + String(motor1Target));
      } 
    }
  
    if (motor2Target != motor2Actual){
      if (motor2Target == 0){
        motor2.run(0);
      } else {
        motor2.run(motor2Target);
      }
    }
  
    if (motor3Target != motor3Actual){
      if (motor3Target == 0){
        motor3.stop();
      } else {
        motor3.run(motor3Target);
      }
    }
  
    if (motor4Target != motor4Actual){
      if (motor4Target == 0){
        motor4.stop();
      } else {
        motor4.run(motor4Target);
      }
    }
  
    // Si un moteur de chenille a changé de sens
    if ((motor1Target < 0 != motor1Actual < 0) || (motor2Target < 0 != motor2Actual < 0)){
      bluetooth.sendData("Change de sens : " + String(motor1Target < 0 != motor1Actual < 0));
      motor1.stop(); // On arrête les moteurs des chenilles
      motor2.stop();
      waitedTime = millis() + delayForMotorRestart;
      restartMotorsAfterDelay = true; // Et on signale qu'il faut les redémarrer
    }
  
    motor1Actual = motor1Target;
    motor2Actual = motor2Target;
    motor3Actual = motor3Target;
    motor4Actual = motor4Target;
  }
}

void restartMotorsIfNeeded(){
  if(restartMotorsAfterDelay && waitedTime < millis()){
    if (motor1Actual == 0){
      motor1.stop();
    } else {
      motor1.run(motor1Actual);
      bluetooth.sendData(String(motor1Actual));
    }
    if (motor2Actual == 0){
      motor2.stop();
    } else {
      motor2.run(motor2Actual);
    }
    restartMotorsAfterDelay = false;
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
