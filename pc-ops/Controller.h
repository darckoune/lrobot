#ifndef DEF_CONTROLLER
#define DEF_CONTROLLER

#include <iostream>
#include <linux/input.h>
#include <string.h>
using namespace std;

#define MAX_SPEED 65
#define MEDIUM_SPEED 40

#define FIRST_THRESHOLD 30
#define SECOND_THRESHOLD 70

struct booleanInput {
  bool value;
  bool changed;
};

struct intInput {
  int value;
  bool changed;
};

struct controllerEvent {
  string robotMessage;
  string ihmMessage;
};

class Controller {

  // Attributs
  private:

  booleanInput A;
  booleanInput B;
  booleanInput X;
  booleanInput Y;
  booleanInput L1;
  booleanInput R1;
  booleanInput JSR_B;
  booleanInput JSL_B;
  booleanInput SELECT;
  booleanInput START;
  booleanInput HOME;

  intInput  JSL_H;
  intInput  JSL_V;
  intInput  JSR_H;
  intInput  JSR_V;
  intInput  L2;
  intInput  R2;
  intInput  DPAD_H;
  intInput  DPAD_V;

  int lastMotor1Target;
  int lastMotor2Target;

  void setBooleanInputValue(booleanInput*, bool);
  void setIntInputValue(intInput*, int);
  void setSmallerIntInputValue(intInput*, int);
  void setIntAsBooleanInputValue(intInput*, int);
  bool checkLastJoystick(int x, int y);

  // Methods
  public:

  bool getA()      const;
  bool getB()      const;
  bool getX()      const;
  bool getY()      const;
  bool getL1()     const;
  bool getR1()     const;
  bool getJSR_B()  const;
  bool getJSL_B()  const;
  bool getSELECT() const;
  bool getSTART()  const;
  bool getHOME()   const;

  int  getJSL_H()  const;
  int  getJSL_V()  const;
  int  getJSR_H()  const;
  int  getJSR_V()  const;
  int  getL2()     const;
  int  getR2()     const;
  int  getDPAD_H() const;
  int  getDPAD_V() const;

  controllerEvent getLastEvent();

  void update(input_event ev);

  Controller();

  friend ostream &operator<<(ostream &out, Controller &c) {
    out << "\033[2J" << "\033[?25l"
    << "\033[1;1H"  << "A      = " << c.A.value      << endl
    << "\033[2;1H"  << "B      = " << c.B.value      << endl
    << "\033[3;1H"  << "X      = " << c.X.value      << endl
    << "\033[4;1H"  << "Y      = " << c.Y.value      << endl
    << "\033[5;1H"  << "L1     = " << c.L1.value     << endl
    << "\033[6;1H"  << "R1     = " << c.R1.value     << endl
    << "\033[7;1H"  << "JSL_B  = " << c.JSL_B.value  << endl
    << "\033[8;1H"  << "JSR_B  = " << c.JSR_B.value  << endl
    << "\033[9;1H"  << "SELECT = " << c.SELECT.value << endl
    << "\033[10;1H" << "START  = " << c.START.value  << endl
    << "\033[11;1H" << "HOME   = " << c.HOME.value   << endl

    << "\033[1;15H" << "JSL_H  = " << c.JSL_H.value  << endl
    << "\033[2;15H" << "JSL_V  = " << c.JSL_V.value  << endl
    << "\033[3;15H" << "JSR_H  = " << c.JSR_H.value  << endl
    << "\033[4;15H" << "JSR_V  = " << c.JSR_V.value  << endl
    << "\033[5;15H" << "L2     = " << c.L2.value     << endl
    << "\033[6;15H" << "R2     = " << c.R2.value     << endl
    << "\033[7;15H" << "DPAD_H = " << c.DPAD_H.value << endl
    << "\033[8;15H" << "DPAD_V = " << c.DPAD_V.value << endl;

	  return out;
  }
};

#endif
