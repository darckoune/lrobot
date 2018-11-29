var img;
var canvas;
var ctx;
var joy1;
var joy2;

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

  joy1 = new JoyStick(ctx, 71, 104.5, 20, 15, "#CCCCCC");;
  joy1.draw();

  joy2 = new JoyStick(ctx, 189.5, 156, 20, 15, "#CCCCCC");
  joy2.draw();

  buttonA = new RoundButton(ctx, 226, 125, 11, "#FFFFFF44");
  buttonA.draw();

  buttonB = new RoundButton(ctx, 246, 104.5, 11, "#FFFFFF44");
  buttonB.draw();

  buttonX = new RoundButton(ctx, 205, 104.5, 11, "#FFFFFF44");
  buttonX.draw();

  buttonY = new RoundButton(ctx, 225.5, 84, 11, "#FFFFFF44");
  buttonY.draw();

  buttonSELECT = new RoundButton(ctx, 129, 90, 5, "#FFFFFF44");
  buttonSELECT.draw();

  buttonSTART = new RoundButton(ctx, 169, 90, 5, "#FFFFFF44");
  buttonSTART.draw();

  dpadLeft = new SquareButton(ctx, 82, 144.5, 10, 20, 2, "#FFFFFFAA");
  dpadLeft.draw();

  dpadUp = new SquareButton(ctx, 103.5, 124, 20, 10, 2, "#FFFFFFAA");
  dpadUp.draw();

  dpadDown = new SquareButton(ctx, 134, 144.5, 10, 20, 2, "#FFFFFFAA");
  dpadDown.draw();

  dpadRight = new SquareButton(ctx, 103.5, 174.5, 20, 10, 2, "#FFFFFFAA");
  dpadRight.draw();

  xboxButton = new XboxButton(ctx, "#FFFFFF44");
  xboxButton.draw();

  triggerL1 = new CustomButton(ctx, [49,64], [91,49], [102,55], [46,75], "#CCCCCC");
  triggerL1.draw();

  triggerL2 = new CustomButton(ctx, [53,44], [74,37], [84,43], [50,55], "#CCCCCC");
  triggerL2.draw();

  triggerR1 = new CustomButton(ctx, [209,49], [251,64], [254,75], [198,55], "#CCCCCC");
  triggerR1.draw();

  triggerR2 = new CustomButton(ctx, [226,37], [247,44], [250,55], [216,43], "#CCCCCC");
  triggerR2.draw();
});
