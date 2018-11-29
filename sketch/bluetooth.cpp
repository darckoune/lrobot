  #include "Arduino.h"
#include "bluetooth.h"
#include <ArduinoSTL.h>

using namespace std;

Bluetooth::Bluetooth(){
  incomingData = String("");
  data;
  lastChar = 0;
}

int Bluetooth::recievedData(){
  fetchSerial();
  return (data.size() > 0);
}

vector<String> Bluetooth::getData(){
  fetchSerial();
  if (data.size() > 0){
    cleanData();
    vector<String> copy = data;
    data.clear();
    return copy;
  }
}

void Bluetooth::fetchSerial(){
  while (Serial3.available()){
    char c = char(Serial3.read());
    sendData(String(c));
    if (c != 10){
      incomingData = incomingData + c;
    } else {
      data.push_back(incomingData);
      incomingData = "";
    }
    
    lastChar = c;
  }
}

void Bluetooth::cleanData(){
  int movePosition = -1;
  vector<String> cleanedData;
  for(int i = 0; i < data.size() ; i++){
    if (data[i].substring(0,5) == String("MOVE:")){
      if (movePosition == -1){
        movePosition = i;
        cleanedData.push_back(data[i]);
      } else {
        cleanedData[movePosition] = data[i];
      }
    } else {
      cleanedData.push_back(data[i]);
    }
  }
  data = cleanedData;
}

void Bluetooth::sendData(String data){
  Serial3.println(data);
}
