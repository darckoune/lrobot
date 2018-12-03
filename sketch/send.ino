#define DELAY_ALIVE 250
#define SPEED_RATIO 78

void sendSpeed(int motor1, int motor2){
  int s = (((motor1 * SPEED_RATIO) /255) + ((motor2 * SPEED_RATIO) / 255))/2;
  if(s < 0){
    s = -s; 
  }
  if (s == 16){
    s = 15;
  }
  // bluetooth.sendData("-LOG: speed " + String(s));
  bluetooth.sendData("S" + String((char) (s + 1)));
}

void sendLine(bool left, bool right){
  int line = 4;
  line = left ? line +  2 : line;
  line = right ? line +  1 : line;
  bluetooth.sendData("L" + String((char) line));
}

void sendColor(bool yellow, bool red, bool green){
  int color = 8;
  color = yellow ? color +  1 : color;
  color = red ? color +  2 : color;
  color = green ? color +  4 : color;
  bluetooth.sendData("C" + String((char) color));
}

void sendAutopilot(bool autopilotStatus){
  int sentStatus = 2;
  sentStatus = autopilotStatus ? sentStatus +  1 : sentStatus;
  Serial.println("A" + String(sentStatus));
  bluetooth.sendData("A" + String((char) sentStatus));
}

void sendNextPhase(){
  bluetooth.sendData("NP");
}

long alive = 0;

void sendImAlive(){
  if (millis() - alive > DELAY_ALIVE){
    bluetooth.sendData(String("Z"));
    alive = millis();  
  }
}
