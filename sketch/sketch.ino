#include <MeMCore.h>
#include <MeBluetooth.h>

void setup()
{
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(2000);
  digitalWrite(13, HIGH);
  delay(3000);
  digitalWrite(13, LOW);
  delay(4000);
}
