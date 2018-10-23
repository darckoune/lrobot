#ifndef DEF_CONTROLLER
#define DEF_CONTROLLER

#include <iostream>
#include <linux/input.h>
using namespace std;

class Controller {

  // Attributs
  private:

  bool A;
  bool B;
  bool X;
  bool Y;
  bool L1;
  bool R1;
  bool JSR_B;
  bool JSL_B;
  bool SELECT;
  bool START;
  bool HOME;

  int  JSL_H;
  int  JSL_V;
  int  JSR_H;
  int  JSR_V;
  int  L2;
  int  R2;
  int  DPAD_H;
  int  DPAD_V;

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

  void update(input_event ev);

  Controller();

  friend ostream &operator<<(ostream &out, Controller &c) {
    out << "\033[2J" << "\033[?25l"
    << "\033[1;1H"  << "A      = " << c.A      << endl
    << "\033[2;1H"  << "B      = " << c.B      << endl
    << "\033[3;1H"  << "X      = " << c.X      << endl
    << "\033[4;1H"  << "Y      = " << c.Y      << endl
    << "\033[5;1H"  << "L1     = " << c.L1     << endl
    << "\033[6;1H"  << "R1     = " << c.R1     << endl
    << "\033[7;1H"  << "JSL_B  = " << c.JSL_B  << endl
    << "\033[8;1H"  << "JSR_B  = " << c.JSR_B  << endl
    << "\033[9;1H"  << "SELECT = " << c.SELECT << endl
    << "\033[10;1H" << "START  = " << c.START  << endl
    << "\033[11;1H" << "HOME   = " << c.HOME   << endl

    << "\033[1;15H" << "JSL_H  = " << c.JSL_H  << endl
    << "\033[2;15H" << "JSL_V  = " << c.JSL_V  << endl
    << "\033[3;15H" << "JSR_H  = " << c.JSR_H  << endl
    << "\033[4;15H" << "JSR_V  = " << c.JSR_V  << endl
    << "\033[5;15H" << "L2     = " << c.L2     << endl
    << "\033[6;15H" << "R2     = " << c.R2     << endl
    << "\033[7;15H" << "DPAD_H = " << c.DPAD_H << endl
    << "\033[8;15H" << "DPAD_V = " << c.DPAD_V << endl;

	  return out;
  }
};

#endif
