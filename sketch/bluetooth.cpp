#include <MeMegaPi.h>
#include "bluetooth.h"

Bluetooth::Bluetooth(){
  dataAvailable = false;
  data = String("");
  lastChar = 0;
}

int Bluetooth::recievedData(){
  fetchSerial();
  return dataAvailable;
}

String Bluetooth::getData(){
  fetchSerial();
  if (dataAvailable){
    String s = data;
    dataAvailable = false;
    data = "";
    return s;
  } else {
    return String("");
  }
}

void Bluetooth::fetchSerial(){
  while (Serial3.available()){
    char c = char(Serial3.read());
    if (c != 13 && c != 10){
      data = data + c; 
    }
    if (c == 10 && lastChar == 13){
      dataAvailable = true;
    }
    lastChar = c;
  }
}

void Bluetooth::sendData(String data){
  Serial3.println(data);
}
