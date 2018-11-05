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

string Controller::getLastEvent() {
  if(A.changed){
    A.changed = false;
    if(A.value){
      return (string("CRANE:LOWER"));
    } else {
      return (string("CRANE:STOP"));
    }
  }
  if(Y.changed){
    Y.changed = false;
    if(Y.value){
      return (string("CRANE:RAISE"));
    } else {
      return (string("CRANE:STOP"));
    }
  }
  if(B.changed){
    B.changed = false;
    if(B.value){
      return (string("PLIERS:OPEN"));
    } else {
      return (string("PLIERS:STOP"));
    }
  }
  if(X.changed){
    X.changed = false;
    if(X.value){
      return (string("PLIERS:CLOSE"));
    } else {
      return (string("PLIERS:STOP"));
    }
  }
  if(HOME.changed){
    HOME.changed = false;
    if(HOME.value){
      return (string("A"));
    }
  }
  if (JSL_V.changed || JSL_H.changed){
    JSL_H.changed = false;
    JSL_V.changed = false;
    string v = to_string((-1 * JSL_V.value)/327);
    string h = to_string((JSL_H.value)/327);
    return (string("MOVE:" + v + ":" + h));
  }
  if (DPAD_V.changed){
    DPAD_V.changed = false;
    string state = "CRANE:";
    switch(DPAD_V.value){
      case 0:
        state += "STOP";
        break;
      case 1:
        state += "LOWER";
        break;
      case -1:
        state += "RAISE";
        break;
    }
    return state;
  }
  if (DPAD_H.changed){
    DPAD_H.changed = false;
    string state = "PLIERS:";
    switch(DPAD_H.value){
      case 0:
        state += "STOP";
        break;
      case 1:
        state += "OPEN";
        break;
      case -1:
        state += "CLOSE";
        break;
    }
    return state;
  }
  return string("");
}

void Controller::update(input_event ev) {
  if (ev.type == 1) { // digital
    switch(ev.code) {
      case 304: setBooleanInputValue(&A, ev.value); break;
      case 305: setBooleanInputValue(&B, ev.value); break;
      case 307: setBooleanInputValue(&X, ev.value); break;
      case 308: setBooleanInputValue(&Y, ev.value); break;
      case 310: setBooleanInputValue(&L1, ev.value); break;
      case 311: setBooleanInputValue(&R1, ev.value); break;
      case 317: setBooleanInputValue(&JSL_B, ev.value); break;
      case 318: setBooleanInputValue(&JSR_B, ev.value); break;
      case 314: setBooleanInputValue(&SELECT, ev.value); break;
      case 315: setBooleanInputValue(&START, ev.value); break;
      case 316: setBooleanInputValue(&HOME, ev.value); break;
      default: cout << "[CONTROLLER] digital not assigned" << endl;
    }
  } else if (ev.type == 3) {            // analogic and dpad
    switch(ev.code) {
      case   0: setIntInputValue(&JSL_H, ev.value); break;
      case   1: setIntInputValue(&JSL_V, ev.value); break;
      case   3: setIntInputValue(&JSR_H, ev.value); break;
      case   4: setIntInputValue(&JSR_V, ev.value); break;
      case   2: setIntInputValue(&L2, ev.value); break;
      case   5: setIntInputValue(&R2, ev.value); break;
      case  16: setIntAsBooleanInputValue(&DPAD_H, ev.value); break;
      case  17: setIntAsBooleanInputValue(&DPAD_V, ev.value); break;
      default: cout << "[CONTROLLER] analog not assigned" << endl;
    }
  }
}

void Controller::setBooleanInputValue(booleanInput* input, bool value){
  if (input->value != value){
    input->value = value;
    input->changed = true;
  }
}

void Controller::setIntInputValue(intInput* input, int value){
  if (abs(value) < 5000){
    value = 0;
  }
  if (abs(input->value - value) > 1500){
    input->value = value;
    input->changed = true;
  }
}

void Controller::setIntAsBooleanInputValue(intInput* input, int value){
  if (input->value != value){
    input->value = value;
    input->changed = true;
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
