var Ihm = "PILOT";

addWebsocketCallback(function(data){
  if(data.type == "robot") {
    var str = data.message;
    var strCopy = str.split(':');
    if(strCopy[0] == 'STEP') {
      valideEtat(strCopy[1]);
    }
  }

  if(data.type == "controller") {
    var str = data.message;
    if(str == "AUTOPILOT") {
      changeIHM();
    }
  }

});

// Fonction pour passer de IHM manu à pilot
function changeIHM() {
  if (Ihm == "PILOT") {
    $("#bras").css('display', 'block');
    $("#pince").css('display', 'block');
    $('#colorDetection').css('display', 'none');
    $('#lineFollower').css('display', 'none');
  } else {
    $("#bras").css('display', 'none');
    $("#pince").css('display', 'none');
    $('#colorDetection').css('display', 'block');
    $('#lineFollower').css('display', 'block');
  }
}
// fonction de changement etat (étape du parcours)
  function valideEtat(etat) {
    for(i = etat ; i >= 0 ; i--) {
      $('#'+i).html('&#10003;');
      $('#'+i).css('background-color', 'green');
      $('#circle'+i).css('background-color', 'green');
    }
  }

  function init() {
    for(i = 6 ; i >= 0 ; i--) {
      $('#'+i).html(i);
      $('#'+i).css('background-color', '#075C93');
      $('#circle'+i).css('background-color', '#075C93');
    }
  }
  valideEtat(3);
console.log("bidule");
