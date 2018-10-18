#include "MeMegaPi.h"
#include <Wire.h>

MeGyro gyro(PORT_5);
void setup()
{
  Serial.begin(9600);
  gyro.begin();
}

void loop()
{
  gyro.update();
  Serial.read();
  Serial.print("X:");
  Serial.print(gyro.getAngleX() );
  Serial.print(" Y:");
  Serial.print(gyro.getAngleY() );
  Serial.print(" Z:");
  Serial.println(gyro.getAngleZ() );
  delay(100);
}


//Le Gyro Sensor permet de calculer l’angle actuel du module sur 3 axes.
