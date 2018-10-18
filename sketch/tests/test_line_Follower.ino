#include "MeMegaPi.h"

MeLineFollower lineFinder(PORT_5); 

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int sensorState = lineFinder.readSensors();
  switch(sensorState)
  {
    case S1_IN_S2_IN: Serial.println("Sensor 1 and 2 are inside of black line"); break;
    case S1_IN_S2_OUT: Serial.println("Sensor 2 is outside of black line"); break;
    case S1_OUT_S2_IN: Serial.println("Sensor 1 is outside of black line"); break;
    case S1_OUT_S2_OUT: Serial.println("Sensor 1 and 2 are outside of black line"); break;
    default: break;
  }
  delay(200);
}

/*Le Line Follower Sensor permet de détecter si le détecteur se trouve au dessus d’un objet de couleur noir ou blanc.
La distance maximale a laquelle le détecteur fonctionne est de 3 cm, donc il faudra le mettre juste au dessus du centre des roues avant.
La valeur par défaut du détecteur est noire.
*/
