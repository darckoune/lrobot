#include <MeMegaPi.h>

void setup() {
  Serial.begin(9600);
  Serial3.begin(115200);
}

void loop() {
  // Write back data received from Bluetooth to Serial monitor
  if (Serial3.available()) {
    Serial.write(Serial3.read());
  }
  // Send to Bluetooth data received from Serial monitor
  if (Serial.available()) {
    Serial3.write(Serial.read());
  }
}
