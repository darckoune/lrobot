#include "bluetooth.h"
#include <MeMegaPi.h>
#include <ArduinoSTL.h>
#include <math.h>
#include <queue>

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
queue<float> yellowDetection;
queue<float> redDetection;
queue<float> greenDetection;
int bufferSize = 15;
float yellowSum = 0;
float redSum = 0;
float greenSum = 0;
float yellowThreshold = -80.0;
float redThreshold = -25.0;
float greenThreshold = 10.0;

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

int swapMotor = 1;

uint8_t motorValue(float speed) {
  float secondsPerMinute = 60;
  float wheelDiameter = 60;
  float maxMotorSpeed = 185;
  
  return (secondsPerMinute * speed * maxMotorValue) / (wheelDiameter * PI * maxMotorSpeed);
}

//////////// Robot control functions ///////////////////////

void emptyQueue(queue<float>& queue) {
  while (!queue.empty()) {
    queue.pop();
  }
}

void autoPilotStop() {
  sendAutopilot(false);
  autoPilot = false;
  previousSensorState = -1;
  motor1Target = 0;
  motor2Target = 0;
  led.setColor(0, 0, 0);
  led.show();
  emptyQueue(yellowDetection);
  emptyQueue(redDetection);
  emptyQueue(greenDetection);
}

void updateQueue(queue<float>& queue, float& sum, float value) {
  sum += value;
  queue.push(value);
  if (queue.size() > bufferSize) {
    sum -= queue.front();
    queue.pop();
  }
}

float getValue(queue<float> queue, float sum) {
  return (1.0 - sum / queue.size()) * 10000.0;
}

void manageAutopilot(){
  if (autoPilot) {
    int sensorState = lineFinder.readSensors();
    if (sensorState != previousSensorState) {
      switch(sensorState) {
        case S1_IN_S2_IN:
          sendLine(true, true);
          motor1Target = maxMotorValue;
          motor2Target = -maxMotorValue;
          break;
        case S1_IN_S2_OUT:
          sendLine(false, true);
          motor1Target = maxMotorValue;
          motor2Target = 0;
          break;
        case S1_OUT_S2_IN:
          sendLine(true, false);
          motor1Target = 0;
          motor2Target = -maxMotorValue;
          break;
        case S1_OUT_S2_OUT:
          sendLine(false, false);
          motor1Target = -maxMotorValue/3;
          motor2Target = +maxMotorValue/3;
          break;
        default:
          break;
      }
      
      previousSensorState = sensorState;
    }
    
    led.setColor(255, 255, 0);
    led.show();
    float yellowValue = lightSensor.read();

    led.setColor(0, 0, 255);
    led.show();
    float blueValue = lightSensor.read();

    updateQueue(yellowDetection, yellowSum, yellowValue / blueValue);
    bool yellowDetected = yellowDetection.size() == bufferSize && getValue(yellowDetection, yellowSum) < yellowThreshold;

    led.setColor(255, 0, 0);
    led.show();
    float redValue = lightSensor.read();

    led.setColor(0, 255, 255);
    led.show();
    float cyanValue = lightSensor.read();

    updateQueue(redDetection, redSum, redValue / cyanValue);
    bool redDetected = redDetection.size() == bufferSize && getValue(redDetection, redSum) < redThreshold;

    led.setColor(0, 255, 0);
    led.show();
    float greenValue = lightSensor.read();

    led.setColor(255, 0, 255);
    led.show();
    float magentaValue = lightSensor.read();
    
    updateQueue(greenDetection, greenSum, greenValue / magentaValue);
    bool greenDetected = greenDetection.size() == bufferSize && getValue(greenDetection, greenSum) < greenThreshold;
  
    if (yellowDetected || redDetected || greenDetected) {
      autoPilotStop();
      sendColor(yellowDetected, redDetected, greenDetected);
      sendNextPhase();
    }
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
  bluetooth.sendData("-LOG Proceeding command... (" + command +")");
  if (command.substring(0,2) == String("A")){
    bluetooth.sendData("-LOG SWITCH !");
    if (autoPilot){
      autoPilotStop();
    } else {
      // Implémenter une véfification de la présence de la ligne
      autoPilot = true;
      sendAutopilot(true);
      sendNextPhase();
    }
  }
  if(autoPilot){
    return;
  }
  if (command.substring(0,1) == String("M")){
    bluetooth.sendData("-LOG MOVING");
    controlMove((int) command[1],(int) command[2]);
  }
  if (command.substring(0,1) == String("C")){
    switch (command[1]) {
      case 'S':
        motor3Target = 0;
        bluetooth.sendData("-LOG CRANE STOP");
        break;
      case 'L':
        motor3Target = 50;
        bluetooth.sendData("-LOG CRANE LOWER");
        break;
      case 'R':
        motor3Target = -50;
        bluetooth.sendData("-LOG CRANE RAISE");
        break;
      default:
        break;
    }
  }
  if (command.substring(0,1) == String("P")){
    switch (command[1]) {
      case 'S':
        motor4Target = 0;
        bluetooth.sendData("-LOG PLIERS STOP");
        break;
      case 'O':
        motor4Target = -150;
        bluetooth.sendData("-LOG PLIERS OPEN");
        break;
      case 'C':
        motor4Target = 150;
        bluetooth.sendData("-LOG PLIERS CLOSE");
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
    motor1.run(swapMotor * way * maxMotorValue);
    motor2.run(swapMotor * way * maxMotorValue);
    waitedTime = millis() + 4000;
    restartMotorsAfterDelay = true;
    motor1Target = 0;
    motor2Target = 0;
    motor1Actual = 0;
    motor2Actual = 0;
  }
  if (command.substring(0,1) == String("S")){
    swapMotor = swapMotor * -1;
  }
}

void updateMotors(){
  if(waitedTime < millis()){
    bool speedChanged = false;
    if (motor1Target != motor1Actual){
      speedChanged = true;
      if (motor1Target == 0){
        motor1.run(0);
      } else {
        motor1.run(swapMotor * motor1Target);
        bluetooth.sendData("-LOG New motor speed : " + String(motor1Target));
      } 
    }
  
    if (motor2Target != motor2Actual){
      speedChanged = true;
      if (motor2Target == 0){
        motor2.run(0);
      } else {
        motor2.run(swapMotor * motor2Target);
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
      speedChanged = true;
      // bluetooth.sendData("-LOG Change de sens : " + String(motor1Target < 0 != motor1Actual < 0));
      motor1.stop(); // On arrête les moteurs des chenilles
      motor2.stop();
      waitedTime = millis() + delayForMotorRestart;
      restartMotorsAfterDelay = true; // Et on signale qu'il faut les redémarrer
    }
  
    motor1Actual = motor1Target;
    motor2Actual = motor2Target;
    motor3Actual = motor3Target;
    motor4Actual = motor4Target;

    if (speedChanged){
      sendSpeed(motor1Target, -motor2Target);
    }
  }
}

void restartMotorsIfNeeded(){
  if(restartMotorsAfterDelay && waitedTime < millis()){
    if (motor1Actual == 0){
      motor1.stop();
    } else {
      motor1.run(motor1Actual * swapMotor);
    }
    if (motor2Actual == 0){
      motor2.stop();
    } else {
      motor2.run(motor2Actual * swapMotor);
    }
    restartMotorsAfterDelay = false;
  }
}


//////////// ARDUINO RESERVED SETUP & LOOP FUNCTIONS /////////////////////

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
  bluetooth.sendData("-LOG Booting");
}

void loop() {
  restartMotorsIfNeeded();

  manageCommands();

  manageAutopilot();
  
  updateMotors();
}
