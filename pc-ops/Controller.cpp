#include "Controller.h"

using namespace std;

bool Controller::getA()      const { return A; }
bool Controller::getB()      const { return B; }
bool Controller::getX()      const { return X; }
bool Controller::getY()      const { return Y; }
bool Controller::getL1()     const { return L1; }
bool Controller::getR1()     const { return R1; }
bool Controller::getJSR_B()  const { return JSR_B; }
bool Controller::getJSL_B()  const { return JSL_B; }
bool Controller::getSELECT() const { return SELECT; }
bool Controller::getSTART()  const { return START; }
bool Controller::getHOME()   const { return X; }

int  Controller::getJSL_H()  const { return JSL_H; }
int  Controller::getJSL_V()  const { return JSL_V; }
int  Controller::getJSR_H()  const { return JSR_H; }
int  Controller::getJSR_V()  const { return JSR_V; }
int  Controller::getL2()     const { return L2; }
int  Controller::getR2()     const { return R2; }
int  Controller::getDPAD_H() const { return DPAD_H; }
int  Controller::getDPAD_V() const { return DPAD_V; }

void Controller::update(input_event ev) {
  if (ev.type == 1) { // digital
    switch(ev.code) {
      case 304: A      = ev.value; break;
      case 305: B      = ev.value; break;
      case 307: X      = ev.value; break;
      case 308: Y      = ev.value; break;
      case 310: L1     = ev.value; break;
      case 311: R1     = ev.value; break;
      case 317: JSL_B  = ev.value; break;
      case 318: JSR_B  = ev.value; break;
      case 314: SELECT = ev.value; break;
      case 315: START  = ev.value; break;
      case 316: HOME   = ev.value; break;
      default: cout << "[CONTROLLER] digital not assigned" << endl;
    }
  } else if (ev.type == 3) {            // analogic and dpad
    switch(ev.code) {
      case   0: JSL_H  = ev.value; break;
      case   1: JSL_V  = ev.value; break;
      case   3: JSR_H  = ev.value; break;
      case   4: JSR_V  = ev.value; break;
      case   2: L2     = ev.value; break;
      case   5: R2     = ev.value; break;
      case  16: DPAD_H = ev.value; break;
      case  17: DPAD_V = ev.value; break;
      default: cout << "[CONTROLLER] analog not assigned" << endl;
    }
  }
}

Controller::Controller(void) {
  A      = 0;
  B      = 0;
  X      = 0;
  Y      = 0;
  L1     = 0;
  R1     = 0;
  JSR_B  = 0;
  JSL_B  = 0;
  SELECT = 0;
  START  = 0;
  HOME   = 0;

  JSL_H  = 0;
  JSL_V  = 0;
  JSR_H  = 0;
  JSR_V  = 0;
  L2     = 0;
  R2     = 0;
  DPAD_H = 0;
  DPAD_V = 0;

  // cout << "[CONTROLLER] object created" << endl;
}
