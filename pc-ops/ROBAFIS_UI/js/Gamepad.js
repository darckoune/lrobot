var img;
var canvas;
var ctx;

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

    ctx.drawImage(img, 0, 0);
    ctx.fillStyle = "#AAAAAA";
    ctx.beginPath();
    ctx.arc(129, 90, 5, 0, 2*Math.PI);
    ctx.fill();
    ctx.beginPath();
    ctx.arc(169, 90, 5, 0, 2*Math.PI);
    ctx.fill();

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

$(document).ready(function(){
  img = document.getElementById("gamepadImg");
  canvas = document.getElementById("gamepad");
  canvas.width = img.width;
  canvas.height = img.height;
  ctx = canvas.getContext("2d");

  ctx.drawImage(img, 0, 0);
  ctx.fillStyle = "#AAAAAA";
  ctx.beginPath();
  ctx.arc(129, 90, 5, 0, 2*Math.PI);
  ctx.fill();
  ctx.beginPath();
  ctx.arc(169, 90, 5, 0, 2*Math.PI);
  ctx.fill();

  joy1         = new JoyStick(ctx, 71, 104.5, 20, 15, "#CCCCCC");
  joy1.draw();
  joy2         = new JoyStick(ctx, 189.5, 156, 20, 15, "#CCCCCC");
  joy2.draw();
  buttonA      = new RoundButton(ctx, 226, 125, 11, "#FFFFFF44");
  buttonB      = new RoundButton(ctx, 246, 104.5, 11, "#FFFFFF44");
  buttonX      = new RoundButton(ctx, 205, 104.5, 11, "#FFFFFF44");
  buttonY      = new RoundButton(ctx, 225.5, 84, 11, "#FFFFFF44");
  buttonSELECT = new RoundButton(ctx, 129, 90, 5, "#FFFFFF44");
  buttonSTART  = new RoundButton(ctx, 169, 90, 5, "#FFFFFF44");
  dpadLeft     = new SquareButton(ctx, 82, 144.5, 10, 20, 2, "#FFFFFFAA");
  dpadUp       = new SquareButton(ctx, 103.5, 124, 20, 10, 2, "#FFFFFFAA");
  dpadRight    = new SquareButton(ctx, 134, 144.5, 10, 20, 2, "#FFFFFFAA");
  dpadDown     = new SquareButton(ctx, 103.5, 174.5, 20, 10, 2, "#FFFFFFAA");
  buttonXbox   = new XboxButton(ctx, "#FFFF00");
  triggerL1    = new CustomButton(ctx, [49,64], [91,49], [102,55], [46,75], "#CCCCCC");
  triggerL2    = new CustomButton(ctx, [53,44], [74,37], [84,43], [50,55], "#CCCCCC");
  triggerR1    = new CustomButton(ctx, [209,49], [251,64], [254,75], [198,55], "#CCCCCC");
  triggerR2    = new CustomButton(ctx, [226,37], [247,44], [250,55], [216,43], "#CCCCCC");
});
