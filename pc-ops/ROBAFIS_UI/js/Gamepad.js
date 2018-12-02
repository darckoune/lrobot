var imgGamepad;
var canvasGamepad;
var ctxGamepad;

var joy1;
var joy2;
var buttonA;
var buttonB;
var buttonX;
var buttonY;
var buttonSTART;
var buttonSELECT;
var dpadLeft;
var dpadRight;
var dpadUp;
var dpadDown;
var buttonXbox;
var triggerL1;
var triggerL2;
var triggerR1;
var triggerR2;

var joyX = 0;
var joyY = 0;
var bA = false;
var bB = false;
var bX = false;
var bY = false;
var tL1 = false;
var tL2 = false;
var tR1 = false;
var tR2 = false;
var bXbox = false;
var dLeft = false;
var dRight = false;

function drawGamepadCanvasBackground() {
  ctxGamepad.drawImage(imgGamepad, 0, 0);
  // select button
  buttonSELECT.erase();
  // start button
  buttonSTART.erase();
  // L1, L2, R1, R2
  triggerL1.erase();
  triggerL2.erase();
  triggerR1.erase();
  triggerR2.erase();
}

addWebsocketCallback(function(data) {
  if (data.type == "controller") {
    var str     = data.message;
    var strCopy = str.split(':');

    if(strCopy[0] == "CRANE") { // A Y
      if(strCopy[1] == "RAISE") {
        bY = true;
      }
      if(strCopy[1] == "LOWER") {
        bA = true;
      }
      if(strCopy[1] == "STOP") {
        bA = false;
        bY = false;
      }
    }

    if(strCopy[0] == "PLIERS") { // X B
      if(strCopy[1] == "OPEN") {
        bB = true;
      }
      if(strCopy[1] == "CLOSE"){
        bX = true;
      }
      if(strCopy[1] == "STOP"){
        bB = false;
        bX = false;
      }
    }

    if(strCopy[0] == "MOVE") { // joy L
      joy1.setXY(strCopy[1], strCopy[2]);
    }

    if(strCopy[1] == "PILOT" || strCopy[1] == "MANU") {
      bXbox = true;
      setTimeout(function() {
        buttonXbox.erase();
      }, 500);
    }

    if(strCopy[0] == "REVERSE") {
      if(strCopy[1] == "LEFT") {
        dLeft = true;
        setTimeout(function() {
          dpadLeft.erase();
        }, 500);
      }
      if (strCopy[1] == "RIGHT") {
        dRight = true;
        setTimeout(function() {
          dpadRight.erase();
        }, 500);
      }
    }

    if(strCopy[0] == "THRESHOLD") { // L1
      if(strCopy[1] == "ENABLED") {
        tL1 = false;        
      }
      if(strCopy[1] == "DISABLED"){
        tL1 = true;
      }
    }

    if(strCopy[0] == "SWAP") { //R1
      tR1 = true;
      setTimeout(function() {
        triggerR1.erase();
      }, 500);
    }

    drawGamepadCanvasBackground();

    joy1.draw();
    joy2.draw();
    if (bA) buttonA.draw();
    if (bB) buttonB.draw();
    if (bX) buttonX.draw();
    if (bY) buttonY.draw();
    if (tL1) {
      triggerL1.draw();
    } else {
      triggerL1.erase();
    }
    if (tL2) triggerL2.draw();
    if (tR1) {
      triggerR1.draw();
      tR1 = false;
    }
    if (tR2) triggerR2.draw();
    if (bXbox) {
      buttonXbox.draw();
      bXbox = false;
    }
    if (dLeft) {
      dpadLeft.draw();
      dLeft = false;
    }
    if (dRight) {
      dpadRight.draw();
      dRight = false;
    }

  }
});

$(window).on("load", function() {
  imgGamepad = document.getElementById("gamepadImg");
  canvasGamepad = document.getElementById("gamepad");
  canvasGamepad.width = imgGamepad.width;
  canvasGamepad.height = imgGamepad.height;
  ctxGamepad = canvasGamepad.getContext("2d");

  // buttons & triggers not on the imgGamepad basically
  buttonSELECT = new RoundButton(ctxGamepad, 129, 90, 5, "black", "#AAAAAA");
  buttonSTART  = new RoundButton(ctxGamepad, 169, 90, 5, "black", "#AAAAAA");
  triggerL1    = new CustomButton(ctxGamepad, [49,64], [91,49], [102,55], [46,75], "black", "#CCCCCC");
  triggerL2    = new CustomButton(ctxGamepad, [53,44], [74,37], [84,43], [50,55], "black", "#CCCCCC");
  triggerR1    = new CustomButton(ctxGamepad, [209,49], [251,64], [254,75], [198,55], "black", "#CCCCCC");
  triggerR2    = new CustomButton(ctxGamepad, [226,37], [247,44], [250,55], [216,43], "black", "#CCCCCC");

  drawGamepadCanvasBackground();

  joy1         = new JoyStick(ctxGamepad, 71, 104.5, 20, 15, "#CCCCCC");
  joy1.draw();
  joy2         = new JoyStick(ctxGamepad, 189.5, 156, 20, 15, "#CCCCCC");
  joy2.draw();
  buttonA      = new RoundButton(ctxGamepad, 226, 125, 11, "#006612");
  buttonB      = new RoundButton(ctxGamepad, 246, 104.5, 11, "#A51000");
  buttonX      = new RoundButton(ctxGamepad, 205, 104.5, 11, "#01186b");
  buttonY      = new RoundButton(ctxGamepad, 225.5, 84, 11, "#725700");
  dpadLeft     = new SquareButton(ctxGamepad, 82, 144.5, 10, 20, 2, "#FFFFFFAA", "#546A79");
  dpadUp       = new SquareButton(ctxGamepad, 103.5, 124, 20, 10, 2, "#FFFFFFAA", "#546A79");
  dpadRight    = new SquareButton(ctxGamepad, 134, 144.5, 10, 20, 2, "#FFFFFFAA", "#546A79");
  dpadDown     = new SquareButton(ctxGamepad, 103.5, 174.5, 20, 10, 2, "#FFFFFFAA", "#546A79");
  buttonXbox   = new XboxButton(ctxGamepad, "#FFFF00");
  
});

/*(function testGamepad() {
  var data = '';
  setTimeout(function() {
    data = {type: 'controller', message: 'CRANE:RAISE'};//yellow
    callbackTest(data);
  }, 1000);
  setTimeout(function() {
    data = {type: 'controller', message: 'CRANE:STOP'};
    callbackTest(data);
  }, 2000);
  setTimeout(function() {
    data = {type: 'controller', message: 'CRANE:LOWER'};//green
    callbackTest(data);
  }, 3000);
  setTimeout(function() {
    data = {type: 'controller', message: 'CRANE:STOP'};
    callbackTest(data);
  }, 4000);
  setTimeout(function() {
    data = {type: 'controller', message: 'PLIERS:OPEN'};//red
    callbackTest(data);
  }, 5000);
  setTimeout(function() {
    data = {type: 'controller', message: 'PLIERS:STOP'};
    callbackTest(data);
  }, 6000);
  setTimeout(function() {
    data = {type: 'controller', message: 'PLIERS:CLOSE'};//blue
    callbackTest(data);
  }, 7000);
  setTimeout(function() {
    data = {type: 'controller', message: 'PLIERS:STOP'};
    callbackTest(data);
  }, 8000);

  setTimeout(function() {
    data = {type: 'controller', message: 'MOVE:100:100'};//joyL
    callbackTest(data);
  }, 9000);
  setTimeout(function() {
    data = {type: 'controller', message: 'MOVE:-100:-100'};//joyL
    callbackTest(data);
  }, 10000);

  setTimeout(function() {
    data = {type: 'controller', message: ':PILOT'};//xbox button
    callbackTest(data);
  }, 11000);
  setTimeout(function() {
    data = {type: 'controller', message: ':PILOT'};//xbox button
    callbackTest(data);
  }, 12000);

  setTimeout(function() {
    data = {type: 'controller', message: 'REVERSE:LEFT'};//arrowL
    callbackTest(data);
  }, 13000);
  setTimeout(function() {
    data = {type: 'controller', message: 'REVERSE:RIGHT'};//arrowR
    callbackTest(data);
  }, 14000);

  setTimeout(function() {
    data = {type: 'controller', message: 'THRESHOLD:DISABLED'};//L1
    callbackTest(data);
  }, 15000);
  setTimeout(function() {
    data = {type: 'controller', message: 'THRESHOLD:ENABLED'};
    callbackTest(data);
  }, 16000);

  setTimeout(function() {
    data = {type: 'controller', message: 'SWAP'};//R1
    callbackTest(data);
  }, 17000);
})();*/