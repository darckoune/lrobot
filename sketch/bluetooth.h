#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <ArduinoSTL.h>

using namespace std;

class Bluetooth {
  
  public:
  Bluetooth();
  int recievedData();
  vector<String> getData();
  void sendData(String);

  private:
  void fetchSerial();
  void cleanData();

  String incomingData;
  vector<String> data;
  char lastChar;
};

#endif
