#ifndef BLUETOOTH_H
#define BLUETOOTH_H

class Bluetooth {
  int dataAvailable;
  String data;
  char lastChar;

  public:
  Bluetooth();
  int recievedData();
  String getData();
  void sendData(String);

  private:
  void fetchSerial();
};

#endif
