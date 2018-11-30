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
var tR1 = false;
var bXbox = false;
var dLeft = false;
var dRight = false;

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
      } else {
        dRight = true;
        setTimeout(function() {
          dpadRight.erase();
        }, 500);
      }
    }

    ctxGamepad.drawImage(imgGamepad, 0, 0);
    ctxGamepad.fillStyle = "#AAAAAA";
    ctxGamepad.beginPath();
    ctxGamepad.arc(129, 90, 5, 0, 2*Math.PI);
    ctxGamepad.fill();
    ctxGamepad.beginPath();
    ctxGamepad.arc(169, 90, 5, 0, 2*Math.PI);
    ctxGamepad.fill();

    joy1.draw();
    joy2.draw();
    if (bA) buttonA.draw();
    if (bB) buttonB.draw();
    if (bX) buttonX.draw();
    if (bY) buttonY.draw();
    if (tR1) triggerR1.draw();
    if (bXbox) buttonXbox.draw();
    if (dLeft) dpadLeft.draw();
    if (dRight) dpadRight.draw();

  }
});

$(window).on("load", function() {
  imgGamepad = document.getElementById("gamepadImg");
  canvasGamepad = document.getElementById("gamepad");
  canvasGamepad.width = imgGamepad.width;
  canvasGamepad.height = imgGamepad.height;
  ctxGamepad = canvasGamepad.getContext("2d");

  ctxGamepad.drawImage(imgGamepad, 0, 0);
  ctxGamepad.fillStyle = "#AAAAAA";
  ctxGamepad.beginPath();
  ctxGamepad.arc(129, 90, 5, 0, 2*Math.PI);
  ctxGamepad.fill();
  ctxGamepad.beginPath();
  ctxGamepad.arc(169, 90, 5, 0, 2*Math.PI);
  ctxGamepad.fill();

  joy1         = new JoyStick(ctxGamepad, 71, 104.5, 20, 15, "#CCCCCC");
  joy1.draw();
  joy2         = new JoyStick(ctxGamepad, 189.5, 156, 20, 15, "#CCCCCC");
  joy2.draw();
  buttonA      = new RoundButton(ctxGamepad, 226, 125, 11, "#FFFFFF44");
  buttonB      = new RoundButton(ctxGamepad, 246, 104.5, 11, "#FFFFFF44");
  buttonX      = new RoundButton(ctxGamepad, 205, 104.5, 11, "#FFFFFF44");
  buttonY      = new RoundButton(ctxGamepad, 225.5, 84, 11, "#FFFFFF44");
  buttonSELECT = new RoundButton(ctxGamepad, 129, 90, 5, "#FFFFFF44");
  buttonSTART  = new RoundButton(ctxGamepad, 169, 90, 5, "#FFFFFF44");
  dpadLeft     = new SquareButton(ctxGamepad, 82, 144.5, 10, 20, 2, "#FFFFFFAA");
  dpadUp       = new SquareButton(ctxGamepad, 103.5, 124, 20, 10, 2, "#FFFFFFAA");
  dpadRight    = new SquareButton(ctxGamepad, 134, 144.5, 10, 20, 2, "#FFFFFFAA");
  dpadDown     = new SquareButton(ctxGamepad, 103.5, 174.5, 20, 10, 2, "#FFFFFFAA");
  buttonXbox   = new XboxButton(ctxGamepad, "#FFFF00");
  triggerL1    = new CustomButton(ctxGamepad, [49,64], [91,49], [102,55], [46,75], "#CCCCCC");
  triggerL2    = new CustomButton(ctxGamepad, [53,44], [74,37], [84,43], [50,55], "#CCCCCC");
  triggerR1    = new CustomButton(ctxGamepad, [209,49], [251,64], [254,75], [198,55], "#CCCCCC");
  triggerR2    = new CustomButton(ctxGamepad, [226,37], [247,44], [250,55], [216,43], "#CCCCCC");
});
