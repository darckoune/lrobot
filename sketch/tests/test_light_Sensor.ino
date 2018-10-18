#include "MeMegaPi.h"

MeLightSensor lightSensor(PORT_5);
int value = 0;      

void setup()
{
 
  Serial.begin(9600);
}


void loop()
{

  value = lightSensor.read();


  Serial.print("value = ");
  Serial.println(value);

  delay(100);
}
/*Le module du Light Sensor va renvoyer les valeurs de l’intensité de la lumière qu’il reçoit.
Les valeurs vont de 0 à 4095.
Le Light Sensor receptionne la lumière ambiante, alors il faut mieux le positionner dans un espace ouvert.
Il ne peut pas lire les valeurs des infrarouges ni ultraviolet.
*/
