#define MEDIUM_SPEED 40

#define BOOST_MEDIUM_SPEED 100

#define FIRST_THRESHOLD 30
#define SECOND_THRESHOLD 70

void controlMove(int x, int y, bool limited){
  //int power = - x;
  //int turn = y;
    
  //motor1Target = -power - turn;
  //motor2Target = power - turn;

  x--;
  y--;

  int maxSpeed =  limited ? FIFTEEN_MMS_LIMIT : EIGHTY_MMS_LIMIT;
  int mediumSpeed = limited ? MEDIUM_SPEED : BOOST_MEDIUM_SPEED;
  
  bluetooth.sendData("-LOG x : " + String(x));
  bluetooth.sendData("-LOG y : " + String(y));
  
  int absx = abs(x);
  int absy = abs(y);

  if (absx < FIRST_THRESHOLD && absy < FIRST_THRESHOLD){
    bluetooth.sendData("-LOG Case 0");
    motor1Target = 0;
    motor2Target = 0;
  } else if(absx < FIRST_THRESHOLD){
    bluetooth.sendData("-LOG Case 1");
    int yway = y > 0 ? 1 : -1;
    int power;
    if (absy < 50){
      power = 50;
    } else if (absy < SECOND_THRESHOLD){
      power = 100;
    } else {
      power = 255;
    }
    motor1Target = -1 * swapMotor * yway * power;
    motor2Target = yway * swapMotor * power;
  } else if (absy < FIRST_THRESHOLD) {
    bluetooth.sendData("-LOG Case 2");
    int xway = x > 0 ? 1 : -1;
    int power = absx < SECOND_THRESHOLD ? mediumSpeed : maxSpeed;
    motor1Target = xway * power;
    motor2Target = xway * power;
  } else if(absy < SECOND_THRESHOLD){
    bluetooth.sendData("-LOG Case 3");
    int xway = x > 0 ? 1 : -1;
    if (swapMotor == 1){
      if (y > 0){
        motor1Target = 0;
        motor2Target = xway * mediumSpeed;
      } else {
        motor1Target = xway * mediumSpeed;
        motor2Target = 0;
      }
    } else {
      if (y > 0){
        motor1Target = xway * mediumSpeed;
        motor2Target = 0;
      } else {
        motor1Target = 0;
        motor2Target = xway * mediumSpeed;
      }
    }
  } else {
    bluetooth.sendData("-LOG Case 4");
    int xway = x > 0 ? 1 : -1;
    int yway = y > 0 ? 1 : -1;
    if (swapMotor == 1){
      if (y > 0){
        motor1Target = 0;
        motor2Target = xway * maxSpeed;
      } else {
        motor1Target = xway * maxSpeed;
        motor2Target = 0;
      }
    } else {
      if (y > 0){
        motor1Target = xway * maxSpeed;
        motor2Target = 0;
      } else {
        motor1Target = 0;
        motor2Target = xway * maxSpeed;
      }
    }
    
  }

  motor2Target = -motor2Target;
}
