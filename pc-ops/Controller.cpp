#include "Controller.h"

using namespace std;

bool Controller::getA()      const { return A.value; }
bool Controller::getB()      const { return B.value; }
bool Controller::getX()      const { return X.value; }
bool Controller::getY()      const { return Y.value; }
bool Controller::getL1()     const { return L1.value; }
bool Controller::getR1()     const { return R1.value; }
bool Controller::getJSR_B()  const { return JSR_B.value; }
bool Controller::getJSL_B()  const { return JSL_B.value; }
bool Controller::getSELECT() const { return SELECT.value; }
bool Controller::getSTART()  const { return START.value; }
bool Controller::getHOME()   const { return X.value; }

int  Controller::getJSL_H()  const { return JSL_H.value; }
int  Controller::getJSL_V()  const { return JSL_V.value; }
int  Controller::getJSR_H()  const { return JSR_H.value; }
int  Controller::getJSR_V()  const { return JSR_V.value; }
int  Controller::getL2()     const { return L2.value; }
int  Controller::getR2()     const { return R2.value; }
int  Controller::getDPAD_H() const { return DPAD_H.value; }
int  Controller::getDPAD_V() const { return DPAD_V.value; }

void Controller::update(input_event ev) {
  if (ev.type == 1) { // digital
    switch(ev.code) {
      case 304: A.value      = ev.value; break;
      case 305: B.value      = ev.value; break;
      case 307: X.value      = ev.value; break;
      case 308: Y.value      = ev.value; break;
      case 310: L1.value     = ev.value; break;
      case 311: R1.value     = ev.value; break;
      case 317: JSL_B.value  = ev.value; break;
      case 318: JSR_B.value  = ev.value; break;
      case 314: SELECT.value = ev.value; break;
      case 315: START.value  = ev.value; break;
      case 316: HOME.value   = ev.value; break;
      default: cout << "[CONTROLLER] digital not assigned" << endl;
    }
  } else if (ev.type == 3) {            // analogic and dpad
    switch(ev.code) {
      case   0: JSL_H.value  = ev.value; break;
      case   1: JSL_V.value  = ev.value; break;
      case   3: JSR_H.value  = ev.value; break;
      case   4: JSR_V.value  = ev.value; break;
      case   2: L2.value     = ev.value; break;
      case   5: R2.value     = ev.value; break;
      case  16: DPAD_H.value = ev.value; break;
      case  17: DPAD_V.value = ev.value; break;
      default: cout << "[CONTROLLER] analog not assigned" << endl;
    }
  }
}

Controller::Controller(void) {
  A      = {false , false};
  B      = {false , false};
  X      = {false , false};
  Y      = {false , false};
  L1     = {false , false};
  R1     = {false , false};
  JSR_B  = {false , false};
  JSL_B  = {false , false};
  SELECT = {false , false};
  START  = {false , false};
  HOME   = {false , false};

  JSL_H  = {0 , false};
  JSL_V  = {0 , false};
  JSR_H  = {0 , false};
  JSR_V  = {0 , false};
  L2     = {0 , false};
  R2     = {0 , false};
  DPAD_H = {0 , false};
  DPAD_V = {0 , false};

  // cout << "[CONTROLLER] object created" << endl;
}
