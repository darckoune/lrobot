$(document).ready(function(){
  // Create JoyStick object into the DIV 'joyDiv'
  var joy1 = new JoyStick('joyDiv',
  {
    title : "joystick1",
		width : 75,
		height : 75,
		internalFillColor : '#00AA00',
		internalLineWidth : 2,
		internalStrokeColor : '#003300',
		externalLineWidth : 2,
		externalStrokeColor : '#008000'
  });

  var joy2 = new JoyStick('joyDiv',
  {
    title : "joystick2",
		width : 75,
		height : 75,
		internalFillColor : '#00AA00',
		internalLineWidth : 2,
		internalStrokeColor : '#003300',
		externalLineWidth : 2,
		externalStrokeColor : '#008000'
  });

  // var inputPosX = document.getElementById("posizioneX");
  // var inputPosY = document.getElementById("posizioneY");
  // var direzione = document.getElementById("direzione");
  // var x = document.getElementById("X");
  // var y = document.getElementById("Y");
  //
  // setInterval(function(){ inputPosX.value=joy1.GetPosX(); }, 50);
  // setInterval(function(){ inputPosY.value=joy1.GetPosY(); }, 50);
  // setInterval(function(){ direzione.value=joy1.GetDir(); }, 50);
  // setInterval(function(){ x.value=joy1.GetX(); }, 50);
  // setInterval(function(){ y.value=joy1.GetY(); }, 50);

  (function test() {
    setTimeout(function() {
      joy2.Set(50, 50);
    }, 1000);
    setTimeout(function() {
      joy2.Set(-50, 32);
    }, 1500);
    setTimeout(function() {
      joy2.Set(11, 0);
    }, 2000);
    setTimeout(function() {
      joy2.Set(2, -40);
    }, 2500);
    setTimeout(function() {
      joy2.Set(0, 0);
    }, 3000);
  })();
});
